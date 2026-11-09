"""룰렛 × 합성 전투의 합성 사다리 표를 만든다.

docs/합성_테크트리.xlsx  — 아이콘이 든 사람용 표
content/merge_tree.tsv    — 같은 내용의 기계용 표 (64명의 역할 · ★ · 특성). build_tree_data.py 가 읽는다.

합성은 6단 = 성급. 같은 역할 ★n 둘을 합치면 그 역할의 ★n+1 동료 중 하나가 무작위로 나온다.
그래서 "트리" 는 역할군 4개의 ★ 사다리다. 64명은 역할 × ★ 로 이미 고르게 깔려 있다.

동료 그림은 게임이 직접 그린 덤프(BuildConfig.h DUMP_CMF_PNG → dump/crew_N.png)를
reports/hero_allies_64/icons/ 에 복사해 둔 것을 쓴다.
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
LV_MAX = 6

# ---------------------------------------------------------------- 동료 데이터
ROLE_CODE = ('ABBCASSC' 'AASCABBSBSCC' 'ABSBCAAACSBSCCB' 'BBCBSSBCACBCASSCAAASC' 'BASCBSBC')
ROLE_INDEX = {'C': 0, 'A': 1, 'B': 2, 'S': 3}          # CrewRole: 지휘 0 · 포격 1 · 지원 2 · 공격 3
ROLE_NAME = ['지휘', '포격', '지원', '공격']
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
ROLE = [ROLE_INDEX[c] for c in ROLE_CODE]
assert len(ROLE) == 64 and len(STAR) == 64 and len(ACTION) == 64 and len(TITLE) == 64

def ladder(role):
    """★1..★6 마다 그 역할의 동료 번호."""
    return {s: [i for i in range(64) if ROLE[i] == role and STAR[i] == s] for s in range(1, LV_MAX + 1)}

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
GEAR_STEP = {'무기': 6, '갑옷': 1, '목걸이': 5}   # Classes/Data/MergeTreeData.h GearDetail 과 같아야 한다

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
LV_FILL = ['', 'C9A66B', 'C0C0C0', 'E6B422', 'D96A4A', 'B06BD9', '5AC8E8']  # ★1 구리 · ★2 은 · ★3 금 · ★4 붉은금 · ★5 보라 · ★6 하늘
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
    tail = f" · {CATALOG[i]['skill3_kind']}" if STAR[i] >= 5 else ''
    return f"{TITLE[i]}\n{CATALOG[i]['name']}\n{TRAIT6[ACTION[i]]}{tail}"

wb = Workbook()

# ---- 읽는 법
ws = wb.active; ws.title = '읽는 법'
ws.column_dimensions['A'].width = 110
notes = [
 '룰렛 × 합성 전투 — 합성 사다리 (2026-11-09, 6단 = 성급). 기획서 docs/기획_룰렛_합성.md §16·§19.',
 '',
 '■ 공통 규칙',
 '· 런 시작 3릴 슬롯이 계열 3개를 정한다. 계열 = 역할군 4(지휘·포격·지원·공격) + 장비 3(무기·갑옷·목걸이). 릴 1 = 내 선택, 릴 2·3 = 무작위.',
 '· 룰렛은 그 계열의 ★1 블록을 낸다. 같은 계열 2 → ★2, 3 → ★3 블록으로 바로 나온다.',
 '· 같은 역할 ★n 블록 둘을 합치면 그 역할의 ★n+1 동료 중 하나가 무작위로 나온다 (운빨존많겜 식). 어떤 동료끼리든 역할·★만 같으면 합쳐진다.',
 '· 블록 크기 ★1 1×1 → ★2 1×2 → ★3 2×2 → ★4 2×3 → ★5 3×3 → ★6 3×4. 한 방 = 그 동료 값 × 2^(★-1).',
 '· 공격해도 판은 비지 않는다. 성을 도는 동안 판이 ★6 까지 자란다. 압박은 하트(룰렛)·목숨(적 턴)·칸이다.',
 '· 포격은 ★6 이 없어 ★5(기함 함포선장·전설의 강태공)가 끝이다. 지휘 ★6 = 국왕, 지원 ★6 = 성녀, 공격 ★6 = 검성.',
 '',
 '■ 역할 사다리 시트',
 '· 열 = ★1~★6, 행 = 역할마다 최대 5명. 같은 열 안의 얼굴 중 누가 나올지는 합성 때 정해진다.',
 '· 특성(표식·고무·강타·연타·빙결·지속)은 동료마다 하나. ★1·2 는 SKILL1, ★3·4 는 SKILL2, ★5·6 은 SKILL3(궁극기/소환) 를 쏜다.',
 '· 보유한 동료만 사다리에 선다. 한 ★ 에 보유 동료가 없으면 그 역할은 거기서 멈춘다.',
 '',
 '■ 장비',
 '· 무기(검/총/부메랑 = 로빈/다이애나/맥스): ★1 = 히어로가 낀 무기. 한 단계 = 6계단 위. d → d+6 → … 34 에서 멈춘다 (35자루 ≈ 6등급).',
 '· 갑옷(갑옷/조끼/코트): 8벌. 한 단계 = 1칸 위. d → d+1 → … 7 에서 멈춘다.',
 '· 목걸이: 28개. 한 단계 = 5칸 위. d → d+5 → … 27 에서 멈춘다. 낱장 그림이 없어 이름만 적었다.',
 '· 장비 블록이 하는 일: 검 = 히어로 평타 × 2^(Lv-1) · 갑옷 = 보호 1/1/2회, Lv4·5 적 턴 1회 삭제, Lv6 2회 · 목걸이 = 하트 +1/+2/+3, Lv4~6 룰렛 +1/+2/+3.',
 '',
 '■ 그림 출처',
 '· 동료: 게임이 그린 덤프 reports/hero_allies_64/icons/crew_N.png (DUMP_CMF_PNG). 무기: w{0,1,2}_{d+1}.png. 갑옷: item_{armor,vest,coat}_*.png.',
 '· 같은 내용의 기계용 표: content/merge_tree.tsv → tools/merge_roulette/build_tree_data.py → Classes/Data/MergeTreeData.h',
]
for r, t in enumerate(notes, 1):
    c = ws.cell(row=r, column=1, value=t); c.alignment = Alignment(wrap_text=True, vertical='top')
    if t.startswith('■'): c.font = Font(bold=True)

# ---- 역할 사다리
ws = wb.create_sheet('역할 사다리')
labels = ['역할', '#']
for s in range(1, LV_MAX + 1): labels += [f'★{s} 얼굴', f'★{s}']
header(ws, 1, labels)
ws.column_dimensions['A'].width = 7; ws.column_dimensions['B'].width = 4
row = 2
for role in range(4):
    lad = ladder(role)
    depth = max(len(v) for v in lad.values())
    top = max(s for s, v in lad.items() if v)
    for k in range(depth):
        put(ws, row, 1, ROLE_NAME[role] if k == 0 else '', bold=True); put(ws, row, 2, k + 1)
        col = 3
        for s in range(1, LV_MAX + 1):
            ids = lad[s]
            if k < len(ids):
                i = ids[k]
                put(ws, row, col, None, fill=LV_FILL[s]); put_icon(ws, row, col, crew_icon(i))
                put(ws, row, col + 1, crew_label(i), fill=LV_FILL[s])
            else:
                put(ws, row, col, '없음' if (s > top and k == 0) else ''); put(ws, row, col + 1, '')
            ws.column_dimensions[get_column_letter(col + 1)].width = 18
            col += 2
        row += 1
    row += 1
ws.freeze_panes = 'C2'

# ---- 동료 64 목록
ws = wb.create_sheet('동료 64 목록')
header(ws, 1, ['번호', '얼굴', '칭호', '이름', '★', '역할', '원본 Action', '특성 6종', '합성하면(★+1 후보)', '쏘는 것'],
       [6, ICON / 6.5, 14, 14, 5, 7, 12, 9, 34, 20])
for i in range(64):
    r = i + 2
    put(ws, r, 1, i); put_icon(ws, r, 2, crew_icon(i)); put(ws, r, 3, TITLE[i]); put(ws, r, 4, CATALOG[i]['name'])
    put(ws, r, 5, STAR[i], fill=LV_FILL[STAR[i]]); put(ws, r, 6, ROLE_NAME[ROLE[i]]); put(ws, r, 7, ACTION[i]); put(ws, r, 8, TRAIT6[ACTION[i]])
    nxt = ladder(ROLE[i]).get(STAR[i] + 1, [])
    put(ws, r, 9, ' / '.join(TITLE[j] for j in nxt) if nxt else '끝 (더 못 합침)')
    put(ws, r, 10, 'SKILL1 일반탄' if STAR[i] <= 2 else 'SKILL2 일반탄' if STAR[i] <= 4 else f"SKILL3 {CATALOG[i]['skill3_kind']}")
ws.freeze_panes = 'C2'

# ---- 무기
ws = wb.create_sheet('무기 사다리')
header(ws, 1, ['라인', 'detail', '그림', '이름', '→ 합성 결과(d+6)', '그림', '이름', '런 예시 (★1→★6)'],
       [10, 7, ICON / 6.5, 18, 14, ICON / 6.5, 18, 70])
row = 2
for line, (lname, names) in enumerate([('검 (로빈)', SWORD), ('총 (다이애나)', GUN), ('부메랑 (맥스)', BOOM)]):
    step = GEAR_STEP['무기']
    for d in range(35):
        nd = min(d + step, 34)
        put(ws, row, 1, lname); put(ws, row, 2, d)
        put_icon(ws, row, 3, weapon_icon(line, d)); put(ws, row, 4, names[d])
        if nd == d: put(ws, row, 5, '최고 (더 못 합침)'); put(ws, row, 6, ''); put(ws, row, 7, '')
        else: put(ws, row, 5, f'd{d} + d{d} → d{nd}'); put_icon(ws, row, 6, weapon_icon(line, nd)); put(ws, row, 7, names[nd])
        chain = [min(d + step * k, 34) for k in range(LV_MAX)]
        put(ws, row, 8, ' → '.join(f'★{k + 1} {names[c]}' for k, c in enumerate(chain)) + ('' if d + step * (LV_MAX - 1) <= 34 else '  (상한에서 겹침)'))
        row += 1
    row += 1
ws.freeze_panes = 'C2'

# ---- 갑옷
ws = wb.create_sheet('갑옷 사다리')
header(ws, 1, ['라인', 'detail', '그림', '이름', '→ 합성 결과(d+1)', '그림', '이름', '런 예시 (★1→★6)'],
       [12, 7, ICON / 6.5, 16, 14, ICON / 6.5, 16, 70])
row = 2
for line, (lname, names) in enumerate([('갑옷 (로빈)', ARMOR), ('조끼 (다이애나)', VEST), ('코트 (맥스)', COAT)]):
    step = GEAR_STEP['갑옷']
    for d in range(8):
        nd = min(d + step, 7)
        put(ws, row, 1, lname); put(ws, row, 2, d); put_icon(ws, row, 3, armor_icon(line, d)); put(ws, row, 4, names[d])
        if nd == d: put(ws, row, 5, '최고'); put(ws, row, 6, ''); put(ws, row, 7, '')
        else: put(ws, row, 5, f'd{d} + d{d} → d{nd}'); put_icon(ws, row, 6, armor_icon(line, nd)); put(ws, row, 7, names[nd])
        chain = [min(d + step * k, 7) for k in range(LV_MAX)]
        put(ws, row, 8, ' → '.join(f'★{k + 1} {names[c]}' for k, c in enumerate(chain)))
        row += 1
    row += 1
ws.freeze_panes = 'C2'

# ---- 목걸이·반지
ws = wb.create_sheet('목걸이·반지')
header(ws, 1, ['종류', 'detail', '이름', '→ 합성 결과', '이름', '런 예시 (★1→★6)'], [10, 7, 16, 14, 16, 80])
row = 2
for kind, names, step in [('목걸이', NECK, GEAR_STEP['목걸이']), ('반지(참고)', RING, 3)]:
    n = len(names)
    for d in range(n):
        nd = min(d + step, n - 1)
        put(ws, row, 1, kind); put(ws, row, 2, d); put(ws, row, 3, names[d])
        put(ws, row, 4, '최고' if nd == d else f'd{d} + d{d} → d{nd}'); put(ws, row, 5, '' if nd == d else names[nd])
        chain = [min(d + step * k, n - 1) for k in range(LV_MAX)]
        put(ws, row, 6, ' → '.join(f'★{k + 1} {names[c]}' for k, c in enumerate(chain)))
        row += 1
    row += 1
ws.cell(row=row, column=1, value='반지는 §16 의 3칸(무기·갑옷·목걸이)에 없다. 넣을 때를 대비한 참고 표.')

# ---------------------------------------------------------------- TSV (엑셀보다 먼저 쓴다 — 엑셀이 열려 있어도 TSV 는 남게)
with open(OUT_TSV, 'w', encoding='utf-8', newline='\n') as f:
    f.write('#룰렛 × 합성 전투 — 64명의 역할 · ★ · 특성. tools/board/build_merge_tree_xlsx.py 가 쓴다. 사람용은 docs/합성_테크트리.xlsx\n')
    f.write('#합성 6단 = ★. 같은 역할 ★n 둘을 합치면 그 역할의 ★n+1 중 하나가 무작위로 나온다. build_tree_data.py 가 MergeTreeData.h 로 굽는다.\n')
    f.write('#role: 0 지휘 · 1 포격 · 2 지원 · 3 공격 (Def/BoardDef.h CrewRole). trait: 표식·고무·강타·연타·빙결·지속.\n')
    f.write('crew\trole\trole_name\tstar\ttitle\taction\ttrait\n')
    for i in range(64):
        f.write(f'{i}\t{ROLE[i]}\t{ROLE_NAME[ROLE[i]]}\t{STAR[i]}\t{TITLE[i]}\t{ACTION[i]}\t{TRAIT6[ACTION[i]]}\n')

# 무결성: 역할 × ★ 분배가 CLAUDE.md 표와 같은가
expected = {0: [2, 3, 4, 5, 2, 1], 1: [2, 3, 4, 4, 2, 0], 2: [2, 3, 4, 5, 2, 1], 3: [2, 3, 3, 4, 2, 1]}
for role, counts in expected.items():
    lad = ladder(role)
    assert [len(lad[s]) for s in range(1, 7)] == counts, (role, [len(lad[s]) for s in range(1, 7)])

try:
    OUT_XLSX.parent.mkdir(parents=True, exist_ok=True); wb.save(OUT_XLSX)
except PermissionError:
    raise SystemExit(f'엑셀이 {OUT_XLSX.name} 을 열고 있다. 닫고 다시 돌려라. (TSV 는 썼다)')
print('wrote', OUT_XLSX.name, OUT_TSV.name, '| 64 crew, 4 roles x 6 stars match the balance table, gear steps 6-1-5')
