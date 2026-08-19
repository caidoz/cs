# -*- coding: utf-8 -*-
"""cmfVar 를 sizeof 식에서 실제 숫자로 굳힌다.

[왜]
cmfVar 는 이렇게 정의돼 있다.

    static const unsigned short cmfVar_builtin[] = {
        sizeof(c0MI) / 4, sizeof(c1MI) / 4, ...
    };

c0MI 는 Classes/Cmf/c0.h 의 배열이다. 그 배열을 blob 으로 옮기고 헤더에서
지우면 이 식이 컴파일되지 않는다. 더 나쁜 경우도 있다. 배열을 포인터로
바꾸면 sizeof 가 4를 주므로 값이 조용히 전부 1이 된다. cmfMove 가 실제로
그렇게 깨졌고, 아무도 안 읽어서 드러나지 않았다.

[하는 일]
배열이 아직 살아 있을 때 컴파일러에게 값을 물어, 숫자로 바꿔 적는다.
파이썬으로 sizeof 를 흉내내지 않는다.

    python tools/content/freeze_cmfvar.py
    python tools/content/freeze_cmfvar.py --write
"""
import argparse
import io
import os
import re
import shutil
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT
import dump_ids as D

ROOT = CT.ROOT
CLASSES = CT.CLASSES
DATA = os.path.join(CLASSES, 'Data')
CPP = os.path.join(DATA, 'CmfData.cpp')

NAME = 'cmfVar'

MAIN = r'''
#include "Cmf.h"
#include "Data/CmfData.h"
#include <stdio.h>

int main(void)
{
    int i;

    for (i = 0; i < %s_COUNT; i++)
        printf("%%d\n", (int)%s[i]);

    return 0;
}
''' % (NAME, NAME)


def ask():
    vcvars = D.find_vs()

    if not vcvars:
        sys.stderr.write('Visual Studio를 못 찾았다\n')
        return None

    work = tempfile.mkdtemp(prefix='freeze_')

    try:
        src = os.path.join(work, 'main.cpp')

        with open(src, 'w', encoding='utf-8') as fp:
            fp.write(MAIN)

        objdir = os.path.join(ROOT, 'proj.win32', 'Debug.win32')
        objs = [os.path.join(objdir, os.path.splitext(n)[0] + '.obj')
                for n in sorted(os.listdir(DATA))
                if n.endswith('.cpp') and n not in
                ('DataPack.cpp', 'DataCount.cpp', 'DataPackCheck.cpp',
                 'CmfLink.cpp', 'MapLink.cpp', 'MapBlob.cpp')]

        missing = [o for o in objs if not os.path.isfile(o)]

        if missing:
            sys.stderr.write('%s 가 없다. 먼저 win32를 빌드하라.\n' % missing[0])
            return None

        cmd = ('call "%s" >nul 2>&1 && cl /nologo /EHsc /utf-8 /W0 /MDd /D_DEBUG '
               '/I "%s" "%s" %s /Fe:"%s"'
               % (vcvars, CLASSES, src, ' '.join('"%s"' % o for o in objs),
                  os.path.join(work, 'a.exe')))

        r = subprocess.run(cmd, shell=True, cwd=work,
                           stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

        if r.returncode:
            sys.stderr.write(r.stdout.decode('mbcs', 'replace'))
            return None

        r = subprocess.run([os.path.join(work, 'a.exe')],
                           stdout=subprocess.PIPE)

        return [int(x) for x in r.stdout.decode().split()]
    finally:
        shutil.rmtree(work, ignore_errors=True)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    vals = ask()

    if vals is None:
        return 1

    print('%s : %d칸, 서로 다른 값 %d가지' % (NAME, len(vals), len(set(vals))))
    print('  앞 12개 : %s' % vals[:12])

    if len(set(vals)) == 1:
        sys.stderr.write('값이 전부 같다. 이미 깨진 뒤일 수 있다. 멈춘다.\n')
        return 1

    text = io.open(CPP, encoding='utf-8-sig', newline='').read()
    eol = '\r\n' if '\r\n' in text else '\n'

    m = re.search(r'^static const unsigned short %s_builtin\[\]\s*=\s*\{'
                  % NAME, text, re.M)

    if not m:
        sys.stderr.write('%s_builtin 을 못 찾았다\n' % NAME)
        return 1

    close = text.index('};', m.end())

    body = [eol + '\t//sizeof(c0MI) / 4 같은 식이었다. 그 배열이 blob 으로 옮겨가',
            '\t//헤더에서 사라지므로, 컴파일러가 계산한 값을 그대로 굳혀 둔다.',
            '\t//tools/content/freeze_cmfvar.py 가 적었다.']

    for a in range(0, len(vals), 16):
        body.append('\t' + ', '.join(str(v) for v in vals[a:a + 16]) + ',')

    out = text[:m.end()] + eol.join(body) + eol + text[close:]

    if not args.write:
        print('  (실제로 쓰려면 --write)')
        return 0

    io.open(CPP, 'w', encoding='utf-8-sig', newline='').write(out)
    print('  CmfData.cpp 에 숫자로 적었다')
    return 0


if __name__ == '__main__':
    sys.exit(main())
