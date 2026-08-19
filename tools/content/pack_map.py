# -*- coding: utf-8 -*-
"""지도 데이터를 소스에서 빼내 팩에 넣을 수 있는 꼴로 바꾼다.

Cmf 와 구조가 같다(tools/content/pack_cmf.py 참고).

[지금 모습]
Classes/Write.h 에 배열이 맵마다 7개씩, 426맵 2,983개, 모두 2.0MB.

    const unsigned char ma0[] = { ... };   //타일
    const unsigned char mt0[] = { ... };   //타일종류
    ...

이걸 Classes/Data/MapData.h 의 표가 가리킨다.

    const unsigned char* const mapPtr[TOTALMAP] = { ma0, ma1, ... };

[바꾸는 꼴]
가족마다 하나로 잇고, 어디서 시작하는지를 따로 적는다.

    mapPtrBlob : ma0 + ma1 + ... 를 이어붙인 것
    mapPtrIdx  : 맵수 + 1 칸

표는 부팅 때 MapRelink() 가 채운다. 호출부의 mapPtr[i][j] 는 안 바뀐다.

    python tools/content/pack_map.py
    python tools/content/pack_map.py --write
"""
import argparse
import os
import re
import struct
import subprocess
import sys
import tempfile
import shutil

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT
import dump_ids as D

ROOT = CT.ROOT
CLASSES = CT.CLASSES
DATA = os.path.join(CLASSES, 'Data')

#(표 이름, 배열 접두어, C 타입)
FAMILIES = [
    ('mapPtr',        'ma', 'unsigned char'),
    ('mapTilePtr',    'mt', 'unsigned char'),
    ('mapRectPtr',    'mr', 'unsigned char'),
    ('mapBackPtr',    'mb', 'signed short'),
    ('mapObjPtr',     'mo', 'signed short'),
    ('mapNeutralPtr', 'mn', 'signed short'),
    ('mapEnemyPtr',   'me', 'unsigned short'),
]

CTYPE_SIZE = {'unsigned char': 1, 'signed short': 2, 'unsigned short': 2}
CTYPE_FMT = {'unsigned char': 'B', 'signed short': 'h', 'unsigned short': 'H'}


def map_ids():
    """mapPtr 표에 적힌 순서 그대로의 맵 번호.

    ma0, ma1 처럼 번호가 이름에 들어 있지만 표의 순서가 진짜다. 표가
    비어 있거나 순서가 다르면 그쪽을 따라야 한다.
    """
    t = CT.read(os.path.join(DATA, 'MapData.h'))
    m = re.search(r'mapPtr\[TOTALMAP\]\s*=\s*\{(.*?)\n\};', t, re.S)

    if not m:
        #표를 이미 갈아끼운 뒤다. 커밋된 판에서 읽는다. 순서를 짐작하면 안 된다.
        r = subprocess.run(['git', 'show', 'HEAD:Classes/Data/MapData.h'],
                           cwd=ROOT, stdout=subprocess.PIPE)

        if r.returncode == 0:
            m = re.search(r'mapPtr\[TOTALMAP\]\s*=\s*\{(.*?)\n\};',
                          r.stdout.decode('utf-8-sig', 'replace'), re.S)

    if not m:
        raise SystemExit('mapPtr 표를 못 찾았다')

    return [int(x) for x in re.findall(r'\bma(\d+)\b', m.group(1))]


DUMPER = r'''
//pack_map.py 가 만든 임시 프로그램. 지도 배열을 이어붙여 써낸다.
#include "Write.h"
#include <stdio.h>

static FILE* g;

static void Put(const void* p, int cells, int esz)
{
    fwrite(&cells, 4, 1, g);
    fwrite(p, (size_t)esz, (size_t)cells, g);
}

#define PUT(A) Put(A, (int)(sizeof(A) / sizeof(A[0])), (int)sizeof(A[0]))

int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;

    g = fopen(argv[1], "wb");

    if (!g)
        return 1;

__BODY__

    fclose(g);
    return 0;
}
'''


def build_dumper(ids, work):
    body = []

    for table, prefix, _ctype in FAMILIES:
        body.append('    //---- %s ----' % table)

        for i in ids:
            body.append('    PUT(%s%d);' % (prefix, i))

        body.append('')

    src = os.path.join(work, 'dumper.cpp')

    with open(src, 'w', encoding='utf-8') as fp:
        fp.write(DUMPER.replace('__BODY__', '\n'.join(body)))

    return src


