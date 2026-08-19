# -*- coding: utf-8 -*-
"""데이터 팩을 만든다.

[핵심]
값의 59%가 CMF_SNAIL, TSIZE * 3 같은 이름과 식이다. 이걸 파이썬으로 해석하면
언젠가 반드시 어긋난다. 그래서 해석하지 않는다.

데이터 .cpp를 그대로 컴파일해서 "컴파일러가 이미 계산해 둔 배열"을 바이트째
써낸다. 팩의 값이 게임이 쓰던 값과 다를 수가 없다.

    python tools/content/make_pack.py EnemyData
    python tools/content/make_pack.py EnemyData --out Resources/data

[하는 일]
    1. Data/*.h 에서 포인터 선언을 긁어 목록을 만든다
    2. Classes/Data/DataList.h 를 생성한다 (로더와 덤퍼가 같이 쓰는 X매크로)
    3. 덤퍼 main을 만들어 데이터 .cpp 와 함께 컴파일하고 실행한다
    4. 나온 팩을 검증한다
"""
import argparse
import os
import re
import struct
import subprocess
import sys
import tempfile
import zlib

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT
import dump_ids

ROOT = CT.ROOT
CLASSES = CT.CLASSES
DATA = os.path.join(CLASSES, 'Data')

NAMELEN = 32
ENTRYSIZE = 48
MAGIC = 0x314B5049

# extern const <타입>* <이름>;  다음 줄에 enum { <이름>_COUNT = N };
PTR_RE = re.compile(
    r'extern[ \t]+const[ \t]+(?P<type>[A-Za-z_][A-Za-z0-9_ \t]*?)[ \t]*\*[ \t]*'
    r'(?P<name>[A-Za-z_]\w*)[ \t]*;\s*'
    r'enum[ \t]*\{[ \t]*(?P=name)_COUNT[ \t]*=[ \t]*(?P<count>\d+)[ \t]*\}[ \t]*;')

# 2차원 : extern const <타입> (*<이름>)[COLS];
#         enum { <이름>_ROWS = R, <이름>_COLS = (C), <이름>_COUNT = R * C };
# 팩에는 평평하게 R*C 칸으로 들어간다. 색인식 x[a][b] 는 그대로 동작한다.
PTR2_RE = re.compile(
    r'extern[ \t]+const[ \t]+(?P<type>[A-Za-z_][A-Za-z0-9_ \t]*?)[ \t]*'
    r'\([ \t]*\*[ \t]*(?P<name>[A-Za-z_]\w*)[ \t]*\)[ \t]*\[[^\]]*\][ \t]*;\s*'
    r'enum[ \t]*\{[ \t]*(?P=name)_ROWS[ \t]*=[ \t]*(?P<rows>\d+)[ \t]*,'
    r'\s*(?P=name)_COLS[ \t]*=[ \t]*\((?P<cols>[^)]*)\)')

SIZE = {'char': 1, 'signed char': 1, 'unsigned char': 1, 'bool': 1,
        'short': 2, 'signed short': 2, 'unsigned short': 2,
        'int': 4, 'signed int': 4, 'unsigned int': 4, 'float': 4,
        'long': 4, 'unsigned long': 4,
        'long long': 8, 'long long int': 8, 'signed long long': 8,
        'unsigned long long': 8, 'unsigned long long int': 8, 'double': 8}


