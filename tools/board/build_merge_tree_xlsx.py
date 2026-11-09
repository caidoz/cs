"""룰렛 × 합성 전투의 합성 테크트리 표를 만든다.

docs/합성_테크트리.xlsx  — 아이콘이 든 사람용 표
content/merge_tree.tsv    — 같은 내용의 기계용 표 (동료 트리)

동료 그림은 게임이 직접 그린 덤프(BuildConfig.h DUMP_CMF_PNG → dump/crew_N.png)를
reports/hero_allies_64/icons/ 에 복사해 둔 것을 쓴다. 부품 시트에서 머리를 자르는 방법은
64명 중 절반이 틀려서 버렸다.
무기는 w{line}_{detail+1}.png, 갑옷은 item_{armor|vest|coat}_{hero}{detail}.png.
목걸이·반지는 낱장 그림이 없어 이름만 적는다.
"""
from pathlib import Path
import io, re, csv
from PIL import Image
from openpyxl import Workbook
from openpyxl.drawing.image import Image as XLImage
from openpyxl.styles import Alignment, Font, PatternFill, Border, Side
from openpyxl.utils import get_column_letter

ROOT = Path(__file__).resolve().parents[2]
RES = ROOT / 'Resources/res'
OUT_XLSX = ROOT / 'docs/합성_테크트리.xlsx'
OUT_TSV = ROOT / 'content/merge_tree.tsv'
ICON = 56  # 셀에 넣는 그림 크기(px)

# ---------------------------------------------------------------- 동료 데이터
ROLE_CODE = ('ABBCASSC' 'AASCABBSBSCC' 'ABSBCAAACSBSCCB' 'BBCBSSBCACBCASSCAAASC' 'BASCBSBC')
ROLE_NAME = {'A': '포격', 'B': '지원', 'C': '지휘', 'S': '공격'}
STAR = [1,1,1,1,1,1,1,1, 2,2,2,2,2,2,2,2, 2,2,2,2,3,3,3,3, 3,3,3,3,3,3,3,3,
        3,3,3,4,4,4,4,4, 4,4,4,5,5,4,4,4, 4,4,4,4,4,4,5,4, 5,5,5,5,5,6,6,6]
ACTION = ['Volley','Shield','Heal','Inspire','Expose','Bleed','Strike','Supply',
          'Shield','Strike','Strike','Supply','Chill','Cleanse','Repair','Chill','Repair','Strike','Shield','Fortify',
          'Expose','Cleanse','Volley','Supply','Inspire','Chill','Burn','Leech','Fortify','Poison','Repair','Inspire','Shield','Expose','Supply',
          'Heal','Smith','Inspire','Fortify','Strike','Poison','Repair','Supply','Strike','Fortify','Cleric','Expose','Strike','Bleed','Shock','Inspire','Chill','Leech','Discharge','Chill','Supply',
          'Heal','Captain','Burn','Expose','Shield','Strike','Repair','Inspire']
TITLE = ['새총 꼬마','용기 꼬마','약초 할머니','원로 촌장','성벽 파수꾼','침술 낭자','열혈 일꾼','마을 살림꾼',
         '파도 어인','삼지창 수병','연타 격투가','신속 배달부','올가미 선원','길잡이 탐험가','새싹 치유사','서리 궁수','부품 보급상','질풍 검객','기도의 현자','철벽 근위대장',
         '파수 부엉이','정돈 메이드','행운의 바니걸','지도 제작자','학당 교사','물방울 꼬마','화약통 해적','약탈 해적','고목 룬 장로','맹독 사냥꾼','왕실 정원사','박자의 무희','계약 남작','기록 학자','무역 거상',
         '성채 대식가','수석 대장장이','왕실 공주','충직한 수호견','결투 중기사','가마솥 마녀','비스트로 셰프','궁정 재상','전설의 강태공','맹수 군주','빛의 성직자','원로 참모','발경의 달인','그림자 암살자','전격술사','진격의 사령관','한기의 원령','유령 집사','잔류 전류령','빙정의 창술사','친선 대사',
         '왕실 대요리장','기함 함포선장','성염의 기사단장','심판 백작','결계 대마도사','무영의 검성','광휘의 성녀','위엄의 국왕']
