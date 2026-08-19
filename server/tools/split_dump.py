# -*- coding: utf-8 -*-
"""insamdb 덤프 파일을 테이블별 TSV로 쪼개고 MariaDB용 LOAD DATA 문을 만든다.

형식은 server/dumpformat.md 참고. 쪼개면서 규격 검증도 한다.

    python server/tools/split_dump.py save.dat --out /tmp/imp
    mysql -u root insam < server/schema.sql
    mysql -u root --local-infile=1 insam < /tmp/imp/load.sql

--check 만 주면 파일을 검증만 하고 아무것도 만들지 않는다. 클라이언트가 쓴
파일이 규격에 맞는지 보는 용도다.
"""
import argparse
import os
import sys
import zlib

FORMAT_VERSION = 1

#외래키 때문에 부모가 먼저 들어가야 하는 것들. 여기 없는 표는 뒤에 붙인다.
TABLE_ORDER = [
    'account',
    'account_link',
    'player',
    'player_castle',
    'player_flag',
    'player_consumable',
    'inventory',
    'inventory_option',
    'inventory_socket',
    'hero',
    'hero_equip',
    'hero_hotkey',
    'hero_skill',
    'hero_skill_slot',
    'crew_slot',
    'quest_progress',
    'game_event',
    'calendar_day',
    'battle_session',
    'battle_enemy',
    'battle_enemy_effect',
    'pvp_house',
    'pvp_house_crew',
    'pvp_house_look',
]


class DumpError(Exception):
    pass


def parse(path):
    """덤프를 읽어 (헤더 dict, [(표이름, 컬럼들, 행들)]) 로 돌려준다."""
    with open(path, 'rb') as fp:
        raw = fp.read()

    #행 구분은 LF다. CRLF로 저장됐다면 그 시점에 이미 규격 위반이라 잡아준다.
    if b'\r\n' in raw:
        raise DumpError('행 구분이 CRLF다. LF여야 한다 (dumpformat.md 참고)')

    text = raw.decode('utf-8')
    lines = text.split('\n')

    #마지막 개행 뒤의 빈 줄은 버린다.
    if lines and lines[-1] == '':
        lines.pop()

    header = {}
    tables = []
    i = 0

    #블록 사이의 빈 줄은 읽기 좋으라고 넣는 것이라 무시한다.
    #데이터 줄은 개수(#rows)로 읽으므로 빈 줄과 헷갈릴 일이 없다.
    def skip_blank(k):
        while k < len(lines) and lines[k].strip() == '':
            k += 1
        return k

    #---- 헤더 ----
    i = skip_blank(i)

    while i < len(lines) and lines[i].startswith('#'):
        parts = lines[i].split('\t')
        key = parts[0][1:]

        if key == 'table':
            break

        header[key] = parts[1] if len(parts) > 1 else ''
        i = skip_blank(i + 1)

    if 'insamdb' not in header:
        raise DumpError('#insamdb 줄이 없다. insamdb 덤프가 아니다')

    if int(header['insamdb']) != FORMAT_VERSION:
        raise DumpError('형식 버전이 %s다. 이 도구는 %d만 안다'
                        % (header['insamdb'], FORMAT_VERSION))

    #---- 표들 ----
    while True:
        i = skip_blank(i)

        if i >= len(lines):
            break

        line = lines[i]

        if line.startswith('#end'):
            #체크섬 검증. #insamdb 줄부터 #end 직전까지가 대상이다.
            body = '\n'.join(lines[:i]) + '\n'
            want = line.split('\t')[1].strip() if '\t' in line else None

            if want:
                got = '%08x' % (zlib.crc32(body.encode('utf-8')) & 0xffffffff)
                if got.lower() != want.lower():
                    raise DumpError('체크섬이 안 맞는다. 기록=%s 계산=%s'
                                    % (want, got))
            break

        if not line.startswith('#table'):
            raise DumpError('%d번째 줄: #table이 와야 하는데 %r'
                            % (i + 1, line[:40]))

        name = line.split('\t')[1].strip()
        i += 1

        if i >= len(lines) or not lines[i].startswith('#cols'):
            raise DumpError('표 %s: #cols 줄이 없다' % name)

        cols = lines[i].split('\t')[1:]
        i += 1

        if i >= len(lines) or not lines[i].startswith('#rows'):
            raise DumpError('표 %s: #rows 줄이 없다' % name)

        count = int(lines[i].split('\t')[1])
        i += 1

        rows = lines[i:i + count]

        if len(rows) != count:
            raise DumpError('표 %s: %d행이라고 했는데 %d행뿐이다'
                            % (name, count, len(rows)))

        for n, row in enumerate(rows):
            ##rows가 실제보다 크면 다음 블록의 메타행을 데이터로 먹는다.
            #컬럼 수 오류로 흘려보내면 원인이 안 보이므로 여기서 먼저 잡는다.
            if row.startswith('#'):
                raise DumpError('표 %s: %d행이라고 했는데 %d행에서 메타행(%s)이 나왔다'
                                % (name, count, n + 1, row.split('\t')[0]))

            #컬럼 수 검증. 값 안의 탭은 \t로 이스케이프돼 있어야 하므로
            #탭으로 자른 개수가 컬럼 수와 같아야 한다.
            got = len(row.split('\t'))

            if got != len(cols):
                raise DumpError('표 %s %d행: 컬럼이 %d개여야 하는데 %d개다'
                                % (name, n + 1, len(cols), got))

        i += count
        tables.append((name, cols, rows))

    return header, tables


