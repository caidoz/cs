"""Build review artifacts from the existing 64 ally profiles; no game mutation."""
import csv
import html
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'reports/drag_preview'
OUT.mkdir(parents=True, exist_ok=True)
allies = json.loads((ROOT / 'reports/hero_allies_64/balance.json').read_text(encoding='utf-8'))
assert len(allies) == 64 and len({p['id'] for p in allies}) == 64
actions = dict(Shield='보호막 회복', Heal='체력 회복', Repair='수리', Supply='공격 준비 진행',
              Inspire='인접 동료 다음 탄 강화', Fortify='다음 기본 피격 감소', Cleanse='해로운 효과 하나 제거',
              Volley='추가 사격', Strike='영웅 공격력 기준 타격', Leech='흡혈', Burn='화상',
              Poison='중독', Chill='냉기', Shock='감전', Bleed='출혈', Expose='취약', Discharge='감전 소비',
              PrototypeSmith='로키 수리', PrototypeCleric='아밀 회복', PrototypeCaptain='잭 지원 사격')
conditions = dict(Always='배치 후 사용 가능', Front='전열: 오른쪽 절반', Back='후열: 왼쪽 절반',
                 AdjacentWeapon='검·총·부메랑 인접', AdjacentCrew='다른 ID 동료 인접', Alone='다른 ID 동료 비인접',
                 LowHp='성 체력 50% 이하', HighHp='성 체력 50% 초과', LowShield='보호막 50% 이하',
                 EnemyLowHp='적 체력 50% 이하', EnemyHighHp='적 체력 50% 초과', EnemyDebuffed='적 상태이상 있음',
                 EnemyClean='적 상태이상 없음', EveryThird='원본 영웅 공격 이벤트 3회 이후')
def effect(action, power):
    label = actions[action]
    if action in ('Burn','Poison','Chill','Shock','Bleed','Expose'):
        return f'{label} {power}중첩'
    if action == 'Cleanse':
        return label
    if action == 'Inspire':
        return f'{label} +{power}%p (합계 40%p 한도)'
    if action == 'Supply':
        return f'{label} +{power}% (주기당 합계 30% 한도)'
    return f'{label} {power}% (단위·상한은 BALANCE_RULES.md)'

rows = []
for p in allies:
    links = []
    for key, label, trigger in [('robin','로빈','실제 검 명중'), ('diana','디아나','기본 총 사격'), ('max','맥스','귀환 완료')]:
        link = p[key]
        if key == 'max' and p['id'] in (36,45,57):
            trigger = {36:'부메랑 비행 중',45:'귀환 완료',57:'귀환 시작'}[p['id']]
        links.append(f"{label}: {trigger} → {effect(link['action'], link['power'])} / {link['cooldown_seconds']:g}초")
    rows.append(dict(id=p['id'], name=p['name'], size=f"{p['cols']}×{p['rows']}",
                     attack=f"{p['attack_seconds']:g}초 / 기존 공격력 {p['attack_percent']}%",
                     ability=f"{p['ability']} · {effect(p['action'],p['power'])} / {p['ability_seconds']:g}초",
                     condition=conditions[p['condition']], robin=links[0], diana=links[1], max=links[2],
                     inactive=f"조건 대기: {conditions[p['condition']]}", drawback=p['drawback']))
with (OUT/'ALLIES_CASES.csv').open('w', encoding='utf-8-sig', newline='') as f:
    writer=csv.DictWriter(f, fieldnames=list(rows[0])); writer.writeheader(); writer.writerows(rows)
lines=['# 동료 64종 드래그 상세 케이스', '',
       '원본: reports/hero_allies_64/balance.json. 64개 고유 능력 + 192개 히어로 연계.',
       '수치는 현행 v1. 배치 조건과 전투 조건을 구별하고 세부 단위·상한은 ../hero_allies_64/BALANCE_RULES.md를 따른다.',
       '로키·아밀·잭은 시제품 전용 경로가 있으므로 본문 예외 규칙을 함께 적용한다.', '']
for r in rows:
    lines += [f"## {r['id']:02d} {r['name']}", '',
              f"- 점유 {r['size']} · 기본 사격 {r['attack']}", f"- 고유: {r['ability']}",
              f"- 조건 충족: {r['condition']} → 능력 사용 가능; 실제 발동/회복 대상은 전투에서 판정",
              f"- 조건 미충족: {r['inactive']}", f"- 제약: {r['drawback']}",
              *[f"- {r[key]}" for key in ('robin','diana','max')],
              '- 이동: 자신의 조건과 주변 동료의 인접/독립/격려 조건의 전후 차이를 모두 표시', '']
