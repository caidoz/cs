# -*- coding: utf-8 -*-
"""C++ 몇 개를 컴파일해서 돌린다. 윈도우와 맥/리눅스를 둘 다 본다.

[왜 있나]
이 폴더의 도구들은 "파이썬으로 값을 해석하지 않는다"는 규칙을 지킨다. 값에
CMF_SNAIL, TSIZE * 3 같은 이름과 식이 섞여 있어서 다시 해석하면 언젠가
반드시 어긋난다. 그래서 소스를 그대로 컴파일해 "컴파일러가 이미 계산해 둔
값"을 받아 적는다.

그러다 보니 도구마다 컴파일러를 부르는데, 그게 전부 cl.exe(윈도우) 였다.
맥으로 넘어가면 데이터를 고쳐도 팩을 다시 낼 수가 없다. 팩이 옛 값을 든 채로
빌드되고, 고친 사람은 자기 수정이 무시된 줄 모른다.

여기 한 곳에 모아 두고 각 도구가 이걸 쓴다.

[쓰는 법]
    exe = cc.build(srcs, includes, workdir)      #실패하면 None
    out = cc.run(exe, args)                      #실패하면 None
"""
import os
import subprocess
import sys

IS_WIN = (os.name == 'nt')

#윈도우에서 찾아볼 Visual Studio 자리.
VS_CANDIDATES = [
    r'C:\Program Files\Microsoft Visual Studio\2022\Community',
    r'C:\Program Files\Microsoft Visual Studio\2022\Professional',
    r'C:\Program Files\Microsoft Visual Studio\2022\Enterprise',
    r'C:\Program Files\Microsoft Visual Studio\2022\BuildTools',
    r'C:\Program Files (x86)\Microsoft Visual Studio\2019\Community',
    r'C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional',
    r'C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools',
]


def find_vs():
    for p in VS_CANDIDATES:
        bat = os.path.join(p, r'VC\Auxiliary\Build\vcvars32.bat')

        if os.path.isfile(bat):
            return bat

    return None


def find_clang():
    """맥/리눅스에서 쓸 C++ 컴파일러."""
    for c in ('clang++', 'g++', 'c++'):
        try:
            r = subprocess.run([c, '--version'],
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

            if r.returncode == 0:
                return c
        except OSError:
            continue

    return None


def build(srcs, includes, work, name='a'):
    """srcs 를 컴파일해 실행 파일을 만든다. 만든 경로를 돌려준다.

    includes : -I 로 넣을 폴더 목록
    work     : 임시로 쓸 폴더
    """
    exe = os.path.join(work, name + ('.exe' if IS_WIN else ''))

    if IS_WIN:
        vcvars = find_vs()

        if not vcvars:
            sys.stderr.write(
                'Visual Studio를 못 찾았다. tools/content/cc.py 의 '
                'VS_CANDIDATES 에 경로를 추가하라.\n')
            return None

        inc = ' '.join('/I "%s"' % i for i in includes)
        args = ' '.join('"%s"' % s for s in srcs)
        cmd = ('call "%s" >nul 2>&1 && cl /nologo /EHsc /utf-8 /W0 %s %s /Fe:"%s"'
               % (vcvars, inc, args, exe))

        r = subprocess.run(cmd, shell=True, cwd=work,
                           stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    else:
        cxx = find_clang()

        if not cxx:
            sys.stderr.write('C++ 컴파일러를 못 찾았다(clang++/g++).\n')
            return None

        #-fno-ms-extensions 같은 것은 안 넣는다. 소스가 표준 C++ 이다.
        #소스가 UTF-8(BOM 포함)이라 clang 은 그대로 읽는다.
        cmd = [cxx, '-std=c++11', '-w', '-fsigned-char', '-o', exe]

        for i in includes:
            cmd += ['-I', i]

        cmd += list(srcs)

        r = subprocess.run(cmd, cwd=work,
                           stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    if r.returncode:
        sys.stderr.write(r.stdout.decode('utf-8', 'replace'))
        return None

    return exe


def run(exe, args=None):
    """만든 실행 파일을 돌린다. 표준출력을 bytes 로 돌려준다."""
    cmd = [exe] + list(args or [])
    r = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    if r.returncode:
        sys.stderr.write(r.stdout.decode('utf-8', 'replace'))
        return None

    return r.stdout
