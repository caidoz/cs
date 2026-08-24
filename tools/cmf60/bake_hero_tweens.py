# -*- coding: utf-8 -*-
"""c0/c1/c2의 재생성 모션만 기존 CmfBlob에 병합한다.

c3 이후와 이미 패킹된 cNmv는 건드리지 않는다. 전체 pack_cmf.py가 소스에서
제거된 옛 배열을 요구하는 문제를 피하면서 히어로 보간 결과를 실제 데이터에
굽기 위한 전용 도구다.
"""
import io
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)

from cmflib import val
from hero import expandHero

BLOB_CPP = os.path.join(ROOT, 'Classes', 'Data', 'CmfBlob.cpp')
BLOB_H = os.path.join(ROOT, 'Classes', 'Data', 'CmfBlob.h')
BASE = '05997da'
IMGDEF = os.path.join(ROOT, 'Classes', 'Def', 'ImgDef.h')

FAMILIES = (
    ('cmfMotionImg', 'signed short'),
    ('cmfMotionImgCnt', 'unsigned short'),
    ('cmfMotionImgSize', 'signed short'),
    ('cmfCrashSize', 'signed short'),
)


def image_type_symbols():
    text = io.open(IMGDEF, encoding='utf-8-sig').read()
    symbols = {}
    for name, expr in re.findall(r'^\s*([A-Za-z_]\w*)\s*=\s*([^,]+),', text, re.M):
        try:
            symbols[name] = int(eval(expr, {'__builtins__': {}}, symbols))
        except (NameError, SyntaxError):
            pass
    return symbols


IMAGE_TYPE = image_type_symbols()


def numbers(text, name):
    pattern = (r'(static const [^{]+\b' + re.escape(name)
               + r'_builtin\[\]\s*=\s*\{)(.*?)(\n\};)')
    match = re.search(pattern, text, re.S)
    if not match:
        raise RuntimeError('%s 배열을 찾지 못했다' % name)
    body = re.sub(r'//.*', '', match.group(2))
    return match, [int(x) for x in re.findall(r'-?\d+', body)]


def render(vals):
    lines = []
    for at in range(0, len(vals), 16):
        lines.append('\t' + ', '.join(str(v) for v in vals[at:at + 16]) + ',')
    return '\n' + '\n'.join(lines)


def numeric(token):
    result = val(str(token))
    if result is None:
        result = IMAGE_TYPE.get(str(token).strip())
    if result is None:
        raise RuntimeError('숫자로 바꿀 수 없는 CMF 값: %s' % token)
    return result


def hero_tables(c):
    image = []
    count = []
    image_size = []
    crash = []
    part_at = 0

    for parts in c.newMotions:
        count.extend((part_at, len(parts)))
        for img, x, y, typ in parts:
            image.extend((img, x, y, numeric(typ)))
        part_at += len(parts)

    for row in c.newMis:
        image_size.extend(int(x) for x in row)
    for row in c.newCsRows:
        crash.extend(numeric(x) for x in row)

    return {
        'cmfMotionImg': image,
        'cmfMotionImgCnt': count,
        'cmfMotionImgSize': image_size,
        'cmfCrashSize': crash,
    }


def replace_three_slots(blob, slots, replacements):
    old_starts = slots[:3]
    old_tail = slots[3]
    new_starts = []
    merged = []
    for cells in replacements:
        new_starts.append(len(merged))
        merged.extend(cells)
    new_tail = len(merged)
    merged.extend(blob[old_tail:])
    delta = new_tail - old_tail
    start_map = dict(zip(old_starts, new_starts))

    new_slots = []
    for old in slots:
        if old in start_map:
            new_slots.append(start_map[old])
        elif old >= old_tail:
            new_slots.append(old + delta)
        else:
            raise RuntimeError('예상하지 못한 히어로 슬롯 오프셋: %d' % old)
    return merged, new_slots


def main():
    generated = []
    for hero in range(3):
        source = subprocess.check_output(
            ['git', 'show', '%s:Classes/Cmf/c%d.h' % (BASE, hero)]
        ).decode('utf-8-sig')
        c, _chains, _loops = expandHero(hero, source, write_output=False)
        generated.append(hero_tables(c))

    cpp = io.open(BLOB_CPP, encoding='utf-8-sig', newline='').read()
    header = io.open(BLOB_H, encoding='utf-8-sig', newline='').read()

    for family, _ctype in FAMILIES:
        blob_match, blob = numbers(cpp, family + 'Blob')
        slot_match, slots = numbers(cpp, family + 'Slot')
        merged, new_slots = replace_three_slots(
            blob, slots, [generated[h][family] for h in range(3)])

        cpp = (cpp[:blob_match.start(2)] + render(merged)
               + cpp[blob_match.end(2):])
        slot_match, _ = numbers(cpp, family + 'Slot')
        cpp = (cpp[:slot_match.start(2)] + render(new_slots)
               + cpp[slot_match.end(2):])

        header = re.sub(
            r'(enum \{ ' + re.escape(family) + r'Blob_COUNT = )\d+(; \};)',
            r'\g<1>%d\g<2>' % len(merged), header)
        header = re.sub(
            r'(enum \{ ' + re.escape(family) + r'Slot_COUNT = )\d+(; \};)',
            r'\g<1>%d\g<2>' % len(new_slots), header)
        print('%-24s %d cells' % (family, len(merged)))

    io.open(BLOB_CPP, 'w', encoding='utf-8-sig', newline='').write(cpp)
    io.open(BLOB_H, 'w', encoding='utf-8-sig', newline='').write(header)
    print('c0/c1/c2 보간 데이터를 CmfBlob에 병합했다')


if __name__ == '__main__':
    main()
