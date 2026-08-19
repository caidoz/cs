# -*- coding: utf-8 -*-
"""슬롯 429개가 제 자료를 가리키는지 확인한다.

(옛 verify_mv.py 를 대신한다. 그쪽은 서로 다른 자료 123개만 봤다.)

[왜 필요한가]
처음 옮길 때 슬롯 429개 중 123개만 만들고 나머지 별칭을 놓쳤다. 부팅하자마자
죽었다. verify_cmf.py 는 슬롯 0..122 만 맞춰봐서 이걸 못 잡았다.

[무엇을 맞춰보나]
mv 가족은 옛 팩(c0mv..c122mv)에 자료가 통째로 들어 있다. 그래서

    새 : cmfMoveInfoBlob[ cmfMoveInfoSlot[s] .. ]
    옛 : 옛 팩의 c<slot_map[s]>mv

를 슬롯 429개 전부에 대해 한 칸씩 맞춰볼 수 있다. 슬롯 지도가 틀렸다면
여기서 잡힌다.

나머지 5가족은 옛 팩에 없다. 대신 슬롯 지도가 6가족 모두 같다는 것을
pack_cmf.slot_map 이 확인하므로, mv 가 맞으면 나머지도 같은 지도를 쓴다.

    python tools/content/verify_slots.py
"""
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT
import pack_cmf as PC

ROOT = CT.ROOT
DATA = os.path.join(CT.CLASSES, 'Data')

NAMELEN = 32
ENTRYSIZE = 48
MAGIC = 0x314B5049


def read_pack(rev):
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

        if sz == 2:
            out[name] = list(struct.unpack_from('<%dh' % cells, buf, dat + off))

    return out


def read_array(text, name):
    m = re.search(r'%s_builtin\[\]\s*=\s*\{(.*?)\n\};' % name, text, re.S)

    if not m:
        raise SystemExit('%s 를 못 찾았다' % name)

    #주석에도 숫자가 있다. 걷어내고 센다.
    body = re.sub(r'//[^\n]*', '', m.group(1))
    return [int(x) for x in re.findall(r'-?\d+', body)]


def main():
    slots = PC.slot_map()
    text = CT.read(os.path.join(DATA, 'CmfBlob.cpp'))
    blob = read_array(text, 'cmfMoveInfoBlob')
    off = read_array(text, 'cmfMoveInfoSlot')

    print('슬롯 %d개' % len(slots))

    if len(off) != len(slots):
        sys.stderr.write('슬롯표가 %d칸이다. %d칸이어야 한다\n'
                         % (len(off), len(slots)))
        return 1

    old = read_pack(PC.TABLE_REV)
    bad = 0
    cells = 0

    for s in range(len(slots)):
        name = 'c%dmv' % slots[s]
        want = old.get(name)

        if want is None:
            print('  슬롯 %d : 옛 팩에 %s 가 없다' % (s, name))
            bad += 1
            continue

        got = blob[off[s]:off[s] + len(want)]
        cells += len(want)

        if got != want:
            print('  슬롯 %3d (%s) 이 다르다' % (s, name))
            bad += 1

    print('슬롯 %d개 %d칸 맞춰봤다. 다른 곳 %d개' % (len(slots), cells, bad))

    #별칭이 실제로 겹치는지도 본다. 안 겹치면 지도를 잘못 읽은 것이다.
    uniq = len(set(off))
    print('  서로 다른 시작 위치 %d개 (자료 %d개와 같아야 한다)'
          % (uniq, len(set(slots))))

    if uniq != len(set(slots)):
        bad += 1

    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
