# -*- coding: utf-8 -*-
"""mapRectSize 같은 크기표를 sizeof 식에서 실제 숫자로 굳힌다.

[왜]
이렇게 정의돼 있다.

    static const unsigned int mapRectSize_builtin[] = {
        sizeof(mr0) / 5, sizeof(mr1) / 5, ...
    };

mr0 은 Classes/Write.h 의 배열이다. blob 으로 옮기고 헤더에서 지우면 이 식이
컴파일되지 않는다. 지우지 않고 포인터로만 바꿔도 sizeof 가 4를 주므로 값이
조용히 망가진다(cmfMove 가 실제로 그렇게 깨졌다).

[값을 어떻게 얻나]
Write.h 는 이미 지웠으므로 컴파일러에게 물어볼 수 없다. 대신 두 곳에서
따로 구해 서로 맞는지 본다. 한쪽만 믿지 않는다.

  1. MapBlob 의 색인표에서 계산한다.
         칸수 = Idx[i + 1] - Idx[i]
         값   = 칸수 * 원소크기 / 나누는수
  2. 커밋된 팩에 이미 들어 있는 값을 읽는다.

둘이 다르면 멈춘다.

    python tools/content/freeze_mapsize.py
    python tools/content/freeze_mapsize.py --write
"""
import argparse
import io
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT

ROOT = CT.ROOT
DATA = os.path.join(CT.CLASSES, 'Data')
CPP = os.path.join(DATA, 'MapData.cpp')

#(크기표 이름, 짝이 되는 blob 표, 원소 바이트, 나누는 수)
JOBS = [
    ('mapRectSize',    'mapRectPtr',    1, 5),
    ('mapBackSize',    'mapBackPtr',    2, 6),
    ('mapObjSize',     'mapObjPtr',     2, 6),
    ('mapNeutralSize', 'mapNeutralPtr', 2, 8),
    ('mapEnemySize',   'mapEnemyPtr',   2, 8),
]

NAMELEN = 32
ENTRYSIZE = 48
MAGIC = 0x314B5049


def read_idx(name):
    """MapBlob.cpp 에서 <name>Idx 를 읽는다."""
    t = CT.read(os.path.join(DATA, 'MapBlob.cpp'))
    m = re.search(r'%sIdx_builtin\[\]\s*=\s*\{(.*?)\n\};' % name, t, re.S)

    if not m:
        raise SystemExit('%sIdx 를 못 찾았다' % name)

    return [int(x) for x in re.findall(r'\d+', m.group(1))]


def read_old_pack(rev='HEAD'):
    """커밋된 팩에서 4바이트 배열들을 읽는다."""
    r = subprocess.run(['git', 'show', '%s:Resources/data/content.pack' % rev],
                       cwd=ROOT, stdout=subprocess.PIPE)

    if r.returncode:
        raise SystemExit('%s 의 팩을 못 꺼냈다' % rev)

    buf = r.stdout
    magic, _abi, count, _body = struct.unpack_from('<IIiI', buf, 0)

    if magic != MAGIC:
        raise SystemExit('팩이 아니다')

    dat = 16 + count * ENTRYSIZE
    out = {}

    for i in range(count):
        e = 16 + i * ENTRYSIZE
        name = buf[e:e + NAMELEN].split(b'\0')[0].decode('ascii')
        sz = buf[e + NAMELEN]
        cells, off = struct.unpack_from('<II', buf, e + NAMELEN + 4)

        if sz == 4:
            out[name] = list(struct.unpack_from('<%dI' % cells, buf, dat + off))

    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    old = read_old_pack()
    text = io.open(CPP, encoding='utf-8-sig', newline='').read()
    eol = '\r\n' if '\r\n' in text else '\n'
    bad = 0

    for name, blob, esz, div in JOBS:
        idx = read_idx(blob)
        vals = [(idx[i + 1] - idx[i]) * esz // div for i in range(len(idx) - 1)]

        want = old.get(name)

        if want is None:
            print('  %-16s 옛 팩에 없다. 맞춰볼 수 없다.' % name)
            bad += 1
            continue

        if want != vals:
            diff = [i for i in range(min(len(want), len(vals)))
                    if want[i] != vals[i]]
            print('  %-16s 안 맞는다. 옛 %d칸, 새 %d칸, 다른 곳 %d개 (처음 %s)'
                  % (name, len(want), len(vals), len(diff), diff[:5]))
            bad += 1
            continue

        print('  %-16s %d칸 일치' % (name, len(vals)))

        m = re.search(r'^static const unsigned int %s_builtin\[\]\s*=\s*\{'
                      % name, text, re.M)

        if not m:
            print('  %s_builtin 을 못 찾았다' % name)
            bad += 1
            continue

        close = text.index('};', m.end())
        body = [eol + '\t//sizeof(%s0) / %d 같은 식이었다. 그 배열이 blob 으로'
                % (blob[3:6].lower(), div),
                '\t//옮겨가 헤더에서 사라지므로 숫자로 굳혀 둔다.',
                '\t//tools/content/freeze_mapsize.py 가 적었다.']

        for a in range(0, len(vals), 20):
            body.append('\t' + ', '.join(str(v) for v in vals[a:a + 20]) + ',')

        text = text[:m.end()] + eol.join(body) + eol + text[close:]

    if bad:
        sys.stderr.write('%d개가 안 맞는다. 아무것도 안 쓴다.\n' % bad)
        return 1

    if not args.write:
        print('  (실제로 쓰려면 --write)')
        return 0

    io.open(CPP, 'w', encoding='utf-8-sig', newline='').write(text)
    print('  MapData.cpp 에 숫자로 적었다')
    return 0


if __name__ == '__main__':
    sys.exit(main())
