# -*- coding: utf-8 -*-
"""데이터가 바뀌었으면 팩을 다시 낸다. 빌드 앞에 붙여 쓴다.

[왜 필요한가]
게임은 Resources/data/content.pack 을 읽는다. 내장 배열(Classes/Data/*.cpp)은
팩이 없거나 깨졌을 때만 쓰인다. 그래서 데이터를 고치고 빌드만 하면

    EnemyData.cpp 를 고쳤다 -> 빌드했다 -> 실행했다 -> 안 바뀌었다

는 일이 벌어진다. 팩이 옛 값을 그대로 들고 있기 때문이다. 고친 사람은
자기 수정이 무시된 줄 모른다.

이 도구를 빌드 앞에 붙여 두면 그 함정이 사라진다. 데이터를 고치면 팩이
따라 바뀌고, 안 고쳤으면 아무 일도 안 한다.

[언제 다시 내나]
Classes/Data/ 의 .h/.cpp 중 하나라도 팩보다 새로우면 다시 낸다.
안 그러면 곧바로 끝난다(1초 안).

다시 내는 데는 20초쯤 걸린다. 데이터 .cpp 를 전부 컴파일해서 "컴파일러가
계산해 둔 값"을 받아 적기 때문이다. 파이썬으로 값을 해석하지 않는 대가다.

    python tools/content/build_pack.py           #바뀌었으면 낸다
    python tools/content/build_pack.py --force   #무조건 낸다
    python tools/content/build_pack.py --check   #내지 않고 상태만 본다
"""
import argparse
import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT

ROOT = CT.ROOT
DATA = os.path.join(CT.CLASSES, 'Data')
PACK = os.path.join(ROOT, 'Resources', 'data', 'content.pack')

#팩을 만드는 쪽이 아니라 "쓰는 쪽"이라 팩에 안 들어가는 것들.
SKIP = ('DataPack.cpp', 'DataCount.cpp', 'DataPackCheck.cpp',
        'CmfLink.cpp', 'MapLink.cpp')


def bases():
    """팩에 넣을 데이터 묶음 이름."""
    out = []

    for n in sorted(os.listdir(DATA)):
        if n.endswith('.cpp') and n not in SKIP:
            out.append(os.path.splitext(n)[0])

    return out


def newest_source():
    """Classes/Data 안에서 가장 최근에 고쳐진 파일. (시각, 이름)"""
    best = (0, None)

    for n in sorted(os.listdir(DATA)):
        if not (n.endswith('.h') or n.endswith('.cpp')):
            continue

        #생성물이다. 이것 때문에 다시 낼 필요는 없다.
        if n == 'DataList.h':
            continue

        t = os.path.getmtime(os.path.join(DATA, n))

        if t > best[0]:
            best = (t, n)

    return best


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--force', action='store_true', help='무조건 다시 낸다')
    ap.add_argument('--check', action='store_true', help='내지 않고 상태만 본다')
    args = ap.parse_args()

    src_time, src_name = newest_source()
    have = os.path.isfile(PACK)
    pack_time = os.path.getmtime(PACK) if have else 0

    if not have:
        why = '팩이 없다'
    elif src_time > pack_time:
        why = '%s 가 팩보다 새롭다' % src_name
    else:
        why = None

    if args.check:
        print('팩이 최신이다' if why is None else '다시 내야 한다 : %s' % why)
        return 1 if why else 0

    if why is None and not args.force:
        print('데이터가 그대로다. 팩을 다시 내지 않는다.')
        return 0

    print('팩을 다시 낸다 : %s' % (why or '--force'))

    cmd = [sys.executable, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                        'make_pack.py')] + bases()
    r = subprocess.run(cmd, cwd=ROOT)

    if r.returncode:
        sys.stderr.write('팩을 못 냈다. 빌드를 멈춘다.\n')
        return r.returncode

    return 0


if __name__ == '__main__':
    sys.exit(main())
