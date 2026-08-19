# -*- coding: utf-8 -*-
"""팩을 클라이언트가 받아들이는지 확인한다. 게임을 띄우지 않는다.

Classes/Data/DataPackCheck.cpp 를 그대로 컴파일해 돌린다. 파이썬으로 규칙을
다시 구현하지 않는다. 그러면 둘이 어긋날 수 있고, 어긋나면 이 시험은 아무것도
증명하지 못한다.

    python tools/content/check_pack.py Resources/data/content.pack
    python tools/content/check_pack.py Resources/data/content.pack.grown
"""
import argparse
import os
import shutil
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT
import dump_ids as D

ROOT = CT.ROOT
OBJDIR = os.path.join(ROOT, 'proj.win32', 'Debug.win32')

MAIN = r'''
//make_pack 계열이 만드는 임시 프로그램. 팩을 검사만 한다.
#include "Config/Capacity.h"
#include "Data/DataPack.h"
#include <stdio.h>
#include <stdlib.h>

static const char* KEYNAME[] = {
    "(고정)", "몬스터", "동료", "스킬", "성", "맵"
};

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("팩 경로를 달라\n");
        return 2;
    }

    FILE* fp = fopen(argv[1], "rb");

    if (!fp) {
        printf("못 연다: %s\n", argv[1]);
        return 2;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    unsigned char* buf = (unsigned char*)malloc((size_t)size);

    if (fread(buf, 1, (size_t)size, fp) != (size_t)size) {
        printf("다 못 읽었다\n");
        return 2;
    }

    fclose(fp);

    char why[8192];
    int keyCount[DPK_KEY_MAX];
    int i;

    why[0] = 0;

    int bad = DataPackCheck(buf, size, keyCount, why, (int)sizeof(why));

    printf("클라이언트 abi %08x\n", DataPackAbi());
    printf("용량 : 몬스터 %d, 동료 %d, 스킬 %d, 성 %d, 맵 %d\n",
        CAP_ENEMY, CAP_CREW, CAP_SKILL, CAP_CASTLE, CAP_MAP);

    if (bad) {
        printf("거부 : 어긋난 항목 %d개\n%s", bad, why);
        return 1;
    }

    printf("받아들인다.\n");

    for (i = 1; i < DPK_KEY_MAX; i++) {
        if (keyCount[i] >= 0)
            printf("  %s %d개\n", KEYNAME[i], keyCount[i]);
    }

    return 0;
}
'''


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('pack')
    args = ap.parse_args()

    pack = args.pack if os.path.isabs(args.pack) else os.path.join(ROOT, args.pack)

    if not os.path.isfile(pack):
        sys.stderr.write('%s 가 없다\n' % pack)
        return 2

    vcvars = D.find_vs()

    if not vcvars:
        sys.stderr.write('Visual Studio를 못 찾았다\n')
        return 2

    work = tempfile.mkdtemp(prefix='chkpack_')

    try:
        src = os.path.join(work, 'main.cpp')

        with open(src, 'w', encoding='utf-8') as fp:
            fp.write(MAIN)

        bat = os.path.join(work, 'go.bat')

        with open(bat, 'w', encoding='mbcs') as fp:
            fp.write('@echo off\r\n')
            fp.write('call "%s" >nul\r\n' % vcvars)
            fp.write('cd /d "%s"\r\n' % work)
            #DataList.h 가 데이터 헤더를 전부 끌어온다. 그 안의 포인터 표
            #(cmfMoveInfo, mapPtr 등)가 Data/*.cpp 의 배열을 참조하므로 그것들도
            #링크해야 한다. 다시 컴파일하면 몇 분씩 걸리니, MSBuild가 이미 만들어
            #둔 .obj 를 쓴다. 없으면 먼저 빌드하라고 알려준다.
            #
            #포인터 표를 헤더 밖으로 빼면 이 의존이 사라진다. 그때 정리하자.
            objs = [os.path.join(OBJDIR, os.path.splitext(n)[0] + '.obj')
                    for n in sorted(os.listdir(os.path.join(CT.CLASSES, 'Data')))
                    if n.endswith('.cpp') and n not in
                    ('DataPack.cpp', 'DataCount.cpp', 'DataPackCheck.cpp')]

            missing = [o for o in objs if not os.path.isfile(o)]

            if missing:
                sys.stderr.write('%s 가 없다. 먼저 win32를 빌드하라.\n' % missing[0])
                return 2

            #/MDd /D_DEBUG : 가져다 쓰는 .obj 가 Debug 빌드라 런타임을 맞춰야
            #한다. 안 맞추면 _ITERATOR_DEBUG_LEVEL 불일치로 링크가 안 된다.
            fp.write('cl /nologo /EHsc /utf-8 /MDd /D_DEBUG /I"%s" "%s" "%s" %s /Fe:chk.exe >build.log 2>&1\r\n'
                     % (CT.CLASSES, src,
                        os.path.join(CT.CLASSES, 'Data', 'DataPackCheck.cpp'),
                        ' '.join('"%s"' % o for o in objs)))
            fp.write('if not exist chk.exe (type build.log & exit /b 2)\r\n')
            #cmd 가 현재 디렉터리를 실행 경로에서 안 찾는 설정일 수 있다.
            fp.write('.\\chk.exe "%s"\r\n' % pack)
            fp.write('exit /b %%errorlevel%%\r\n')

        r = subprocess.run([bat], capture_output=True)
        out = r.stdout.decode('utf-8', 'replace')
        err = r.stderr.decode('utf-8', 'replace')

        print(out.strip())

        if err.strip():
            sys.stderr.write(err)

        return r.returncode
    finally:
        shutil.rmtree(work, ignore_errors=True)


if __name__ == '__main__':
    sys.exit(main())
