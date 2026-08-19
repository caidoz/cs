# -*- coding: utf-8 -*-
"""새 cmf 표가 옛 배열과 같은 값을 주는지 확인한다.

CmfRelink() 로 채운 cmfOff[i][j] 가 Classes/Cmf/c<i>.h 의 c<i>Off[j] 와
글자 하나까지 같아야 한다. 옛 배열을 지우기 전에 반드시 돌려야 한다.
지우고 나면 비교할 상대가 없어진다.

    python tools/content/verify_cmf.py
"""
import os
import re
import shutil
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT
import dump_ids as D
import pack_cmf as PC

ROOT = CT.ROOT
CLASSES = CT.CLASSES
DATA = os.path.join(CLASSES, 'Data')

MAIN = r'''
//verify_cmf.py 가 만든 임시 프로그램.
//새 표(CmfRelink 가 채운 것)와 옛 배열(Cmf/c*.h)을 하나하나 맞춰본다.
#include "Cmf.h"
#include "Data/CmfBlob.h"
#include <stdio.h>
#include <string.h>

void CmfRelink(void);

static int bad = 0;
static long cells = 0;

static void Cmp(const char* what, int id, const void* a, const void* b, int n, int esz)
{
    cells += n;

    if (memcmp(a, b, (size_t)n * esz) == 0)
        return;

    printf("  다르다 : %s[%d] (%d칸)\n", what, id, n);
    bad++;
}

//표에서 꺼낸 것과 원래 배열을 잰다. 길이는 Idx 로 잰다.
#define CMP(TABLE, IDX, OLD, ID, ESZ) \
    Cmp(#TABLE, ID, TABLE[ID], OLD, (int)(IDX[ID + 1] - IDX[ID]), ESZ)

int main(void)
{
    CmfRelink();

__BODY__

    printf("맞춰본 칸 %ld개, 다른 곳 %d개\n", cells, bad);
    return bad ? 1 : 0;
}
'''


def main():
    ids = PC.cmf_ids()
    heroes = PC.hero_ids(ids)

    #strip_cmf.py 를 이미 돌렸으면 맞춰볼 상대가 없다. 컴파일 오류를 잔뜩
    #쏟아내기 전에 여기서 알려준다.
    if not heroes:
        print('Classes/Cmf/c*.h 에 옛 배열이 없다. 이미 지운 뒤다.')
        print('이 시험은 strip_cmf.py 를 돌리기 전에만 쓸 수 있다.')
        print('지금 팩이 맞는지 보려면 check_pack.py 를 써라.')
        return 0

    body = []

    for table, suffix, ctype, _kind in PC.FAMILIES:
        #mv 는 이미 소스에서 지워서 맞춰볼 상대가 없다. 옛 팩과 대조한다
        #(verify_mv.py). 나머지 6가족만 여기서 본다.
        if suffix in PC.BY_COUNT:
            continue

        which = heroes if suffix == 'Loop60' else ids
        esz = PC.CTYPE_SIZE[ctype]
        body.append('    //---- %s ----' % table)

        for slot, i in enumerate(which):
            body.append('    CMP(%s, %sIdx, c%d%s, %d, %d);'
                        % (table, table, i, suffix, slot, esz))

        body.append('')

    work = tempfile.mkdtemp(prefix='vfycmf_')

    try:
        src = os.path.join(work, 'main.cpp')

        with open(src, 'w', encoding='utf-8') as fp:
            fp.write(MAIN.replace('__BODY__', '\n'.join(body)))

        objdir = os.path.join(ROOT, 'proj.win32', 'Debug.win32')
        objs = [os.path.join(objdir, os.path.splitext(n)[0] + '.obj')
                for n in sorted(os.listdir(DATA))
                if n.endswith('.cpp') and n not in
                ('DataPack.cpp', 'DataCount.cpp', 'DataPackCheck.cpp',
                 'MapLink.cpp', 'MapBlob.cpp')]

        missing = [o for o in objs if not os.path.isfile(o)]

        if missing:
            sys.stderr.write('%s 가 없다. 먼저 win32를 빌드하라.\n' % missing[0])
            return 2

        #DataPackCount 를 CmfLink 가 부른다. 팩 없이 도는 시험이라 -1 을 준다.
        stub = os.path.join(work, 'stub.cpp')

        with open(stub, 'w', encoding='utf-8') as fp:
            fp.write('int DataPackCount(const char*) { return -1; }\n'
                     'int gTotalCmf = 0;\n')

        vcvars = D.find_vs()
        cmd = ('call "%s" >nul 2>&1 && cl /nologo /EHsc /utf-8 /W0 /MDd /D_DEBUG '
               '/I "%s" "%s" "%s" %s /Fe:"%s"'
               % (vcvars, CLASSES, src, stub, ' '.join('"%s"' % o for o in objs),
                  os.path.join(work, 'v.exe')))

        r = subprocess.run(cmd, shell=True, cwd=work,
                           stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

        if r.returncode:
            sys.stderr.write(r.stdout.decode('mbcs', 'replace'))
            return 2

        r = subprocess.run([os.path.join(work, 'v.exe')],
                           stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        print(r.stdout.decode('utf-8', 'replace').strip())
        return r.returncode
    finally:
        shutil.rmtree(work, ignore_errors=True)


if __name__ == '__main__':
    sys.exit(main())
