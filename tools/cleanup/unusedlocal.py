# -*- coding: utf-8 -*-
"""컴파일러가 미사용이라고 지목한 지역변수를 지운다.

MSBuild /W4 로그의 C4101(선언만 하고 안 씀)과 C4189(초기화만 하고 안 씀)를 먹는다.
컴파일러가 짚어준 것이라 "안 쓴다"는 사실 자체는 확실하지만, 지우는 것이
안전한지는 별개다. 아래 셋은 자동으로 지우지 않고 목록으로만 남긴다.

1. 초기화식에 함수 호출이 있는 것
   int n = SetFoo();  에서 변수를 지우면 SetFoo() 호출까지 사라진다.
   값을 안 쓸 뿐 부수효과가 필요한 코드일 수 있다.
2. 같은 함수 안에서 그 이름이 또 나오는 것
   지금 빌드에서만 죽은 #ifdef 가지 안에서 쓰이는 경우다. 지우면 다른
   빌드 구성이 깨진다. 이 프로젝트는 안드로이드/iOS/리눅스도 같이 만든다.
3. 선언 모양을 못 알아본 것 (for문 초기화, 여러 줄 선언 등)

한 줄에 여러 개가 선언된 경우(int i, j, k;)는 해당 이름만 빼낸다.
"""
import io, os, re, sys

WARN = re.compile(r'\\Classes\\([\w.]+)\((\d+),\d+\): warning (C4101|C4189): \'(\w+)\'')

#선언 한 줄을 통째로 지워도 되는 모양: "타입 이름;" 또는 "타입 이름 = 리터럴;"
SIMPLE = re.compile(r'^\s*[\w:<>,\s\*&]+?\b%s\s*(=\s*[^;()]*)?;\s*$')


def funcRange(lines, idx):
    """idx가 속한 함수의 줄 범위. 이 코드베이스는 함수가 1열에서 시작한다."""
    start = 0

    for i in range(idx, -1, -1):
        if lines[i] is not None and lines[i].startswith('{'):
            start = i
            break

    end = len(lines) - 1

    for i in range(idx, len(lines)):
        if lines[i] is not None and lines[i].startswith('}'):
            end = i
            break

    return start, end


def parseLog(path):
    """{파일: {줄번호: set(이름)}}"""
    hit = {}

    for line in io.open(path, encoding='utf-8', errors='replace'):
        m = WARN.search(line)

        if not m:
            continue

        name, num, code, var = m.group(1), int(m.group(2)), m.group(3), m.group(4)
        hit.setdefault(name, {}).setdefault(num, set()).add(var)

    return hit


def dropName(text, var):
    """'int i, j, k;'에서 var만 뺀다. 못 빼면 None."""
    #선언부와 나머지를 가른다.
    m = re.match(r'^(\s*)([\w:<>\s\*&]+?)\s+(.+);(\s*(?://.*)?)$', text)

    if not m:
        return None

    indent, decl, body, tail = m.groups()

    #쉼표로 나눈다. 괄호/대괄호 안의 쉼표는 건드리면 안 된다.
    parts = []
    depth = 0
    cur = ''

    for c in body:
        if c in '([{':
            depth += 1
        elif c in ')]}':
            depth -= 1

        if c == ',' and depth == 0:
            parts.append(cur)
            cur = ''
        else:
            cur += c

    parts.append(cur)

    if len(parts) < 2:
        return None

    keep = [p for p in parts if not re.match(r'^\s*\*?\s*%s\s*(=|\[|$)' % var, p)]

    if len(keep) == len(parts):
        return None	#못 찾았다

    if not keep:
        return ''	#전부 지워졌다 - 줄째로 없앤다

    return '%s%s %s;%s' % (indent, decl, ','.join(keep).strip(), tail)


def run(logPath, dryRun=False):
    hit = parseLog(logPath)
    removed = 0
    skipped = []

    for fname in sorted(hit):
        path = os.path.join('Classes', fname)

        if not os.path.exists(path):
            continue

        text = io.open(path, encoding='utf-8-sig').read()
        lines = text.split('\n')
        changed = 0

        #뒤에서부터 고쳐야 줄번호가 안 밀린다.
        for num in sorted(hit[fname], reverse=True):
            idx = num - 1

            if idx >= len(lines):
                continue

            line = lines[idx]

            for var in sorted(hit[fname][num]):
                why = None

                #1. 초기화식에 호출이 있으면 부수효과가 있을 수 있다.
                init = re.search(r'\b%s\s*=\s*([^;]*)' % var, line)

                if init and '(' in init.group(1):
                    why = '초기화에 호출'

                #2. 같은 함수 안에서 또 쓰이면 죽은 #ifdef 가지 안일 수 있다.
                if why is None:
                    a, b = funcRange(lines, idx)
                    uses = 0

                    for i in range(a, b + 1):
                        if i == idx or lines[i] is None:
                            continue
                        uses += len(re.findall(r'\b%s\b' % var, lines[i]))

                    if uses:
                        why = '함수 안 다른 곳에서 %d번 등장' % uses

                if why is None:
                    #여러 개를 한 줄에 선언한 경우를 먼저 본다. 이걸 뒤로 미루면
                    #"int i, j;"에서 j만 죽었을 때 SIMPLE이 줄 전체에 걸려
                    #살아 있는 i의 선언까지 날아간다.
                    new = dropName(line, var)

                    if new is None:
                        if re.match(SIMPLE.pattern % re.escape(var), line):
                            lines[idx] = None	#선언이 하나뿐이라 줄째로 삭제
                            changed += 1
                            removed += 1
                            break

                        why = '선언 모양을 못 읽음'
                    elif new == '':
                        lines[idx] = None
                        changed += 1
                        removed += 1
                        break
                    else:
                        lines[idx] = new
                        line = new
                        changed += 1
                        removed += 1
                        continue

                skipped.append('%s:%d %s (%s)  %s'
                    % (fname, num, var, why, line.strip()[:70]))

        if changed and not dryRun:
            out = [l for l in lines if l is not None]
            io.open(path, 'w', encoding='utf-8-sig',
                newline='\r\n').write('\n'.join(out))

        if changed:
            print('  %-30s %d개' % (fname, changed))

    print('지운 것 %d개 / 보류 %d개' % (removed, len(skipped)))

    return skipped


if __name__ == '__main__':
    log = [a for a in sys.argv[1:] if not a.startswith('--')][0]
    skipped = run(log, '--dry' in sys.argv)

    #콘솔이 cp949라 한글이 깨진다. 보류 목록은 파일로 남긴다.
    out = [a.split('=', 1)[1] for a in sys.argv[1:] if a.startswith('--out=')]

    if out:
        io.open(out[0], 'w', encoding='utf-8').write('\n'.join(skipped))
        print('보류 목록 -> %s' % out[0])