(OUT/'ALLIES_CASES.md').write_text('\n'.join(lines), encoding='utf-8')

kinds=['검','총','부메랑','투구','갑옷','장갑','바지','신발','방패','목걸이','반지','포대','정수','작전서','동료']
rules={('투구','검'):'I01 검 준비 −15%', ('장갑','검'):'I02 추가 검 피해 +20%',
       ('동료','검'):'I03 로키 +25%; I04 추가 검 3회 협공 (대상별 실제 경로 확인)',
       ('신발','갑옷'):'I06 방어막 펄스 준비 −20% (실제 목록 확인)',
       ('신발','방패'):'I06 방어막 펄스 준비 −20%',
       ('투구','작전서'):'I07 궁극기 준비 −20%',
       ('바지','동료'):'I08 체력 기여 50→100%; I09 구 수리 경로 (버그 수정 필요)',
       ('검','포대'):'I11 검 공격력 35%×L 추가 피해 (전투 소비 확인 필요)',
       ('정수','포대'):'I12~I15 불/얼음/번개/마력별; 쿨타임 합계 60% 한도 (소비 확인 필요)',
       ('동료','포대'):'I16 포격형; I17 잭 추가 타격 (ID 변환·전투 소비 확인 필요)',
       ('동료','동료'):'조건 인접/독립, 격려 수신·손실. 동료 상세표 참조',
       ('검','동료'):'무기 인접 조건', ('총','동료'):'무기 인접 조건', ('부메랑','동료'):'무기 인접 조건',
       ('동료','작전서'):'I19 왕/I20 듀라크: 거리 무관 승선 조건',
       ('동료','정수'):'직접 인접 효과 없음',
       }
for k in ('방패','투구','신발','바지'):
    rules[(k,'갑옷')]='I05 특정 로빈 타입당 펄스 위력 +15% (계열 통일 필요)'
for k in ('갑옷','방패','투구','신발'):
    rules[(k,'포대')]='I18 특정 타입 추가 피해/포탄 크기 (전투 소비 확인 필요)'
matrix=[dict(provider=a,receiver=b,result=rules.get((a,b),'직접 인접 효과 없음')) for a in kinds for b in kinds]
assert len(matrix)==225
with (OUT/'PAIR_MATRIX.csv').open('w',encoding='utf-8-sig',newline='') as f:
    writer=csv.DictWriter(f,fieldnames=['provider','receiver','result']);writer.writeheader();writer.writerows(matrix)

samples=[
 ('새 연계', '로키를 검 옆으로 이동', '+ 검 A 담금질: 공격력 100 → 125', '배치 가능 · 보급력 3/10 → 7/10', 'gain'),
 ('이득과 손실', '로키를 다른 검 옆으로 이동', '− 검 A: 125 → 100<br>+ 검 B: 80 → 100', '기존 대상과 새 대상 모두 표시', 'loss'),
 ('독립 조건 해제', '동료를 독립 행동 동료 옆에 배치', '! 이웃 동료의 독립 행동 해제<br>+ 이 동료의 인접 조건 충족', '나쁜 변화부터 표시', 'loss'),
 ('전투 조건 대기', '성 체력 50% 이하에서 회복하는 동료', '◇ 배치 완료 후 체력 50% 이하일 때 회복', '배치 가능 · 지금 회복하지 않음', 'wait'),
 ('배치 불가', '점유 칸과 겹침', '× 다른 아이템과 2칸 겹침', '놓을 수 없어 예상 연계 적용 안 됨', 'bad'),
 ('상한 도달', '얼음 정수를 포대 옆으로 이동', '= 포대 쿨타임 감소 60% 한도<br>추가 쿨타임 효과 없음', '현재는 집계 시안 · 전투 소비 확인 필요', 'wait'),
 ('원거리 연계', '감전 제공 동료와 방전 동료 편성', '+ 감전 축적 → 방전 소비<br>◇ 감전이 쌓인 적에게만 피해', '인접 무관 · 확정 피해로 합산하지 않음', 'gain'),
 ('다른 히어로', '디아나 전용 총 상세', '디아나 얼굴 배지 · 보유<br>디아나 선택 시 사용 가능', '드래그 불가 · 탭 상세', 'bad'),
]
cards=''.join(f'<option value="{i}">{html.escape(s[0])}</option>' for i,s in enumerate(samples))
table=''.join('<tr>'+''.join(f'<td>{html.escape(str(r[k]))}</td>' for k in ('id','name','size','ability','condition','robin','diana','max'))+'</tr>' for r in rows)
matrixhtml='<table><tr><th>제공 ↓ / 수혜 →</th>'+''.join(f'<th>{k}</th>' for k in kinds)+'</tr>'
for a in kinds:
    matrixhtml+=f'<tr><th>{a}</th>'+''.join(f'<td>{html.escape(rules.get((a,b),"—"))}</td>' for b in kinds)+'</tr>'