def order_key(name):
    return TABLE_ORDER.index(name) if name in TABLE_ORDER else len(TABLE_ORDER)


def write_out(header, tables, out_dir):
    os.makedirs(out_dir, exist_ok=True)

    tables = sorted(tables, key=lambda t: order_key(t[0]))
    stmts = []

    for name, cols, rows in tables:
        tsv = os.path.join(out_dir, name + '.tsv')

        #LOAD DATA는 파일에 데이터 줄만 있기를 바란다. 메타는 빼고 쓴다.
        with open(tsv, 'w', encoding='utf-8', newline='\n') as fp:
            for row in rows:
                fp.write(row + '\n')

        #경로는 슬래시로. 윈도우 역슬래시를 그대로 넣으면 SQL 문자열에서
        #이스케이프로 먹힌다.
        sql_path = tsv.replace('\\', '/')

        stmts.append(
            "LOAD DATA LOCAL INFILE '%s'\n"
            "  INTO TABLE `%s`\n"
            "  CHARACTER SET utf8mb4\n"
            "  FIELDS TERMINATED BY '\\t' ESCAPED BY '\\\\'\n"
            "  LINES TERMINATED BY '\\n'\n"
            "  (%s);\n"
            % (sql_path, name, ', '.join('`%s`' % c for c in cols)))

    load_sql = os.path.join(out_dir, 'load.sql')

    with open(load_sql, 'w', encoding='utf-8', newline='\n') as fp:
        fp.write('-- split_dump.py가 만든 파일. 직접 고치지 말 것.\n')
        fp.write('-- user_id=%s revision=%s schema=%s\n\n'
                 % (header.get('user', '?'), header.get('revision', '?'),
                    header.get('schema', '?')))
        fp.write('SET NAMES utf8mb4;\n')
        #같은 유저를 다시 넣을 때를 위해 트랜잭션으로 감싼다.
        fp.write('START TRANSACTION;\n\n')
        fp.write('\n'.join(stmts))
        fp.write('\nCOMMIT;\n')

    return load_sql


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('dump', help='클라이언트가 쓴 덤프 파일')
    ap.add_argument('--out', help='쪼갠 결과를 넣을 폴더')
    ap.add_argument('--check', action='store_true',
                    help='검증만 하고 파일을 만들지 않는다')
    args = ap.parse_args()

    try:
        header, tables = parse(args.dump)
    except DumpError as e:
        sys.stderr.write('덤프가 규격에 안 맞는다: %s\n' % e)
        return 1

    total = sum(len(rows) for _, _, rows in tables)
    print('형식 %s / 스키마 %s / user_id %s / revision %s'
          % (header.get('insamdb'), header.get('schema'),
             header.get('user'), header.get('revision')))
    print('표 %d개, 행 %d개' % (len(tables), total))

    for name, cols, rows in sorted(tables, key=lambda t: order_key(t[0])):
        print('  %-24s %5d행  %2d컬럼' % (name, len(rows), len(cols)))

    if args.check:
        print('검증 통과')
        return 0

    if not args.out:
        sys.stderr.write('--out 이 필요하다 (또는 --check)\n')
        return 1

    path = write_out(header, tables, args.out)
    print('만들었다: %s' % path)
    return 0


if __name__ == '__main__':
    sys.exit(main())
