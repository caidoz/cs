# -*- coding: utf-8 -*-
"""옛 드로우 API가 박제된 주석을 걷어낸다.

DrawImage/MemRect 류의 시그니처에서 cvtDest/cvtLayer/buffering 인자가 빠진 지
오래라, 이 이름이 들어 있는 주석은 되살려도 컴파일이 안 되는 확정된 죽은 코드다.
판단이 필요 없으므로 기계적으로 지운다.

주석만 건드린다. 살아 있는 코드에도 같은 이름이 쓰이므로(DrawBuffer의 매개변수가
cvtDest다) 문자열과 주석을 제대로 갈라 읽어야 한다. 정규식으로 훑으면
문자열 안의 "//"나 코드 중간의 "/*"에 걸려 멀쩡한 줄을 날린다.
"""
import io, os, re, sys

DEAD = re.compile(r'\b(cvtDest|cvtLayer|buffering)\b')

CODE, LINE, BLOCK, STR, CHR = range(5)


def spans(text):
    """(시작, 끝, 주석인가) 목록. 문자열/문자 리터럴을 건너뛴다."""
    out = []
    state = CODE
    i = 0
    n = len(text)
    start = 0

    while i < n:
        c = text[i]
        nxt = text[i + 1] if i + 1 < n else ''

        if state == CODE:
            if c == '/' and nxt == '/':
                start = i
                state = LINE
                i += 2
                continue
            if c == '/' and nxt == '*':
                start = i
                state = BLOCK
                i += 2
                continue
            if c == '"':
                state = STR
            elif c == "'":
                state = CHR
            i += 1
            continue

        if state == LINE:
            if c == '\n':
                out.append((start, i, True))	#줄바꿈은 남긴다
                state = CODE
            i += 1
            continue

        if state == BLOCK:
            if c == '*' and nxt == '/':
                out.append((start, i + 2, True))
                state = CODE
                i += 2
                continue
            i += 1
            continue

        #문자열/문자 리터럴. 이스케이프를 건너뛴다.
        if c == '\\':
            i += 2
            continue
        if (state == STR and c == '"') or (state == CHR and c == "'"):
            state = CODE
        i += 1

    if state == LINE:	#파일이 개행 없이 끝난 경우
        out.append((start, n, True))

    return out


def strip(text):
    """지울 주석을 빼고 돌려준다. (새 텍스트, 지운 주석 수)"""
    kill = [s for s in spans(text) if DEAD.search(text[s[0]:s[1]])]

    if not kill:
        return text, 0

    #뒤에서부터 잘라야 앞쪽 오프셋이 안 밀린다.
    for a, b in [(s[0], s[1]) for s in reversed(kill)]:
        head = text[:a]
        tail = text[b:]

        #주석만 있던 줄은 줄째로 없앤다. 앞에 코드가 있으면 그 코드는 남긴다.
        lineStart = head.rfind('\n') + 1

        if head[lineStart:].strip() == '':
            #뒤쪽도 줄 끝까지 비어 있으면 줄바꿈까지 같이 가져간다.
            m = re.match(r'[ \t]*\r?\n', tail)
            if m:
                head = head[:lineStart]
                tail = tail[m.end():]
        else:
            head = head.rstrip(' \t')	#코드 뒤에 붙어 있던 공백 정리

        text = head + tail

    return text, len(kill)


def run(paths, dryRun=False):
    total = 0
    lines = 0

    for path in paths:
        old = io.open(path, encoding='utf-8-sig').read()
        new, cnt = strip(old)

        if not cnt:
            continue

        gone = old.count('\n') - new.count('\n')
        total += cnt
        lines += gone

        print('  %-34s 주석 %3d개, %4d줄' % (os.path.basename(path), cnt, gone))

        if not dryRun:
            #저장소가 CRLF다. 기본값으로 쓰면 LF가 되어 파일 전체가 바뀐 것처럼 보인다.
            io.open(path, 'w', encoding='utf-8-sig', newline='\r\n').write(new)

    print('합계 주석 %d개, %d줄' % (total, lines))


if __name__ == '__main__':
    import glob

    files = sorted(glob.glob('Classes/*.cpp')) + sorted(glob.glob('Classes/*.h'))
    run(files, '--dry' in sys.argv)