#--------------------------------------------------------------- 콘텐츠 키
#
# 배열이 무엇에 맞춰 길어지는가. 여기 있는 배열은 팩이 내장본보다 길어도
# 된다(용량 안이면). 여기 없는 배열은 길이가 정확히 같아야 한다.
#
#   이름: (키, 폭, 시작번호)
#     폭       : 콘텐츠 하나가 차지하는 칸 수
#     시작번호 : 0번부터 안 담는 배열이 있다. monXYGap 은 3번(ENEMY_SNAIL)부터다.
#                개수 = 칸수 / 폭 + 시작번호
#
# 추측으로 넣지 않는다. 색인식을 눈으로 확인한 것만 넣는다. 길이가 우연히
# 배수인 배열이 많다(c19mv 는 304칸이라 19*16 이지만 성과 무관한 모션이다).
# 확인 안 된 것은 안 넣는다. 안 넣으면 그 콘텐츠를 못 늘릴 뿐, 틀리지는 않는다.
# 빠진 게 있으면 make_pack 이 "의심" 목록으로 알려준다.
CONTENT_KEY = {
    # 몬스터. 색인이 OBJECT.type 이다.
    'enemyData':          ('DPK_KEY_ENEMY', 8, 0),
    'enemyStatInfo':      ('DPK_KEY_ENEMY', 3, 0),
    'enemyZoom':          ('DPK_KEY_ENEMY', 1, 0),
    'enemyIconZoom':      ('DPK_KEY_ENEMY', 1, 0),
    'enemyBossZoom':      ('DPK_KEY_ENEMY', 1, 0),
    'enemyAttackPattern': ('DPK_KEY_ENEMY', 20, 0),
    'enemyIconPos':       ('DPK_KEY_ENEMY', 3, 0),
    'crewPos':            ('DPK_KEY_ENEMY', 5, 0),
    'enemyBigIconPos':    ('DPK_KEY_ENEMY', 3, 0),
    'enemySkillIconPos':  ('DPK_KEY_ENEMY', 3, 0),
    'monXYGap':           ('DPK_KEY_ENEMY', 2, 3),

    # 동료
    'crewData':           ('DPK_KEY_CREW', 6, 0),

    # 스킬
    'skillData':          ('DPK_KEY_SKILL', 29, 0),

    # 성. castleOrder[robin.castle] 처럼 성 번호로 색인한다.
    'castleOrder':        ('DPK_KEY_CASTLE', 1, 0),
    'castleBoxZoom':      ('DPK_KEY_CASTLE', 1, 0),
    'castleBoxColor':     ('DPK_KEY_CASTLE', 1, 0),
    'castleBoxGold':      ('DPK_KEY_CASTLE', 1, 0),
    'castleStarLimit':    ('DPK_KEY_CASTLE', 1, 0),
    'castleCrewPosition': ('DPK_KEY_CASTLE', 12, 0),
    'setHeroPos':         ('DPK_KEY_CASTLE', 6, 0),
    'setEnemyPos':        ('DPK_KEY_CASTLE', 6, 0),

    # 맵. mapRectSize[idx] 처럼 맵 번호로 색인한다.
    'mapRectSize':        ('DPK_KEY_MAP', 1, 0),
    'mapBackSize':        ('DPK_KEY_MAP', 1, 0),
    'mapObjSize':         ('DPK_KEY_MAP', 1, 0),
    'mapNeutralSize':     ('DPK_KEY_MAP', 1, 0),
    'mapEnemySize':       ('DPK_KEY_MAP', 1, 0),
}

#지금 개수. 분류 안 된 배열 중 의심스러운 것을 찾는 데만 쓴다.
NOW = {'DPK_KEY_ENEMY': 431, 'DPK_KEY_CREW': 64, 'DPK_KEY_SKILL': 1374,
       'DPK_KEY_CASTLE': 19, 'DPK_KEY_MAP': 425}


def key_of(name):
    return CONTENT_KEY.get(name, ('DPK_KEY_NONE', 0, 0))


