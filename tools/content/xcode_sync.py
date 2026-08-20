# -*- coding: utf-8 -*-
"""Classes 밑의 .cpp 를 Xcode 프로젝트에 등록한다.

[왜 필요한가]
win32 는 vcxproj 에, 안드로이드는 Android.mk 에 파일을 적어 왔다. 그런데
Xcode 는 project.pbxproj 에 파일을 하나하나 적어야 하고, 이번에 만든 .cpp
가 거기 하나도 안 들어가 있었다. 그대로 pull 하면 맥에서 링크가 안 된다.

    Data/*.cpp 31개   팩에 들어갈 데이터와 표 채우기
    Content.cpp       콘텐츠 배포

[하는 일]
pbxproj 의 네 곳을 고친다.

    PBXFileReference      파일이 있다는 선언
    PBXBuildFile          "이 파일을 컴파일한다" (타겟마다 하나씩)
    그룹 children         Xcode 창에 보이는 자리
    PBXSourcesBuildPhase  실제 컴파일 목록 (타겟마다)

이미 있는 파일은 건드리지 않는다. 여러 번 돌려도 같은 결과다.

    python tools/content/xcode_sync.py
    python tools/content/xcode_sync.py --write
"""
import argparse
import hashlib
import io
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT

ROOT = CT.ROOT
PBX = os.path.join(ROOT, 'proj.ios_mac', 'cs.xcodeproj', 'project.pbxproj')


def new_id(seed):
    """pbxproj 가 쓰는 24자리 16진수 id. 이름에서 만들어 두 번 돌려도 같게 한다."""
    return hashlib.sha1(seed.encode('utf-8')).hexdigest()[:24].upper()


def want_files():
    """등록해야 할 (그룹, 파일이름, 경로) 목록."""
    out = []
    d = os.path.join(CT.CLASSES, 'Data')

    for n in sorted(os.listdir(d)):
        if n.endswith('.cpp'):
            out.append(('Data', n))

    for n in ('Content.cpp',):
        if os.path.isfile(os.path.join(CT.CLASSES, n)):
            out.append(('Classes', n))

    return out


def group_id(text, name):
    """그룹 블록의 id 를 찾는다."""
    m = re.search(r'([0-9A-F]{24}) /\* %s \*/ = \{\s*isa = PBXGroup;' % name, text)

    if not m:
        raise SystemExit('%s 그룹을 못 찾았다' % name)

    return m.group(1)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    t = io.open(PBX, encoding='utf-8', newline='').read()
    eol = '\r\n' if '\r\n' in t else '\n'

    #소스 컴파일 단계가 타겟마다 하나씩 있다(보통 iOS 와 Mac).
    phases = [m.start() for m in re.finditer(r'isa = PBXSourcesBuildPhase;', t)]
    print('소스 컴파일 단계 %d개 (타겟 수)' % len(phases))

    todo = [(g, n) for g, n in want_files() if ('/* %s */' % n) not in t]

    if not todo:
        print('전부 이미 등록돼 있다.')
        return 0

    print('등록할 파일 %d개' % len(todo))

    for g, n in todo:
        print('  %-10s %s' % (g, n))

    if not args.write:
        print('  (실제로 쓰려면 --write)')
        return 0

    #---- 1. PBXFileReference ----
    refs = []

    for g, n in todo:
        fid = new_id('ref:' + g + '/' + n)
        refs.append('\t\t%s /* %s */ = {isa = PBXFileReference; fileEncoding = 4; '
                    'lastKnownFileType = sourcecode.cpp.cpp; path = %s; '
                    'sourceTree = "<group>"; };' % (fid, n, n))

    anchor = '/* End PBXFileReference section */'
    t = t.replace(anchor, eol.join(refs) + eol + anchor, 1)

    #---- 2. PBXBuildFile (타겟마다 하나씩) ----
    builds = []

    for g, n in todo:
        fid = new_id('ref:' + g + '/' + n)

        for k in range(len(phases)):
            bid = new_id('build%d:%s/%s' % (k, g, n))
            builds.append('\t\t%s /* %s in Sources */ = {isa = PBXBuildFile; '
                          'fileRef = %s /* %s */; };' % (bid, n, fid, n))

    anchor = '/* End PBXBuildFile section */'
    t = t.replace(anchor, eol.join(builds) + eol + anchor, 1)

    #---- 3. 그룹 children ----
    for gname in ('Data', 'Classes'):
        mine = [n for g, n in todo if g == gname]

        if not mine:
            continue

        gid = group_id(t, gname)
        m = re.search(r'%s /\* %s \*/ = \{.*?children = \(' % (gid, gname), t, re.S)
        at = m.end()
        add = ''.join(eol + '\t\t\t\t%s /* %s */,'
                      % (new_id('ref:' + gname + '/' + n), n) for n in mine)
        t = t[:at] + add + t[at:]

    #---- 4. PBXSourcesBuildPhase (타겟마다) ----
    #뒤에서부터 넣어야 앞쪽 위치가 안 밀린다.
    for k in range(len(phases) - 1, -1, -1):
        m = re.compile(r'isa = PBXSourcesBuildPhase;.*?files = \(', re.S)
        spots = [mm for mm in m.finditer(t)]
        at = spots[k].end()
        add = ''.join(eol + '\t\t\t\t%s /* %s in Sources */,'
                      % (new_id('build%d:%s/%s' % (k, g, n)), n) for g, n in todo)
        t = t[:at] + add + t[at:]

    io.open(PBX, 'w', encoding='utf-8', newline='').write(t)
    print('  project.pbxproj 에 %d개 등록했다' % len(todo))
    return 0


if __name__ == '__main__':
    sys.exit(main())
