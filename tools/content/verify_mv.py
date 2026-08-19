# -*- coding: utf-8 -*-
"""cmfMoveInfoBlob 이 옛 c0mv~c122mv 와 같은지 확인한다.

c<N>mv 는 이미 소스에서 지웠다(blob 으로 합쳤다). 그래서 verify_cmf.py 처럼
소스끼리 맞춰볼 수가 없다. 대신 지우기 전에 만든 팩과 대조한다. 그 팩에는
c0mv .. c122mv 가 항목별로 들어 있다.

    git show <커밋>:Resources/data/content.pack 로 옛 팩을 꺼내 쓴다.

    python tools/content/verify_mv.py                 #HEAD 의 팩과 대조
    python tools/content/verify_mv.py <커밋>
"""
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT

ROOT = CT.ROOT
DATA = os.path.join(CT.CLASSES, 'Data')

NAMELEN = 32
ENTRYSIZE = 48
MAGIC = 0x314B5049


def read_pack(buf):
    """{이름: 값목록(signed short)}"""
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

        if sz != 2:
            continue

        out[name] = struct.unpack_from('<%dh' % cells, buf, dat + off)

    return out


def read_blob():
    """CmfBlob.cpp 에서 cmfMoveInfoBlob 과 Idx 를 읽는다."""
    t = CT.read(os.path.join(DATA, 'CmfBlob.cpp'))
    out = {}

    for nm in ('cmfMoveInfoBlob', 'cmfMoveInfoIdx'):
        m = re.search(r'%s_builtin\[\]\s*=\s*\{(.*?)\n\};' % nm, t, re.S)

        if not m:
            raise SystemExit('%s 를 못 찾았다' % nm)

        out[nm] = [int(x) for x in re.findall(r'-?\d+', m.group(1))]

    return out['cmfMoveInfoBlob'], out['cmfMoveInfoIdx']


def main():
    rev = sys.argv[1] if len(sys.argv) > 1 else 'HEAD'

    r = subprocess.run(['git', 'show', '%s:Resources/data/content.pack' % rev],
                       cwd=ROOT, stdout=subprocess.PIPE)

    if r.returncode:
        sys.stderr.write('%s 의 팩을 못 꺼냈다\n' % rev)
        return 2

    old = read_pack(r.stdout)
    blob, idx = read_blob()

    names = sorted((n for n in old if re.match(r'^c\d+mv$', n)),
                   key=lambda n: int(n[1:-2]))

    if not names:
        sys.stderr.write('%s 의 팩에 c<N>mv 가 없다. 더 옛 커밋을 대라.\n' % rev)
        return 2

    if len(names) != len(idx) - 1:
        sys.stderr.write('개수가 다르다 (옛 %d, 새 %d)\n' % (len(names), len(idx) - 1))
        return 1

    bad = 0
    cells = 0

    for i, nm in enumerate(names):
        want = list(old[nm])
        got = blob[idx[i]:idx[i + 1]]
        cells += len(want)

        if want != got:
            print('  다르다 : %s (옛 %d칸, 새 %d칸)' % (nm, len(want), len(got)))
            bad += 1

    print('%s 의 팩과 맞춰봤다 : %d개 %d칸, 다른 곳 %d개' % (rev, len(names), cells, bad))
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