def run_dumper(src, work):
    vcvars = D.find_vs()

    if not vcvars:
        sys.stderr.write('Visual Studio를 못 찾았다\n')
        return None

    out = os.path.join(work, 'map.bin')

    objdir = os.path.join(ROOT, 'proj.win32', 'Debug.win32')
    objs = [os.path.join(objdir, os.path.splitext(n)[0] + '.obj')
            for n in sorted(os.listdir(DATA))
            if n.endswith('.cpp') and n not in
            ('DataPack.cpp', 'DataCount.cpp', 'DataPackCheck.cpp',
             'CmfLink.cpp', 'MapLink.cpp', 'MapBlob.cpp')]

    missing = [o for o in objs if not os.path.isfile(o)]

    if missing:
        sys.stderr.write('%s 가 없다. 먼저 win32를 빌드하라.\n' % missing[0])
        return None

    cmd = ('call "%s" >nul 2>&1 && cl /nologo /EHsc /utf-8 /W0 /MDd /D_DEBUG '
           '/I "%s" "%s" %s /Fe:"%s"'
           % (vcvars, CLASSES, src, ' '.join('"%s"' % o for o in objs),
              os.path.join(work, 'd.exe')))

    r = subprocess.run(cmd, shell=True, cwd=work,
                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    if r.returncode:
        sys.stderr.write(r.stdout.decode('mbcs', 'replace'))
        return None

    r = subprocess.run([os.path.join(work, 'd.exe'), out],
                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    if r.returncode:
        sys.stderr.write(r.stdout.decode('mbcs', 'replace'))
        return None

    with open(out, 'rb') as fp:
        return fp.read()


def split_blobs(raw, ids):
    at = 0
    result = []

    for table, _prefix, ctype in FAMILIES:
        esz = CTYPE_SIZE[ctype]
        fmt = '<%d' + CTYPE_FMT[ctype]

        blob = []
        idx = [0]

        for _i in ids:
            cells = struct.unpack_from('<i', raw, at)[0]
            at += 4
            blob.extend(struct.unpack_from(fmt % cells, raw, at))
            at += cells * esz
            idx.append(len(blob))

        result.append((table, ctype, blob, idx))

    if at != len(raw):
        raise SystemExit('덤프를 다 못 읽었다 (%d / %d)' % (at, len(raw)))

    return result


NOTE = [
    '//tools/content/pack_map.py 가 생성한다. 직접 고치지 말 것.',
    '//',
    '//Classes/Write.h 에 흩어져 있던 지도 배열을 가족별로 하나씩 이어붙인',
    '//것이다. 어느 맵이 어디서 시작하는지는 <이름>Idx 가 들고 있다.',
    '//',
    '//    i번 맵의 자료 = Blob[Idx[i]] .. Blob[Idx[i + 1]] 앞까지',
    '//',
    '//평범한 1차원 배열이라 팩에 그대로 들어간다. 표(mapPtr 등)는 부팅 때',
    '//MapRelink() 가 이 둘로 채운다.',
]


def emit(groups, ids, eol):
    H = ['#pragma once', '', '#ifndef _DATA_MAPBLOB_H_',
         '#define _DATA_MAPBLOB_H_', '']
    H.extend(NOTE)
    H.extend(['', '#include "../Def.h"', ''])

    C = list(NOTE)
    C.extend(['', '#include "MapBlob.h"', ''])

    for table, ctype, blob, idx in groups:
        for nm, typ, vals in ((table + 'Blob', ctype, blob),
                              (table + 'Idx', 'unsigned int', idx)):
            H.append('extern const %s* %s;' % (typ, nm))
            H.append('enum { %s_COUNT = %d };' % (nm, len(vals)))
            H.append('')

            C.append('static const %s %s_builtin[] = {' % (typ, nm))

            for a in range(0, len(vals), 20):
                C.append('\t' + ', '.join(str(v) for v in vals[a:a + 20]) + ',')

            C.extend(['};', '', 'const %s* %s = %s_builtin;' % (typ, nm, nm), ''])

    H.append('//맵 개수. 표를 채울 때 쓴다.')
    H.append('enum { MAP_BUILTIN_COUNT = %d };' % len(ids))
    H.extend(['', '#endif', ''])

    return eol.join(H), eol.join(C)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    ids = map_ids()
    print('맵 %d개' % len(ids))

    work = tempfile.mkdtemp(prefix='packmap_')

    try:
        raw = run_dumper(build_dumper(ids, work), work)

        if raw is None:
            return 1

        groups = split_blobs(raw, ids)
    finally:
        shutil.rmtree(work, ignore_errors=True)

    total = 0

    for table, ctype, blob, idx in groups:
        b = len(blob) * CTYPE_SIZE[ctype]
        total += b + len(idx) * 4
        print('  %-16s %8d칸 %10s바이트   Idx %d칸'
              % (table, len(blob), format(b, ','), len(idx)))

    print('  합계 %s 바이트' % format(total, ','))

    htext, ctext = emit(groups, ids, '\r\n')
    print('  Data/MapBlob.h   %s 바이트' % format(len(htext), ','))
    print('  Data/MapBlob.cpp %s 바이트' % format(len(ctext), ','))

    if not args.write:
        print('  (실제로 쓰려면 --write)')
        return 0

    for nm, txt in (('MapBlob.h', htext), ('MapBlob.cpp', ctext)):
        with open(os.path.join(DATA, nm), 'w',
                  encoding='utf-8-sig', newline='') as fp:
            fp.write(txt + '\r\n')

    print('  썼다')
    return 0


if __name__ == '__main__':
    sys.exit(main())