# 기획서 §14 의 특성 6종으로 접는다. 원본 Action 열도 같이 적어 두어 고칠 수 있게 한다.
TRAIT6 = {'Expose':'표식', 'Inspire':'고무', 'Supply':'고무', 'Smith':'고무', 'Captain':'고무',
          'Strike':'강타', 'Volley':'연타',
          'Chill':'빙결', 'Shield':'빙결', 'Fortify':'빙결', 'Heal':'빙결', 'Repair':'빙결', 'Cleanse':'빙결', 'Cleric':'빙결',
          'Burn':'지속', 'Poison':'지속', 'Bleed':'지속', 'Shock':'지속', 'Discharge':'지속', 'Leech':'지속'}

# 트리: (역할, 이름, [Lv1, Lv2, Lv3, Lv4])  — 같은 Lv4 를 두 트리가 공유할 수 있다(합류)
TREES = [
    ('지휘', '왕가', [3, 24, 42, 63]),
    ('지휘', '군단', [7, 19, 50, 44]),
    ('지휘', '현자', [18, 28, 46, 59]),
    ('지휘', '사절', [11, 33, 37, 55]),
    ('포격', '해적', [8, 12, 27, 57]),
    ('포격', '꼬마', [0, 25, 47, 43]),
    ('포격', '파수', [4, 20, 51, 53]),
    ('포격', '화약', [9, 26, 52, 57]),
    ('지원', '식탁', [2, 30, 35, 56]),
    ('지원', '빛',   [1, 14, 45, 62]),
    ('지원', '지킴', [13, 21, 38, 60]),
    ('지원', '공방', [16, 23, 36, 60]),
    ('공격', '검',   [6, 17, 39, 61]),
    ('공격', '서리', [15, 29, 48, 54]),
    ('공격', '독',   [5, 31, 40, 58]),
    ('공격', '격투', [10, 22, 49, 61]),
]
RESERVE = [32, 34, 41]

def load_catalog():
    rows = {}
    with open(ROOT / 'reports/hero_allies_64/catalog.tsv', encoding='utf-8-sig') as f:
        for r in csv.DictReader(f, delimiter='\t'):
            rows[int(r['crew_id'])] = r
    return rows
CATALOG = load_catalog()

# ---------------------------------------------------------------- 아이템 이름
def text_lines(start, count):
    lines = (ROOT / 'Classes/Text.h').read_text(encoding='utf-8-sig').splitlines()
    out = []
    for ln in lines[start - 1:]:
        m = re.search(r'"([^"]*)"', ln)
        if m:
            out.append(m.group(1))
            if len(out) == count: break
    return out
SWORD = text_lines(658, 35); GUN = text_lines(694, 35); BOOM = text_lines(730, 35)
ARMOR = text_lines(793, 8); VEST = text_lines(802, 8); COAT = text_lines(811, 8)
NECK = text_lines(901, 28); RING = text_lines(930, 18)
assert SWORD[1] == '롱소드' and GUN[0] == '발화식 총' and BOOM[0] == '사냥용 부메랑' and ARMOR[0] == '헌터 튜닉' and NECK[0] == '명예의 펜던트'

