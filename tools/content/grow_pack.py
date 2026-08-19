# -*- coding: utf-8 -*-
"""팩에 콘텐츠를 하나 더 넣어본다. CDN 갱신을 흉내내는 시험 도구다.

[무엇을 증명하나]
"앱을 새로 올리지 않고 CDN 팩만으로 콘텐츠를 늘릴 수 있는가"가 목표다.
그 말이 참이려면, 이미 빌드된 클라이언트가 "몬스터가 한 마리 더 든 팩"을
읽어들여야 한다. 이 도구가 바로 그 팩을 만든다. 클라이언트는 손대지 않는다.

DataList.h 에서 콘텐츠 키를 읽어, 그 키에 매인 배열마다 마지막 콘텐츠의
값을 한 벌 더 붙인다. 목차와 CRC를 다시 쓴다.

    python tools/content/grow_pack.py enemy
    python tools/content/grow_pack.py enemy --out Resources/data/content.pack

--out 을 주지 않으면 content.pack.grown 으로 쓴다. 원본은 안 건드린다.
"""
import argparse
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT

ROOT = CT.ROOT
DATA = os.path.join(CT.CLASSES, 'Data')
PACK = os.path.join(ROOT, 'Resources', 'data', 'content.pack')

NAMELEN = 32
ENTRYSIZE = 48
MAGIC = 0x314B5049


def crc32(buf):
    """DataPackCrc 와 같은 것. 표준 CRC-32 다."""
    crc = 0xFFFFFFFF

    for b in bytearray(buf):
        crc ^= b

        for _ in range(8):
            crc = (crc >> 1) ^ (0xEDB88320 & -(crc & 1))

    return crc ^ 0xFFFFFFFF


def read_list():
    """DataList.h 에서 {이름: (키, 폭, 시작번호)} 를 읽는다."""
    t = CT.read(os.path.join(DATA, 'DataList.h'))
    out = {}

    for m in re.finditer(
            #시작번호는 음수일 수 있다. 색인표는 "콘텐츠 수 + 1" 칸이라 -1 이다.
            r'X\((\w+),\s*(\d+),\s*(\w+),\s*([^,]+),\s*(\w+),\s*(\d+),\s*(-?\d+)\)', t):
        out[m.group(1)] = (m.group(5), int(m.group(6)), int(m.group(7)))

    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('key', choices=['enemy', 'crew', 'skill', 'castle',
                                    'map', 'cmf', 'cmf_hero'])
    ap.add_argument('--add', type=int, default=1, help='몇 개 더 넣을까')
    ap.add_argument('--only', help='이 배열 하나만 늘린다. 어긋난 팩을 일부러 만들 때 쓴다')
    ap.add_argument('--out')
    args = ap.parse_args()

    want = 'DPK_KEY_' + args.key.upper()
    spec = read_list()
    keyed = [n for n, (k, _w, _b) in spec.items() if k == want]

    if not keyed:
        sys.stderr.write('%s 에 매인 배열이 없다\n' % want)
        return 1

    with open(PACK, 'rb') as fp:
        buf = fp.read()

    magic, abi, count, _body = struct.unpack_from('<IIiI', buf, 0)

    if magic != MAGIC:
        sys.stderr.write('팩이 아니다\n')
        return 1

    if crc32(buf[:-4]) != struct.unpack_from('<I', buf, len(buf) - 4)[0]:
        sys.stderr.write('원본 팩의 CRC가 안 맞는다\n')
        return 1

    dat = 16 + count * ENTRYSIZE

    #---- 원본을 읽어 항목별로 나눈다 ----
    items = []

    for i in range(count):
        e = 16 + i * ENTRYSIZE
        name = buf[e:e + NAMELEN].split(b'\0')[0].decode('ascii')
        sz = buf[e + NAMELEN]
        kind = buf[e + NAMELEN + 1]
        cells, off = struct.unpack_from('<II', buf, e + NAMELEN + 4)
        blob = buf[dat + off: dat + off + cells * sz]
        items.append([name, sz, kind, cells, bytearray(blob)])

    byname = {it[0]: it for it in items}

    #---- 콘텐츠에 매인 배열을 늘린다 ----
    grown = 0
    before = after = 0

    for it in items:
        name, sz, _kind, cells, blob = it

        if name not in keyed:
            continue

        if args.only and name != args.only:
            continue

        _k, w, base = spec[name]
        n = cells // w + base
        before = n

        if name.endswith('Idx'):
            #blob + 색인표 짝이다. 둘을 같이 늘려야 한다.
            #  색인표 : 마지막 칸 뒤에 "끝 + 방금 늘린 만큼" 을 더 적는다
            #  blob   : 마지막 콘텐츠 한 벌을 그대로 뒤에 붙인다
            pair = byname.get(name[:-3] + 'Blob')

            if pair is None:
                sys.stderr.write('%s 의 짝이 되는 Blob 을 못 찾았다\n' % name)
                return 1

            idx = list(struct.unpack_from('<%dI' % cells, bytes(blob), 0))
            seg = idx[-1] - idx[-2]          #마지막 콘텐츠의 칸 수
            psz = pair[1]
            tail = pair[4][idx[-2] * psz: idx[-1] * psz]

            for _ in range(args.add):
                pair[4].extend(tail)
                idx.append(idx[-1] + seg)

            pair[3] += args.add * seg
            it[4] = bytearray(struct.pack('<%dI' % len(idx), *idx))
            it[3] = len(idx)
            grown += 2
        else:
            tail = blob[-w * sz:]      #마지막 콘텐츠 한 벌을 그대로 복제한다

            for _ in range(args.add):
                blob.extend(tail)

            it[3] = cells + args.add * w
            grown += 1

        after = it[3] // w + base

    if not grown:
        sys.stderr.write('늘릴 배열을 못 찾았다\n')
        return 1

    #---- 다시 깐다 (본문은 8바이트 정렬) ----
    body = bytearray()
    offs = []

    for _name, sz, _kind, cells, blob in items:
        while len(body) % 8:
            body.append(0)

        offs.append(len(body))
        body.extend(blob)
        assert len(blob) == cells * sz

    out = bytearray()
    out.extend(struct.pack('<IIiI', MAGIC, abi, count, len(body)))

    for i, (name, sz, kind, cells, _blob) in enumerate(items):
        e = bytearray(ENTRYSIZE)
        nb = name.encode('ascii')
        e[0:len(nb)] = nb
        e[NAMELEN] = sz
        e[NAMELEN + 1] = kind
        struct.pack_into('<II', e, NAMELEN + 4, cells, offs[i])
        out.extend(e)

    out.extend(body)
    out.extend(struct.pack('<I', crc32(bytes(out))))

    path = os.path.join(ROOT, args.out) if args.out else PACK + '.grown'

    with open(path, 'wb') as fp:
        fp.write(bytes(out))

    print('%s : %d -> %d개' % (args.key, before, after))
    print('  건드린 배열 %d개, abi %08x (원본과 같아야 한다)' % (grown, abi))
    print('  %s  %d -> %d 바이트' % (os.path.relpath(path, ROOT), len(buf), len(out)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
