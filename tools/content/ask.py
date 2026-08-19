# -*- coding: utf-8 -*-
"""상수나 식의 값을 컴파일러에게 물어본다.

    python tools/content/ask.py TOTALENEMY "sizeof(OBJECT)" TOTALOBJECT

파이썬으로 C 식을 해석하지 않는다. Def.h 를 그대로 컴파일해서 컴파일러가
계산한 값을 받아온다. enum 이 서로를 참조하고 #ifdef 가 걸려 있어서,
사람이 읽어 옮기면 틀린다.
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dump_ids as D


def main():
    exprs = sys.argv[1:]

    if not exprs:
        sys.stderr.write('물어볼 식을 적어라\n')
        return 1

    #Core.h 가 필요한 식(sizeof(OBJECT) 등)은 Def.h 만으로는 안 된다.
    got = D.ask_compiler(exprs)

    if got is None:
        return 1

    for e in exprs:
        print('%-40s = %s' % (e, got.get(e, '?')))

    return 0


if __name__ == '__main__':
    sys.exit(main())