# ---------------------------------------------------------------- 그림
def square(im, size=ICON):
    im = im.convert('RGBA')
    s = max(im.size)
    canvas = Image.new('RGBA', (s, s), (0, 0, 0, 0))
    canvas.paste(im, ((s - im.width) // 2, (s - im.height) // 2))
    return canvas.resize((size, size), Image.NEAREST if s <= size else Image.LANCZOS)

def xl_image(pil):
    buf = io.BytesIO(); pil.save(buf, format='PNG'); buf.seek(0)
    img = XLImage(buf); img.width = img.height = ICON
    return img

CREW_ICON_DIR = ROOT / 'reports/hero_allies_64/icons'
def crew_icon(i):
    im = Image.open(CREW_ICON_DIR / f'crew_{i}.png').convert('RGBA')
    b = im.getbbox()
    return square(im.crop(b) if b else im)
def weapon_icon(line, d):
    return square(Image.open(RES / f'w{line}_{d + 1}.png'))
def armor_icon(line, d):
    fn = ['item_armor_robin', 'item_vest_diana', 'item_coat_maxx'][line]
    return square(Image.open(RES / f'{fn}{d}.png'))

# ---------------------------------------------------------------- 엑셀
thin = Side(style='thin', color='999999')
BORDER = Border(left=thin, right=thin, top=thin, bottom=thin)
HEAD = PatternFill('solid', fgColor='2F3B52'); HEADF = Font(bold=True, color='FFFFFF')
LV_FILL = ['', 'C9A66B', 'C0C0C0', 'E6B422', 'D96A4A']  # 구리·은·금·붉은금
CENTER = Alignment(horizontal='center', vertical='center', wrap_text=True)

def header(ws, row, labels, widths=None):
    for c, t in enumerate(labels, 1):
        cell = ws.cell(row=row, column=c, value=t)
        cell.fill = HEAD; cell.font = HEADF; cell.alignment = CENTER; cell.border = BORDER
    if widths:
        for c, wdt in enumerate(widths, 1): ws.column_dimensions[get_column_letter(c)].width = wdt

def put(ws, row, col, value, fill=None, bold=False):
    cell = ws.cell(row=row, column=col, value=value)
    cell.alignment = CENTER; cell.border = BORDER
    if fill: cell.fill = PatternFill('solid', fgColor=fill)
    if bold: cell.font = Font(bold=True)
    return cell

def put_icon(ws, row, col, pil):
    img = xl_image(pil)
    ws.add_image(img, f'{get_column_letter(col)}{row}')
    ws.row_dimensions[row].height = ICON * 0.78
    ws.column_dimensions[get_column_letter(col)].width = ICON / 6.5

def crew_label(i):
    return f"{TITLE[i]}\n{CATALOG[i]['name']}\n★{STAR[i]} · {TRAIT6[ACTION[i]]}"

wb = Workbook()

# ---- 읽는 법
ws = wb.active; ws.title = '읽는 법'
ws.column_dimensions['A'].width = 110
notes = [
 '룰렛 × 합성 전투 — 합성 테크트리 (2026-11-09). 기획서 docs/기획_룰렛_합성.md §15·§16 의 "계열" 이 이 표의 "트리" 다.',
 '',
 '■ 공통 규칙',
 '· 런 시작 3릴 슬롯이 트리 3개를 정한다. 릴 1 = 내가 고른 트리, 릴 2·3 = 보유 풀에서 무작위.',
 '· 룰렛은 그 트리 3개의 Lv1 블록만 낸다. 같은 트리 2 → Lv2 블록, 3 → Lv3 블록으로 나온다.',
 '· 같은 트리·같은 Lv 블록 2개를 합치면 한 단계 위 칸의 것이 된다. 얼굴·장비가 바뀐다 (운빨존많겜 식). 블록 크기 Lv1 1×1 → Lv2 1×2 → Lv3 2×2 → Lv4 2×4.',
 '· 두 트리가 같은 Lv4 로 합류할 수 있다(표에 "합류" 표시). 그 Lv4 는 어느 쪽에서 와도 같은 인물이다.',
 '',
 '■ 동료 트리 (16개, 역할군마다 4개)',
 '· Lv 가 오르면 성급이 오른다: Lv1 ★1~2 → Lv2 ★2~3 → Lv3 ★3~4 → Lv4 ★4~6. 세기는 성급이 정한다.',
 '· 블록이 쏘는 것: Lv1 = 그 동료의 SKILL1, Lv2 = SKILL2, Lv3 = SKILL3(궁극기/소환), Lv4 = SKILL3 ×3 각성.',
 '· 특성(표식·고무·강타·연타·빙결·지속)은 지금 칸의 동료 것을 따른다. 원본 Action 열을 보고 6종 배정을 고칠 수 있다.',
 '· 예비 3명(계약 남작·무역 거상·비스트로 셰프)은 트리 밖이다. 가챠 중복 승급 재료이거나 나중에 다섯째 트리의 씨앗.',
 '',
 '■ 장비 트리',
 '· 무기(검/총/부메랑 = 로빈/다이애나/맥스): Lv1 = 히어로가 낀 무기. 한 단계 = 7계단 위(35자루 = 7 × 5등급). detail d → d+7 → d+14 → d+21, 34 에서 멈춘다.',
 '· 갑옷(갑옷/조끼/코트): 8벌. 한 단계 = 2칸 위. d → d+2 → d+4 → d+6, 7 에서 멈춘다.',
 '· 목걸이: 28개 = 7 × 4등급. 한 단계 = 7칸 위. 낱장 그림이 없어 이름만 적었다.',
 '· 장비 블록이 하는 일은 §16 그대로: 검 = 히어로 평타/궁극기, 갑옷 = 보호/적 턴 삭제, 목걸이 = 하트/룰렛. Lv 가 그 크기를 정하고, 어느 장비인지는 그림과 이름(= 히어로 코스튬)이다.',
 '',
 '■ 그림 출처',
 '· 동료: 게임이 그린 덤프 reports/hero_allies_64/icons/crew_N.png (DUMP_CMF_PNG). 무기: w{0,1,2}_{d+1}.png. 갑옷: item_{armor,vest,coat}_*.png.',
 '· 같은 내용의 기계용 표: content/merge_tree.tsv',
]
for r, t in enumerate(notes, 1):
    c = ws.cell(row=r, column=1, value=t); c.alignment = Alignment(wrap_text=True, vertical='top')
    if t.startswith('■'): c.font = Font(bold=True)

# ---- 동료 트리
ws = wb.create_sheet('동료 트리')
labels = ['역할', '트리']
for lv in range(1, 5):
    labels += [f'Lv{lv} 얼굴', f'Lv{lv}']
    if lv < 4: labels += ['→']
header(ws, 1, labels)
ws.column_dimensions['A'].width = 7; ws.column_dimensions['B'].width = 7
row = 2
lv4_users = {}
for role, name, chain in TREES: lv4_users.setdefault(chain[3], []).append(name)
for role, name, chain in TREES:
    put(ws, row, 1, role, bold=True); put(ws, row, 2, name, bold=True)
    col = 3
    for lv, i in enumerate(chain, 1):
        put(ws, row, col, None, fill=LV_FILL[lv]); put_icon(ws, row, col, crew_icon(i)); col += 1
        label = crew_label(i)
        if lv == 4 and len(lv4_users[i]) > 1: label += f"\n합류 ← {' · '.join(lv4_users[i])}"
        put(ws, row, col, label, fill=LV_FILL[lv]); ws.column_dimensions[get_column_letter(col)].width = 18; col += 1
        if lv < 4: put(ws, row, col, '→', bold=True); ws.column_dimensions[get_column_letter(col)].width = 3; col += 1
    row += 1
row += 1
put(ws, row, 1, '예비', bold=True); put(ws, row, 2, '트리 밖')
col = 3
for i in RESERVE:
    put_icon(ws, row, col, crew_icon(i)); col += 1
    put(ws, row, col, crew_label(i)); col += 1
    if col < 14: put(ws, row, col, ''); col += 1
ws.freeze_panes = 'C2'

# ---- 동료 64 목록
ws = wb.create_sheet('동료 64 목록')
header(ws, 1, ['번호', '얼굴', '칭호', '이름', '★', '역할', '원본 Action', '특성 6종', '트리', 'Lv', '쏘는 것(기획)'],
       [6, ICON / 6.5, 14, 14, 5, 7, 12, 9, 10, 5, 22])
where = {}
for role, name, chain in TREES:
    for lv, i in enumerate(chain, 1): where.setdefault(i, []).append((f'{role}·{name}', lv))
for i in range(64):
    r = i + 2
    put(ws, r, 1, i); put_icon(ws, r, 2, crew_icon(i)); put(ws, r, 3, TITLE[i]); put(ws, r, 4, CATALOG[i]['name'])
    put(ws, r, 5, STAR[i]); put(ws, r, 6, ROLE_NAME[ROLE_CODE[i]]); put(ws, r, 7, ACTION[i]); put(ws, r, 8, TRAIT6[ACTION[i]])
    w = where.get(i)
    if w:
        put(ws, r, 9, ' / '.join(t for t, _ in w), fill=LV_FILL[w[0][1]]); put(ws, r, 10, w[0][1], fill=LV_FILL[w[0][1]])
        shoots = ['SKILL1 일반탄 100%', 'SKILL2 일반탄 300%', f"SKILL3 {CATALOG[i]['skill3_kind']}", f"SKILL3 {CATALOG[i]['skill3_kind']} ×3 각성"][w[0][1] - 1]
        put(ws, r, 11, shoots)
    else:
        put(ws, r, 9, '예비'); put(ws, r, 10, '-'); put(ws, r, 11, '-')
ws.freeze_panes = 'C2'

# ---- 무기 트리
ws = wb.create_sheet('무기 트리')
header(ws, 1, ['라인', 'detail', '등급', '그림', '이름', '→ 합성 결과(d+7)', '그림', '이름', '런 예시 (Lv1→Lv4)'],
       [10, 7, 6, ICON / 6.5, 18, 14, ICON / 6.5, 18, 44])
row = 2
for line, (lname, names) in enumerate([('검 (로빈)', SWORD), ('총 (다이애나)', GUN), ('부메랑 (맥스)', BOOM)]):
    for d in range(35):
        nd = min(d + 7, 34)
        tier = d // 7
        put(ws, row, 1, lname); put(ws, row, 2, d); put(ws, row, 3, f'{tier + 1}등급')
        put_icon(ws, row, 4, weapon_icon(line, d)); put(ws, row, 5, names[d])
        if nd == d:
            put(ws, row, 6, '최고 (더 못 합침)'); put(ws, row, 7, ''); put(ws, row, 8, '')
        else:
            put(ws, row, 6, f'd{d} + d{d} → d{nd}'); put_icon(ws, row, 7, weapon_icon(line, nd)); put(ws, row, 8, names[nd])
        chain = [min(d + 7 * k, 34) for k in range(4)]
        put(ws, row, 9, ' → '.join(f'Lv{k + 1} {names[c]}' for k, c in enumerate(chain)) if d < 14 else
            ' → '.join(f'Lv{k + 1} {names[c]}' for k, c in enumerate(chain)) + '  (상한에서 겹침)')
        row += 1
    row += 1
ws.freeze_panes = 'D2'

# ---- 갑옷 트리
ws = wb.create_sheet('갑옷 트리')
header(ws, 1, ['라인', 'detail', '그림', '이름', '→ 합성 결과(d+2)', '그림', '이름', '런 예시 (Lv1→Lv4)'],
       [12, 7, ICON / 6.5, 16, 14, ICON / 6.5, 16, 50])
row = 2
for line, (lname, names) in enumerate([('갑옷 (로빈)', ARMOR), ('조끼 (다이애나)', VEST), ('코트 (맥스)', COAT)]):
    for d in range(8):
        nd = min(d + 2, 7)
        put(ws, row, 1, lname); put(ws, row, 2, d); put_icon(ws, row, 3, armor_icon(line, d)); put(ws, row, 4, names[d])
        if nd == d: put(ws, row, 5, '최고'); put(ws, row, 6, ''); put(ws, row, 7, '')
        else: put(ws, row, 5, f'd{d} + d{d} → d{nd}'); put_icon(ws, row, 6, armor_icon(line, nd)); put(ws, row, 7, names[nd])
        chain = [min(d + 2 * k, 7) for k in range(4)]
        put(ws, row, 8, ' → '.join(f'Lv{k + 1} {names[c]}' for k, c in enumerate(chain)))
        row += 1
    row += 1
ws.freeze_panes = 'C2'

# ---- 목걸이·반지
ws = wb.create_sheet('목걸이·반지')
header(ws, 1, ['종류', 'detail', '등급', '이름', '→ 합성 결과', '이름', '런 예시 (Lv1→Lv4)'], [8, 7, 6, 16, 14, 16, 60])
row = 2
for kind, names, step in [('목걸이', NECK, 7), ('반지(참고)', RING, 6)]:
    n = len(names)
    for d in range(n):
        nd = min(d + step, n - 1)
        put(ws, row, 1, kind); put(ws, row, 2, d); put(ws, row, 3, f'{d // step + 1}등급'); put(ws, row, 4, names[d])
        put(ws, row, 5, '최고' if nd == d else f'd{d} + d{d} → d{nd}'); put(ws, row, 6, '' if nd == d else names[nd])
        chain = [min(d + step * k, n - 1) for k in range(4)]
        put(ws, row, 7, ' → '.join(f'Lv{k + 1} {names[c]}' for k, c in enumerate(chain)))
        row += 1
    row += 1
ws.cell(row=row, column=1, value='반지는 §16 의 3칸(무기·갑옷·목걸이)에 없다. 넣을 때를 대비한 참고 표.')

OUT_XLSX.parent.mkdir(parents=True, exist_ok=True)
wb.save(OUT_XLSX)

# ---------------------------------------------------------------- TSV
with open(OUT_TSV, 'w', encoding='utf-8', newline='\n') as f:
    f.write('#룰렛 × 합성 전투 동료 트리. tools/board/build_merge_tree_xlsx.py 가 쓴다. 사람용은 docs/합성_테크트리.xlsx\n')
    f.write('#같은 트리·같은 lv 블록 둘을 합치면 lv+1 행의 crew 가 된다. lv4 가 같은 두 트리는 합류한다.\n')
    f.write('tree\trole\tname\tlv\tcrew\ttitle\tstar\taction\ttrait\n')
    for t, (role, name, chain) in enumerate(TREES):
        for lv, i in enumerate(chain, 1):
            f.write(f'{t}\t{role}\t{name}\t{lv}\t{i}\t{TITLE[i]}\t{STAR[i]}\t{ACTION[i]}\t{TRAIT6[ACTION[i]]}\n')
    for i in RESERVE:
        f.write(f'-1\t{ROLE_NAME[ROLE_CODE[i]]}\t예비\t0\t{i}\t{TITLE[i]}\t{STAR[i]}\t{ACTION[i]}\t{TRAIT6[ACTION[i]]}\n')

# 트리 무결성: 64명이 정확히 한 번씩(합류 Lv4 는 두 번) 나오는가
used = [i for _, _, c in TREES for i in c] + RESERVE
from collections import Counter
cnt = Counter(used)
missing = [i for i in range(64) if cnt[i] == 0]
dup = [i for i, n in cnt.items() if n > 1 and i not in (57, 60, 61)]
assert not missing, missing
assert not dup, dup
for role, name, chain in TREES:
    assert all(STAR[a] <= STAR[b] for a, b in zip(chain, chain[1:])), (name, chain)
    assert all(ROLE_NAME[ROLE_CODE[i]] == role for i in chain), (name, chain)
print('wrote', OUT_XLSX, OUT_TSV, '| 64 crew covered, stars non-decreasing, roles consistent')
