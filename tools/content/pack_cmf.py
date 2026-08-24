# -*- coding: utf-8 -*-
"""Cmf 모션 데이터를 소스에서 빼내 팩에 넣을 수 있는 꼴로 바꾼다.

[지금 모습]
Classes/Cmf/c0.h ~ c122.h 에 배열이 파일마다 5~7개씩, 모두 6.1MB.

    static const unsigned short c0Off[] = { ... };

이걸 Classes/Data/CmfData.h 의 표가 가리킨다.

    const unsigned short* const cmfOff[] = { c0Off, c1Off, ... };

[문제]
1. 소스에 박혀 있어서 캐릭터를 추가하려면 앱을 새로 올려야 한다.
2. static 이라 이 헤더를 포함하는 .cpp 마다 한 벌씩 복제된다.
3. 표가 주소 목록이라 팩에 못 담는다.

[바꾸는 꼴]
들쭉날쭉한 배열 123개를 하나로 잇고, 어디서 시작하는지를 따로 적는다.

    cmfOffBlob : c0Off + c1Off + ... 를 이어붙인 것
    cmfOffIdx  : 124칸. i번 cmf는 Blob[Idx[i]] 부터 Idx[i+1] 앞까지.

둘 다 평범한 1차원 배열이라 기존 팩 машин을 그대로 쓴다. 표는 부팅 때
    cmfOff[i] = cmfOffBlob + cmfOffIdx[i]
로 채운다. 호출부의 cmfOff[i][j] 는 안 바뀐다.

[값을 어떻게 얻나]
파이썬으로 숫자를 읽지 않는다. 값에 CMF_SNAIL, TSIZE * 3 같은 이름과 식이
섞여 있어서 다시 해석하면 틀린다. Cmf.h 를 그대로 컴파일해서 컴파일러가
이미 계산해 둔 배열을 그대로 써낸다.

    python tools/content/pack_cmf.py           #재보기만
    python tools/content/pack_cmf.py --write   #Data/CmfBlob.{h,cpp} 생성
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
CMFDIR = os.path.join(CLASSES, 'Cmf')
DATA = os.path.join(CLASSES, 'Data')

#슬롯 지도를 읽어올 커밋. 표를 헤더에서 지우기 전 마지막 판이다.
TABLE_REV = '0567f67'

#(표 이름, 배열 접미어, C 타입, 팩 종류)
#cmfHeroLoop 은 히어로 3명만 있다. 나머지는 cmf 123개 전부다.
FAMILIES = [
    ('cmfOff',           'Off',    'unsigned short', 'DPK_UINT'),
    ('cmfMotionImg',     'MI',     'signed short',   'DPK_INT'),
    ('cmfMotionImgCnt',  'MIC',    'unsigned short', 'DPK_UINT'),
    ('cmfMotionImgSize', 'MIS',    'signed short',   'DPK_INT'),
    ('cmfCrashSize',     'CS',     'signed short',   'DPK_INT'),
    ('cmfHeroLoop',      'Loop60', 'unsigned short', 'DPK_UINT'),
    #mv 는 Cmf/c*.h 가 아니라 Data/CmfData.cpp 에 있다. 이미 팩에 c0mv..c122mv
    #로 따로 들어가 있지만, 그러면 cmf 를 하나 늘릴 때 배열 이름이 새로 생겨야
    #한다. 다른 가족과 같이 blob 으로 합쳐야 CDN 으로 늘릴 수 있다.
    ('cmfMoveInfo',      'mv',     'signed short',   'DPK_INT'),
]

#포인터로 선언된 것들. sizeof 로 길이를 못 재니 _COUNT 를 쓴다.
BY_COUNT = {'mv'}

CTYPE_SIZE = {'unsigned short': 2, 'signed short': 2}


def cmf_ids():
    """Cmf.h 가 포함하는 c<N>.h 의 N 목록. 파일 이름이 아니라 포함 목록을
    본다. 빌드에 실제로 들어가는 것만 세야 한다."""
    t = CT.read(os.path.join(CLASSES, 'Cmf.h'))
    return [int(m) for m in re.findall(r'#include\s+"Cmf/c(\d+)\.h"', t)]


def hero_ids(ids):
    """cmfHeroLoop 이 가리키는 cmf 번호.

    Loop60 배열이 있는 cmf 가 곧 히어로다. CmfData.h 의 표를 읽지 않는다.
    그 표는 이 도구가 없애는 대상이라, 한 번 돌리고 나면 사라진다.
    """
    out = []

    for i in ids:
        t = CT.read(os.path.join(CMFDIR, 'c%d.h' % i))

        if re.search(r'\bc%dLoop60\s*\[\]' % i, t):
            out.append(i)

    return out


def slot_map():
    """슬롯 번호 -> 어느 cmf 의 자료를 쓰는가. 429칸.

    표에 슬롯이 429개인데 서로 다른 자료는 123개뿐이다. 슬롯 123부터는
    몬스터 변종이라 앞 cmf 를 6개씩 나눠 쓴다.

        cmfOff[123..128] = c3Off   (전부 같은 배열을 가리킨다)

    이 별칭 구조를 잃으면 안 된다. 잃으면 변종 몬스터가 엉뚱한 모션을
    쓰거나, 표 밖을 읽어 죽는다.

    표는 이미 헤더에서 지웠으므로 커밋된 판에서 읽는다.
    6가족(Off/MI/MIC/MIS/CS/mv)이 모두 같은 지도를 쓴다. 그래서 한 벌만 둔다.
    """
    r = subprocess.run(['git', 'show', '%s:Classes/Data/CmfData.h' % TABLE_REV],
                       cwd=ROOT, stdout=subprocess.PIPE)

    if r.returncode:
        raise SystemExit('%s 의 CmfData.h 를 못 꺼냈다' % TABLE_REV)

    text = r.stdout.decode('utf-8-sig', 'replace')
    maps = {}

    for table, suffix, _c, _k in FAMILIES:
        if suffix == 'Loop60':
            continue

        m = re.search(r'\*\s*const\s+%s\[\]\s*=\s*\{(.*?)\n\};' % table,
                      text, re.S)

        if not m:
            raise SystemExit('%s 표를 못 찾았다' % table)

        body = re.sub(r'//[^\n]*', '', m.group(1))
        ids = []

        for x in body.split(','):
            x = x.strip()

            if not x:
                continue

            mm = re.match(r'c(\d+)%s$' % suffix, x)

            if not mm:
                raise SystemExit('%s 안의 %r 을 못 읽었다' % (table, x))

            ids.append(int(mm.group(1)))

        maps[table] = ids

    #6가족이 같은 지도를 쓰는지 여기서 확인한다. 다르면 가족별로 따로 둬야 한다.
    ref = maps[FAMILIES[0][0]]

    for table, ids in maps.items():
        if ids != ref:
            raise SystemExit('%s 의 지도가 다르다. 가족별로 따로 둬야 한다' % table)

    return ref


DUMPER = r'''
//pack_cmf.py 가 만든 임시 프로그램. Cmf 배열을 이어붙여 써낸다.
#include "Cmf.h"
#include <stdio.h>
#include <string.h>

static FILE* g;

//한 배열을 내보낸다. 원소 크기는 전부 2바이트라 그대로 쓴다.
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


def build_dumper(ids, heroes, work):
    """가족별로 배열을 순서대로 내보내는 덤퍼를 만든다."""
    body = []

    for table, suffix, _ctype, _kind in FAMILIES:
        which = heroes if suffix == 'Loop60' else ids
        body.append('    //---- %s ----' % table)

        for i in which:
            if suffix in BY_COUNT:
                body.append('    Put(c%d%s, c%d%s_COUNT, 2);' % (i, suffix, i, suffix))
            else:
                body.append('    PUT(c%d%s);' % (i, suffix))

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

    out = os.path.join(work, 'cmf.bin')
    #Cmf.h 가 Def.h 를 거쳐 CmfData.h 를 끌어온다. 거기 있는 표(cmfMoveInfo)가
    #Data/*.cpp 의 배열을 참조하므로 그것들도 링크해야 한다. 다시 컴파일하면
    #오래 걸리니 MSBuild가 이미 만들어 둔 .obj 를 쓴다.
    #덤퍼가 읽는 CMF/이동 배열은 포함된 헤더 안의 static 데이터다. 게임의
    #Data/*.obj를 링크하면 CmfLink.obj가 DataPack 런타임 심볼을 요구하고,
    #오래된 증분 빌드 산출물 여부에 따라서도 결과가 달라진다.
    objs = []

    missing = [o for o in objs if not os.path.isfile(o)]

    if missing:
        sys.stderr.write('%s 가 없다. 먼저 win32를 빌드하라.\n' % missing[0])
        return None

    #.obj 가 Debug 빌드라 런타임을 맞춰야 링크된다.
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


def split_blobs(raw, ids, heroes, slots):
    """덤프를 가족별 (원소목록, 오프셋목록) 으로 나눈다."""
    at = 0
    result = []

    for table, suffix, ctype, _kind in FAMILIES:
        which = heroes if suffix == 'Loop60' else ids
        esz = CTYPE_SIZE[ctype]
        signed = ctype.startswith('signed')
        fmt = ('<%dh' if signed else '<%dH')

        blob = []
        start = {}		#cmf 번호 -> blob 안에서 시작하는 칸

        for i in which:
            cells = struct.unpack_from('<i', raw, at)[0]
            at += 4
            start[i] = len(blob)
            blob.extend(struct.unpack_from(fmt % cells, raw, at))
            at += cells * esz

        #슬롯마다 "어디서 시작하는가"를 적는다.
        #
        #슬롯은 429개인데 서로 다른 자료는 123개다. 슬롯 123부터는 몬스터
        #변종이라 앞 cmf 를 나눠 쓴다. 그래서 여러 슬롯이 같은 자리를 가리킨다.
        #예전 표(cmfOff[] = { c0Off, ..., c3Off, c3Off, ... })가 하던 일이다.
        if suffix == 'Loop60':
            #히어로 전용. 슬롯이 곧 히어로 번호다.
            off = [start[i] for i in which]
        else:
            off = [start[c] for c in slots]

        result.append((table, ctype, blob, off))

    if at != len(raw):
        raise SystemExit('덤프를 다 못 읽었다 (%d / %d)' % (at, len(raw)))

    return result


def emit(groups, slots, heroes, eol):
    """Data/CmfBlob.{h,cpp} 를 만든다."""
    H = []
    C = []

    note = [
        '//tools/content/pack_cmf.py 가 생성한다. 직접 고치지 말 것.',
        '//',
        '//Classes/Cmf/c*.h 에 흩어져 있던 모션 배열을 가족별로 하나씩 이어붙인',
        '//것이다. 슬롯마다 어디서 시작하는지는 <이름>Slot 이 들고 있다.',
        '//',
        '//    i번 슬롯의 자료 = Blob + Slot[i] 부터',
        '//',
        '//슬롯은 429개인데 서로 다른 자료는 123개다. 슬롯 123부터는 몬스터',
        '//변종이라 앞 cmf 를 나눠 쓴다. 그래서 여러 슬롯이 같은 자리를 가리킨다.',
        '//',
        '//평범한 1차원 배열이라 팩에 그대로 들어간다. 표(cmfOff 등)는 부팅 때',
        '//CmfRelink() 가 이 둘로 채운다.',
    ]

    H.append('#pragma once')
    H.append('')
    H.append('#ifndef _DATA_CMFBLOB_H_')
    H.append('#define _DATA_CMFBLOB_H_')
    H.append('')
    H.extend(note)
    H.append('')
    H.append('#include "../Def.h"')
    H.append('')

    C.extend(note)
    C.append('')
    C.append('#include "CmfBlob.h"')
    C.append('')

    for table, ctype, blob, off in groups:
        for nm, typ, vals in ((table + 'Blob', ctype, blob),
                              (table + 'Slot', 'unsigned int', off)):
            H.append('extern const %s* %s;' % (typ, nm))
            H.append('enum { %s_COUNT = %d };' % (nm, len(vals)))
            H.append('')

            C.append('static const %s %s_builtin[] = {' % (typ, nm))

            for a in range(0, len(vals), 16):
                C.append('\t' + ', '.join(str(v) for v in vals[a:a + 16]) + ',')

            C.append('};')
            C.append('')
            C.append('const %s* %s = %s_builtin;' % (typ, nm, nm))
            C.append('')

    H.append('//슬롯 개수. 표를 채울 때 쓴다. 서로 다른 자료 수가 아니다.')
    H.append('enum { CMF_BUILTIN_COUNT = %d, CMF_HERO_COUNT = %d };' %
             (len(slots), len(heroes)))
    H.append('')
    H.append('#endif')
    H.append('')

    return eol.join(H), eol.join(C)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    ids = cmf_ids()
    heroes = hero_ids(ids)
    slots = slot_map()
    print('cmf %d개, 히어로 %d개, 슬롯 %d개' % (len(ids), len(heroes), len(slots)))

    work = tempfile.mkdtemp(prefix='packcmf_')

    try:
        src = build_dumper(ids, heroes, work)
        raw = run_dumper(src, work)

        if raw is None:
            return 1

        groups = split_blobs(raw, ids, heroes, slots)
    finally:
        shutil.rmtree(work, ignore_errors=True)

    total = 0

    for table, ctype, blob, off in groups:
        b = len(blob) * CTYPE_SIZE[ctype]
        total += b + len(off) * 4
        print('  %-18s %8d칸 %9s바이트   슬롯 %d칸'
              % (table, len(blob), format(b, ','), len(off)))

    print('  합계 %s 바이트' % format(total, ','))

    htext, ctext = emit(groups, ids, heroes, '\r\n')

    print('  Data/CmfBlob.h   %s 바이트' % format(len(htext), ','))
    print('  Data/CmfBlob.cpp %s 바이트' % format(len(ctext), ','))

    if not args.write:
        print('  (실제로 쓰려면 --write)')
        return 0

    with open(os.path.join(DATA, 'CmfBlob.h'), 'w',
              encoding='utf-8-sig', newline='') as fp:
        fp.write(htext + '\r\n')

    with open(os.path.join(DATA, 'CmfBlob.cpp'), 'w',
              encoding='utf-8-sig', newline='') as fp:
        fp.write(ctext + '\r\n')

    print('  썼다')
    return 0


if __name__ == '__main__':
    sys.exit(main())
