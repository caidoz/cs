# -*- coding: utf-8 -*-
"""배포용 매니페스트를 만들고, 흉내낼 CDN 폴더를 꾸민다.

[매니페스트]
어떤 파일이 어떤 판인지 적은 표다. 클라이언트는 이걸 받아 자기 것과 견주고
달라진 파일만 받는다(Classes/Content.cpp).

    #content 1
    version <탭> 2026082001
    data/content.pack <탭> 2352372 <탭> 3f2a91c04b7e5d18
    res/aa.png <탭> 12345 <탭> a1b2c3d4e5f60718

지문은 FNV-1a 64비트다. CRC-32 를 쓰면 안 된다 — fnv1a64() 주석을 보라.
크기만 보면 내용이 바뀐 것을 못 잡는다.

[쓰기]
    python tools/content/make_manifest.py                 #Resources 를 훑어 만든다
    python tools/content/make_manifest.py --stage <폴더>  #그 폴더에 CDN 을 꾸민다
    python tools/content/make_manifest.py --only data     #데이터만

--stage 는 매니페스트에 적힌 파일을 그 폴더로 복사한다. 클라이언트가
쓰기 가능 경로의 cdn/ 을 보므로, 거기에 꾸미면 갱신이 도는지 바로 볼 수 있다.
"""
import argparse
import os
import shutil
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT

ROOT = CT.ROOT
RES = os.path.join(ROOT, 'Resources')

#매니페스트에 담을 것. 앱에 딸려오지만 갈아끼울 수 있는 것들이다.
#fonts 는 넣지 않는다. 글꼴이 바뀌면 어차피 앱을 새로 올려야 한다.
GROUPS = {
    'data': ['data'],
    'res': ['res'],
    'sounds': ['sounds'],
}


def fnv1a64(buf):
    """파일 지문. FNV-1a 64비트.

    CRC-32 를 쓰면 안 된다. 팩은 끝에 자기 CRC-32 를 담는데, 메시지 뒤에
    자기 CRC 를 붙이면 전체 CRC 가 늘 같은 값(0x2144DF1C)이 된다. 그래서
    어떤 판의 팩이든 지문이 똑같이 나오고, 바뀐 것을 크기로만 가리게 된다.
    크기가 같고 내용만 다른 팩은 못 잡는다.

    Classes/Content.cpp 의 ContentHash 와 같은 것이어야 한다.
    """
    h = 0xCBF29CE484222325

    for b in bytearray(buf):
        h ^= b
        h = (h * 0x100000001B3) & 0xFFFFFFFFFFFFFFFF

    return h


def scan(dirs):
    """(상대경로, 크기, crc) 목록. 경로는 / 로 적는다."""
    out = []

    for d in dirs:
        base = os.path.join(RES, d)

        if not os.path.isdir(base):
            continue

        for root, _sub, files in os.walk(base):
            for n in sorted(files):
                full = os.path.join(root, n)
                rel = os.path.relpath(full, RES).replace('\\', '/')

                with open(full, 'rb') as fp:
                    body = fp.read()

                out.append((rel, len(body), fnv1a64(body)))

    out.sort()
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--only', choices=sorted(GROUPS), action='append',
                    help='이 묶음만 담는다. 여러 번 줄 수 있다')
    ap.add_argument('--version', type=int, help='판번호. 안 주면 날짜+시각')
    ap.add_argument('--stage', help='이 폴더에 CDN 을 꾸민다')
    ap.add_argument('--out', help='매니페스트를 쓸 곳. 기본은 Resources/manifest.tsv')
    args = ap.parse_args()

    picked = args.only or sorted(GROUPS)
    dirs = []

    for g in picked:
        dirs.extend(GROUPS[g])

    files = scan(dirs)

    if not files:
        sys.stderr.write('담을 파일이 없다\n')
        return 1

    ver = args.version if args.version else int(time.strftime('%Y%m%d%H%M'))

    lines = ['#content 1', 'version\t%d' % ver]
    total = 0

    for rel, size, h in files:
        lines.append('%s\t%d\t%016x' % (rel, size, h))
        total += size

    text = '\n'.join(lines) + '\n'

    out = args.out or os.path.join(RES, 'manifest.tsv')

    with open(out, 'w', encoding='utf-8', newline='\n') as fp:
        fp.write(text)

    print('판 %d, 파일 %d개, %s 바이트' % (ver, len(files), format(total, ',')))
    print('  %s' % os.path.relpath(out, ROOT))

    for g in picked:
        n = sum(1 for r, _s, _c in files if r.split('/')[0] in GROUPS[g])
        print('    %-8s %d개' % (g, n))

    if not args.stage:
        return 0

    #---- CDN 흉내내기 ----
    stage = args.stage if os.path.isabs(args.stage) else os.path.join(ROOT, args.stage)

    if not os.path.isdir(stage):
        os.makedirs(stage)

    with open(os.path.join(stage, 'manifest.tsv'), 'w',
              encoding='utf-8', newline='\n') as fp:
        fp.write(text)

    #판번호만 든 파일. 클라이언트는 갱신 확인을 이것부터 한다.
    #
    #매니페스트는 32KB 인데 대개는 "안 바뀌었다"를 확인하려고 받는다.
    #유저가 백만이면 그 확인만으로 달마다 수백 GB 가 나간다. 스무 바이트짜리를
    #먼저 보게 하면 그게 거의 사라진다.
    #
    #올릴 때 캐시 설정을 나눠야 한다.
    #    version.txt   짧게(60초쯤). 늘 새것을 봐야 하니까
    #    그 밖의 파일  영원히(immutable). 주소에 지문이 붙어 있으니까
    with open(os.path.join(stage, 'version.txt'), 'w',
              encoding='utf-8', newline='\n') as fp:
        fp.write('%d\n' % ver)

    for rel, _size, _crc in files:
        dst = os.path.join(stage, rel.replace('/', os.sep))
        d = os.path.dirname(dst)

        if not os.path.isdir(d):
            os.makedirs(d)

        shutil.copyfile(os.path.join(RES, rel.replace('/', os.sep)), dst)

    print('  CDN 흉내 : %s' % stage)
    return 0


if __name__ == '__main__':
    sys.exit(main())
