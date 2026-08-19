# -*- coding: utf-8 -*-
"""CmfBlob 의 색인표를 "cmf별 124칸" 에서 "슬롯별 429칸" 으로 고친다.

[무엇이 틀렸었나]
원래 표는 슬롯이 429개다.

    const unsigned short* const cmfOff[] = {
        c0Off, c1Off, ... c122Off,      //0..122  서로 다른 자료 123개
        c3Off, c3Off, c3Off, ...        //123..428 몬스터 변종이 나눠 쓴다
    };

서로 다른 자료는 123개지만 슬롯은 429개다. 슬롯 123부터는 앞 cmf 를 6개씩
나눠 쓰는 별칭이다. 처음 옮길 때 이 별칭 구조를 놓치고 123칸짜리 색인표만
만들었다. 그래서

  - 슬롯 123~255 는 엉뚱하게 0번 자료를 가리켰고
  - 슬롯 256~428 은 표(CAP_CMF=256) 밖이라 쓰레기 포인터를 읽어 죽었다

MAXCMF 가 429 라 CmfRead 가 슬롯 428까지 돈다. 부팅하자마자 터졌다.

[고치는 법]
자료(Blob)는 그대로 둔다. 이미 옛 배열과 한 칸씩 맞춰봐서 옳다는 것을
확인했다(452,988칸). 잘못된 것은 색인표뿐이다.

    옛 : cmfOffIdx[124]   i번 cmf 가 어디서 시작하나
    새 : cmfOffSlot[429]  i번 슬롯이 어디서 시작하나

슬롯 지도는 커밋된 CmfData.h 에서 그대로 읽는다(pack_cmf.slot_map).

    python tools/content/cmf_slots.py
    python tools/content/cmf_slots.py --write
"""
import argparse
import io
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT
import pack_cmf as PC

DATA = os.path.join(CT.CLASSES, 'Data')
CPP = os.path.join(DATA, 'CmfBlob.cpp')
H = os.path.join(DATA, 'CmfBlob.h')


def read_array(text, name):
    """CmfBlob.cpp 에서 <name>_builtin 의 숫자를 읽는다."""
    m = re.search(r'%s_builtin\[\]\s*=\s*\{(.*?)\n\};' % name, text, re.S)

    if not m:
        return None

    #주석에도 숫자가 있다. 걷어내고 센다.
    body = re.sub(r'//[^\n]*', '', m.group(1))
    return [int(x) for x in re.findall(r'-?\d+', body)]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    slots = PC.slot_map()
    text = CT.read(CPP)
    htext = CT.read(H)
    eol = '\r\n' if '\r\n' in text else '\n'

    print('슬롯 %d개, 서로 다른 cmf %d개' % (len(slots), len(set(slots))))

    bad = 0

    for table, suffix, _ctype, _kind in PC.FAMILIES:
        if suffix == 'Loop60':
            #히어로 전용. 슬롯이 곧 히어로 번호라 별칭이 없다. 그대로 둔다.
            continue

        idx = read_array(text, table + 'Idx')

        if idx is None:
            print('  %-18s Idx 가 없다. 이미 고친 뒤인가?' % table)
            bad += 1
            continue

        if len(idx) != len(set(slots)) + 1:
            print('  %-18s Idx 가 %d칸이다. %d칸이어야 한다'
                  % (table, len(idx), len(set(slots)) + 1))
            bad += 1
            continue

        #슬롯 s 는 slots[s] 번 cmf 의 자료를 쓴다. 그 자료는 Idx[slots[s]] 에서
        #시작한다. 별칭이라 여러 슬롯이 같은 값을 갖는다.
        off = [idx[c] for c in slots]

        body = [eol + '\t//슬롯마다 blob 안에서 어디서 시작하는지 적는다.',
                '\t//슬롯 %d개인데 서로 다른 자료는 %d개다. 뒤쪽 슬롯은 몬스터'
                % (len(slots), len(set(slots))),
                '\t//변종이라 앞 cmf 를 나눠 쓴다. 그래서 같은 값이 여러 번 나온다.']

        for a in range(0, len(off), 16):
            body.append('\t' + ', '.join(str(v) for v in off[a:a + 16]) + ',')

        #Idx -> Slot 으로 이름과 내용을 바꾼다.
        m = re.search(r'static const unsigned int %sIdx_builtin\[\]\s*=\s*\{'
                      % table, text)
        close = text.index('};', m.end())
        text = (text[:m.start()]
                + 'static const unsigned int %sSlot_builtin[] = {' % table
                + eol.join(body) + eol + text[close:])

        text = text.replace('const unsigned int* %sIdx = %sIdx_builtin;'
                            % (table, table),
                            'const unsigned int* %sSlot = %sSlot_builtin;'
                            % (table, table))

        htext = htext.replace('extern const unsigned int* %sIdx;' % table,
                              'extern const unsigned int* %sSlot;' % table)
        htext = re.sub(r'enum \{ %sIdx_COUNT = \d+ \};' % table,
                       'enum { %sSlot_COUNT = %d };' % (table, len(off)),
                       htext)

        print('  %-18s Idx %d칸 -> Slot %d칸' % (table, len(idx), len(off)))

    #슬롯 수가 곧 cmf 표의 칸 수다. 서로 다른 자료 수가 아니다.
    htext = re.sub(r'CMF_BUILTIN_COUNT = \d+',
                   'CMF_BUILTIN_COUNT = %d' % len(slots), htext)

    if bad:
        sys.stderr.write('%d개가 어긋난다. 아무것도 안 쓴다.\n' % bad)
        return 1

    if not args.write:
        print('  (실제로 쓰려면 --write)')
        return 0

    io.open(CPP, 'w', encoding='utf-8-sig', newline='').write(text)
    io.open(H, 'w', encoding='utf-8-sig', newline='').write(htext)
    print('  CmfBlob.{h,cpp} 고쳤다')
    return 0


if __name__ == '__main__':
    sys.exit(main())