def report_suspects(entries):
    """분류 안 됐는데 길이가 콘텐츠 개수의 배수인 배열을 알려준다.

    전부 진짜는 아니다. 대부분 우연이다. 다만 새 배열이 들어왔을 때
    분류를 빠뜨리지 않도록 눈에 띄게 해둔다.
    """
    out = []

    for _h, _t, name, cnt, _sz, _k in entries:
        if name in CONTENT_KEY or not isinstance(cnt, int):
            continue

        for key, tot in NOW.items():
            if cnt % tot == 0 and 1 <= cnt // tot <= 32:
                out.append((name, cnt, key, cnt // tot))

    return out


def kind_of(typ):
    if 'float' in typ or 'double' in typ:
        return 'DPK_FLOAT'

    return 'DPK_UINT' if 'unsigned' in typ or typ == 'bool' else 'DPK_INT'


def scan(headers):
    """포인터 선언 목록. [(헤더, 타입, 이름, 개수, 원소크기, 종류)]"""
    out = []

    for h in headers:
        text = CT.read(os.path.join(DATA, h))

        found = [(m, None) for m in PTR_RE.finditer(text)]
        found += [(m, m.group('cols')) for m in PTR2_RE.finditer(text)]
        found.sort(key=lambda x: x[0].start())

        for m, cols in found:
            typ = ' '.join(m.group('type').split())
            sz = SIZE.get(typ)

            if sz is None:
                sys.stderr.write('%s : 타입 %r 의 크기를 모른다\n'
                                 % (m.group('name'), typ))
                return None

            if len(m.group('name')) >= NAMELEN:
                sys.stderr.write('%s : 이름이 %d자를 넘는다\n'
                                 % (m.group('name'), NAMELEN - 1))
                return None

            if cols is None:
                cnt = int(m.group('count'))
            else:
                # 안쪽 크기가 (2 * 14) 같은 식이라 파이썬으로 못 푼다.
                # 그대로 넘겨서 컴파일러가 풀게 한다.
                cnt = '%s_ROWS * %s_COLS' % (m.group('name'), m.group('name'))

            out.append((h, typ, m.group('name'), cnt, sz, kind_of(typ)))

    return out


def write_list(entries, headers):
    """로더와 덤퍼가 같이 쓰는 X매크로 목록. 하나만 두어 어긋날 수 없게 한다."""
    path = os.path.join(DATA, 'DataList.h')
    L = []
    L.append('#pragma once')
    L.append('')
    L.append('#ifndef _DATA_LIST_H_')
    L.append('#define _DATA_LIST_H_')
    L.append('')
    L.append('//tools/content/make_pack.py 가 생성한다. 직접 고치지 말 것.')
    L.append('//')
    L.append('//팩에 들어가는 배열 목록이다. 로더(DataPack.cpp)와 팩 생성기가')
    L.append('//이 하나를 같이 쓰므로 둘이 어긋날 수 없다.')
    L.append('//')
    L.append('//X(이름, 원소크기, 종류, 개수, 콘텐츠키, 폭, 시작번호)')
    L.append('//')
    L.append('//콘텐츠키가 DPK_KEY_NONE 이면 길이가 고정이라 팩과 내장본이 정확히')
    L.append('//같아야 한다. 그 외에는 콘텐츠에 맞춰 길어지는 배열이라, 팩이 더')
    L.append('//길어도 용량 안이면 받는다. 개수 = 개수 / 폭 + 시작번호.')
    L.append('')

    for h in headers:
        L.append('#include "%s"' % h)

    L.append('')
    L.append('#define DATA_LIST(X) \\')

    for _h, _t, name, cnt, sz, kind in entries:
        key, w, base = key_of(name)
        L.append('\tX(%s, %d, %s, %s, %s, %d, %d) \\'
                 % (name, sz, kind, cnt, key, w, base))

    L.append('\t/* 끝 */')
    L.append('')
    L.append('#endif')
    L.append('')

    with open(path, 'w', encoding='utf-8-sig', newline='\r\n') as fp:
        fp.write('\n'.join(L))

    return path


DUMPER = r'''
//make_pack.py 가 만든 임시 프로그램. 팩을 써낸다.
#include "Data/DataList.h"
#include "Data/DataPack.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CRC와 ABI 지문은 Classes/Data/DataPackCheck.cpp 것을 그대로 쓴다.
//여기서 다시 구현하면 클라이언트와 조용히 어긋날 수 있다. 실제로 한번
//어긋났었다(DataPack.h 가 BuildConfig.h 보다 먼저 들어가는 곳에서 #ifdef
//가 전부 거짓이 되어, 클라이언트만 다른 지문을 계산했다).

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("usage: dumper <out>\n");
        return 1;
    }

    int count = 0;
#define COUNT_ONE(N, SZ, K, C, KEY, W, B) count++;
    DATA_LIST(COUNT_ONE)
#undef COUNT_ONE

    //본문 크기부터 잰다. 배열마다 8바이트 경계에 맞춘다.
    unsigned int body = 0;
#define SIZE_ONE(N, SZ, K, C, KEY, W, B) body = (body + 7u) & ~7u; body += (unsigned int)(SZ) * (C);
    DATA_LIST(SIZE_ONE)
#undef SIZE_ONE

    unsigned int dirBytes = (unsigned int)count * DPK_ENTRYSIZE;
    unsigned int total = 16 + dirBytes + body + 4;
    unsigned char* out = (unsigned char*)calloc(1, total);

    if (!out)
        return 1;

    unsigned int magic = DPK_MAGIC;
    unsigned int abi = DataPackAbi();

    memcpy(out + 0, &magic, 4);
    memcpy(out + 4, &abi, 4);
    memcpy(out + 8, &count, 4);
    memcpy(out + 12, &body, 4);

    unsigned char* dir = out + 16;
    unsigned char* dat = dir + dirBytes;
    unsigned int at = 0;
    int idx = 0;

#define WRITE_ONE(N, SZ, K, C, KEY, W, B) \
    { \
        at = (at + 7u) & ~7u; \
        unsigned char* e = dir + (unsigned int)idx * DPK_ENTRYSIZE; \
        memset(e, 0, DPK_ENTRYSIZE); \
        strncpy((char*)e, #N, DPK_NAMELEN - 1); \
        e[DPK_NAMELEN + 0] = (unsigned char)(SZ); \
        e[DPK_NAMELEN + 1] = (unsigned char)(K); \
        unsigned int c = (unsigned int)(C); \
        memcpy(e + DPK_NAMELEN + 4, &c, 4); \
        memcpy(e + DPK_NAMELEN + 8, &at, 4); \
        memcpy(dat + at, N, (size_t)(SZ) * (C)); \
        at += (unsigned int)(SZ) * (C); \
        idx++; \
    }
    DATA_LIST(WRITE_ONE)
#undef WRITE_ONE

    unsigned int crc = DataPackCrc(out, total - 4);
    memcpy(out + total - 4, &crc, 4);

    FILE* fp = fopen(argv[1], "wb");

    if (!fp) {
        printf("팩 파일을 못 만든다: %s\n", argv[1]);
        return 1;
    }

    fwrite(out, 1, total, fp);
    fclose(fp);

    printf("배열 %d개, 본문 %u 바이트, 전체 %u 바이트, abi %08x\n",
        count, body, total, abi);
    return 0;
}
'''


def build_and_run(entries, headers, out_pack):
    vcvars = dump_ids.find_vs()

    if not vcvars:
        sys.stderr.write('Visual Studio를 못 찾았다\n')
        return 1

    work = tempfile.mkdtemp(prefix='pack_')
    src = os.path.join(work, 'dumper.cpp')

    with open(src, 'w', encoding='utf-8') as fp:
        fp.write(DUMPER)

    cpps = sorted({os.path.join(DATA, os.path.splitext(h)[0] + '.cpp')
                   for h in headers})

    for c in cpps:
        if not os.path.isfile(c):
            sys.stderr.write('%s 가 없다. split_data.py 로 먼저 갈라야 한다\n' % c)
            return 1

    #CRC와 ABI 지문은 클라이언트와 같은 파일을 쓴다. 두 벌로 두면 어긋난다.
    cpps.append(os.path.join(DATA, 'DataPackCheck.cpp'))

    args = ' '.join('"%s"' % c for c in [src] + cpps)
    cmd = ('call "%s" >nul 2>&1 && cl /nologo /EHsc /utf-8 /W0 /I "%s" %s '
           '/Fe:"%s"' % (vcvars, CLASSES, args, os.path.join(work, 'dumper.exe')))

    r = subprocess.run(cmd, shell=True, cwd=work,
                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    exe = os.path.join(work, 'dumper.exe')

    if not os.path.isfile(exe):
        sys.stderr.write('덤퍼 빌드 실패:\n%s\n'
                         % r.stdout.decode('utf-8', 'replace')[-2000:])
        return 1

    r = subprocess.run([exe, out_pack], stdout=subprocess.PIPE)
    print('  ' + r.stdout.decode('utf-8', 'replace').strip())
    return r.returncode


def verify(path, entries):
    """만든 팩을 다시 읽어 규격과 개수를 확인한다."""
    with open(path, 'rb') as fp:
        buf = fp.read()

    magic, abi, count, body = struct.unpack('<IIiI', buf[:16])

    if magic != MAGIC:
        print('  magic 이 다르다')
        return 1

    if zlib.crc32(buf[:-4]) & 0xffffffff != struct.unpack('<I', buf[-4:])[0]:
        print('  crc 가 안 맞는다')
        return 1

    if count != len(entries):
        print('  배열 개수가 %d여야 하는데 %d다' % (len(entries), count))
        return 1

    for i, (_h, _t, name, cnt, sz, _k) in enumerate(entries):
        e = buf[16 + i * ENTRYSIZE: 16 + (i + 1) * ENTRYSIZE]
        got = e[:NAMELEN].split(b'\0')[0].decode()
        gsz = e[NAMELEN]
        gcnt = struct.unpack('<I', e[NAMELEN + 4:NAMELEN + 8])[0]

        if isinstance(cnt, str):
            cnt = gcnt   # 식이라 파이썬에서 못 센다. 컴파일러가 푼 값을 쓴다.

        if got != name or gsz != sz or gcnt != cnt:
            print('  %d번 항목이 다르다: %s/%d/%d vs %s/%d/%d'
                  % (i, got, gsz, gcnt, name, sz, cnt))
            return 1

    print('  검증 통과 : 배열 %d개, abi %08x, %s 바이트'
          % (count, abi, format(len(buf), ',')))
    return 0



VERIFIER = r"""
//make_pack.py 가 만든 임시 프로그램.
//팩의 값이 소스에 박힌 내장 기본값과 한 칸이라도 다른지 본다.
//
//포인터는 아직 내장 기본값을 가리키고 있다(로더를 안 돌렸으므로).
//그 상태에서 팩을 직접 읽어 바이트째 비교한다.
#include "Data/DataList.h"
#include "Data/DataPack.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const unsigned char* FindEntry(const unsigned char* dir, int count,
    const char* name, unsigned int* oc, int* os, int* ok2)
{
    int i;
    for (i = 0; i < count; i++) {
        const unsigned char* e = dir + (unsigned int)i * DPK_ENTRYSIZE;
        if (strncmp((const char*)e, name, DPK_NAMELEN - 1) != 0) continue;
        *os = e[DPK_NAMELEN + 0];
        *ok2 = e[DPK_NAMELEN + 1];
        memcpy(oc, e + DPK_NAMELEN + 4, 4);
        return e;
    }
    return 0;
}

int main(int argc, char** argv)
{
    if (argc < 2) { printf("usage: verifier <pack>\n"); return 1; }
    FILE* fp = fopen(argv[1], "rb");
    if (!fp) { printf("팩을 못 연다\n"); return 1; }
    fseek(fp, 0, SEEK_END); long size = ftell(fp); fseek(fp, 0, SEEK_SET);
    unsigned char* buf = (unsigned char*)malloc((size_t)size);
    fread(buf, 1, (size_t)size, fp); fclose(fp);

    int count; memcpy(&count, buf + 8, 4);
    const unsigned char* dir = buf + 16;
    const unsigned char* dat = dir + (unsigned int)count * DPK_ENTRYSIZE;

    int bad = 0, arrays = 0; long cells = 0;

#define CMP_ONE(N, SZ, K, C, KEY, W, B) \
    { \
        unsigned int c = 0; int s = 0, k2 = 0; \
        const unsigned char* e = FindEntry(dir, count, #N, &c, &s, &k2); \
        arrays++; \
        if (!e) { printf("  %-24s 팩에 없다\n", #N); bad++; } \
        else if (c != (unsigned int)(C) || s != (SZ)) { \
            printf("  %-24s 규격 다름 (팩 %u칸 %dB / 클라 %d칸 %dB)\n", \
                #N, c, s, (int)(C), (int)(SZ)); bad++; \
        } else { \
            unsigned int off = 0; memcpy(&off, e + DPK_NAMELEN + 8, 4); \
            if (memcmp(dat + off, N, (size_t)(SZ) * (C)) != 0) { \
                printf("  %-24s 값이 다르다\n", #N); bad++; \
            } else { cells += (C); } \
        } \
    }
    DATA_LIST(CMP_ONE)
#undef CMP_ONE

    if (bad) { printf("배열 %d개 중 %d개가 다르다\n", arrays, bad); return 1; }
    printf("배열 %d개 %ld칸 전부 일치\n", arrays, cells);
    return 0;
}
"""


def run_verifier(headers, pack):
    vcvars = dump_ids.find_vs()

    if not vcvars:
        return 1

    work = tempfile.mkdtemp(prefix='vpack_')
    src = os.path.join(work, 'verifier.cpp')

    with open(src, 'w', encoding='utf-8') as fp:
        fp.write(VERIFIER)

    cpps = sorted({os.path.join(DATA, os.path.splitext(h)[0] + '.cpp')
                   for h in headers})
    #CRC와 ABI 지문은 클라이언트와 같은 파일을 쓴다. 두 벌로 두면 어긋난다.
    cpps.append(os.path.join(DATA, 'DataPackCheck.cpp'))

    args = ' '.join('"%s"' % c for c in [src] + cpps)
    cmd = ('call "%s" >nul 2>&1 && cl /nologo /EHsc /utf-8 /W0 /I "%s" %s '
           '/Fe:"%s"' % (vcvars, CLASSES, args,
                         os.path.join(work, 'verifier.exe')))

    r = subprocess.run(cmd, shell=True, cwd=work,
                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    exe = os.path.join(work, 'verifier.exe')

    if not os.path.isfile(exe):
        sys.stderr.write('비교기 빌드 실패:\n%s\n'
                         % r.stdout.decode('utf-8', 'replace')[-2000:])
        return 1

    r = subprocess.run([exe, pack], stdout=subprocess.PIPE)
    print('  ' + r.stdout.decode('utf-8', 'replace').strip().replace('\n', '\n  '))
    return r.returncode

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('bases', nargs='+', help='Data/ 의 헤더 이름 (확장자 없이)')
    ap.add_argument('--out', default=os.path.join('Resources', 'data'))
    ap.add_argument('--name', default='content.pack')
    args = ap.parse_args()

    headers = [b + '.h' for b in args.bases]
    entries = scan(headers)

    if entries is None:
        return 1

    if not entries:
        sys.stderr.write('포인터 선언을 못 찾았다. 먼저 포인터 형태로 바꿔야 한다\n')
        return 1

    print('배열 %d개' % len(entries))

    keyed = sum(1 for e in entries if e[2] in CONTENT_KEY)
    print('  콘텐츠에 맞춰 길어지는 배열 %d개 (나머지는 길이 고정)' % keyed)

    sus = report_suspects(entries)

    if sus:
        print('  분류 안 됐는데 길이가 개수의 배수인 배열 %d개:' % len(sus))

        for name, cnt, key, w in sus[:40]:
            print('    %-24s %6d = %s * %d' % (name, cnt, key[8:], w))

        print('  (대부분 우연이다. 진짜면 CONTENT_KEY 에 넣어라)')

    lp = write_list(entries, headers)
    print('  %s 생성' % os.path.relpath(lp, ROOT))

    outdir = os.path.join(ROOT, args.out)
    os.makedirs(outdir, exist_ok=True)
    out_pack = os.path.join(outdir, args.name)

    if build_and_run(entries, headers, out_pack):
        return 1

    if verify(out_pack, entries):
        return 1

    #팩의 값이 소스에 박힌 값과 한 칸이라도 다르면 여기서 걸린다.
    #이게 통과해야 나중에 내장 기본값을 지울 수 있다.
    if run_verifier(headers, out_pack):
        return 1

    print('  %s' % os.path.relpath(out_pack, ROOT))
    return 0


if __name__ == '__main__':
    sys.exit(main())