matrixhtml+='</table>'
page='''<!doctype html><html lang="ko"><meta charset="utf-8"><title>드래그 정보 시안</title>
<style>body{margin:24px;background:#101b2b;color:#e5ebf5;font:15px system-ui}h1{font-size:24px}p{color:#b7c9dd}select,input{padding:10px;background:#20344d;color:white;border:1px solid #59708a}section{margin:24px 0} .preview{display:flex;gap:24px;align-items:center;flex-wrap:wrap}.panel{width:320px;min-height:240px;border:2px solid #58c6c7;border-radius:12px;background:#192b40;padding:16px;box-shadow:0 12px 35px #0008}.panel h3{margin:0 0 16px}.panel div{line-height:1.8}.foot{border-top:1px solid #48617c;margin-top:14px;padding-top:8px}.grid{display:grid;grid-template-columns:repeat(6,48px);grid-template-rows:repeat(4,48px);gap:3px}.cell{background:#172d49;border:1px solid #48617c;display:grid;place-items:center}.source{background:#38707b;border:2px solid #5df6c5}.target{border:2px solid #ffd36c}.loss{border-color:#ffb260}.wait{border-color:#b09cff}.bad{border-color:#ff7786}.wrap{overflow:auto;max-height:600px}table{border-collapse:collapse;font-size:12px;min-width:1400px}td,th{padding:10px;border:1px solid #354a64;vertical-align:top;min-width:90px}th{background:#243b56;position:sticky;top:0}a{color:#6dd8f5}small{color:#9aafc8}</style>
<h1>드래그 중 기능·상호작용 표시 시안</h1><p>읽기 전용 UI 시안 · 예시 수치는 설명용 · 게임에 적용하지 않음</p>
<section><select id="scenario">OPTIONS</select><div class="preview" style="margin-top:20px"><div class="grid" id="grid"></div><div class="panel" id="panel"></div></div><p>+ 새로 생김　− 사라짐　= 유지　◇ 전투 조건 대기　× 배치 불가</p></section>
<section><h2>225개 방향별 조합</h2><small>—는 직접 인접 효과 없음. 원거리 상태·영웅 연계는 동료 상세표와 본문 별도 규칙을 함께 사용합니다.</small><div class="wrap">MATRIX</div></section>
<section><h2>동료 64종 · 히어로 연계 192개</h2><input id="filter" placeholder="이름·조건·효과 검색"><div class="wrap"><table id="allies"><thead><tr><th>ID</th><th>이름</th><th>칸</th><th>고유 능력</th><th>조건</th><th>로빈</th><th>디아나</th><th>맥스</th></tr></thead><tbody>ROWS</tbody></table></div></section>
<p><a href="../DRAG_PREVIEW_DESIGN.md">전체 설계</a> · <a href="ALLIES_CASES.md">동료별 상세</a> · <a href="PAIR_MATRIX.csv">조합표 CSV</a></p>
<script>const samples=SAMPLES;const grid=document.querySelector('#grid');for(let i=0;i<24;i++){let d=document.createElement('div');d.className='cell'+(i===14?' source':i===13||i===15?' target':'');d.textContent=i===14?'이동':i===13?'검 A':i===15?'검 B':'';grid.append(d)}function show(){const s=samples[document.querySelector('#scenario').value];let p=document.querySelector('#panel');p.className='panel '+s[4];p.innerHTML='<h3>'+s[0]+'</h3><small>'+s[1]+'</small><div style="margin-top:16px">'+s[2]+'</div><div class="foot">'+s[3]+'</div>'}document.querySelector('#scenario').onchange=show;show();document.querySelector('#filter').oninput=e=>{for(const r of document.querySelectorAll('#allies tbody tr'))r.hidden=!r.textContent.includes(e.target.value)};</script></html>'''
page=page.replace('OPTIONS',cards).replace('MATRIX',matrixhtml).replace('ROWS',table).replace('SAMPLES',json.dumps(samples,ensure_ascii=False))
(OUT/'preview.html').write_text(page,encoding='utf-8')
print('PASS: 64 ally cases, 192 hero links, 225 directed pairs, 8 selectable mockups')
