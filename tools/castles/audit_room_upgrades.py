"""Read-only pixel audit of generated atlases; write registration and review HTML."""
from pathlib import Path
import hashlib, json, html
import numpy as np
from PIL import Image

root = Path(__file__).resolve().parents[2]
assets = root / 'Resources/res/castle_room_upgrades_v3'
generation = json.loads((assets / 'generation.json').read_text(encoding='utf-8'))
audit = []
sections = []
for spec in generation['atlases']:
    castle, count = spec['castle'], spec['rooms']
    path = assets / f'castle-{castle:02}.png'
    image = Image.open(path).convert('RGB')
    width, height = image.size
    rows = 5 if castle == 2 else count * 2
    frames = []
    for room in range(count):
        first_row = 3 if castle == 2 and room == 1 else room * 2
        previous = None
        for level in range(6):
            col, row = level % 3, first_row + level // 3
            left, right = col * width // 3, (col+1) * width // 3
            top, bottom = row * height // rows, (row+1) * height // rows
            ix, iy = (right-left)*3//100, (bottom-top)*3//100
            crop = (left+ix, top+iy, right-ix, bottom-iy)
            assert crop[0] >= 0 and crop[1] >= 0 and crop[2] <= width and crop[3] <= height
            tile = image.crop(crop)
            pixels = np.array(tile.resize((128,64)), dtype=np.float32)
            delta = None if previous is None else float(np.abs(pixels-previous).mean())
            assert delta is None or delta > 1.0, (castle,room,level,'duplicate state')
            frames.append(dict(room=room,level=level,crop=[crop[0],crop[1],crop[2]-crop[0],crop[3]-crop[1]],previous_delta=delta))
            previous = pixels
    audit.append(dict(castle=castle,theme=spec['theme'],file=path.name,size=image.size,rows=rows,rooms=count,frames=frames,sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    screenshots = ''.join(f'<figure><img loading="lazy" src="../../output/room-upgrades-1408/castle-{castle:02}-level-{lv}.png"><figcaption>Lv.{lv}</figcaption></figure>' for lv in range(6))
    sections.append(f'<section><h2>{castle}. {html.escape(spec["theme"])}</h2><div class="stages">{screenshots}</div><details><summary>생성 원본 · {count}개 방 × 6단계</summary><img class="atlas" src="../../Resources/res/castle_room_upgrades_v3/{path.name}"></details></section>')
(assets / 'registration.json').write_text(json.dumps(audit,ensure_ascii=False,indent=2),encoding='utf-8')
report = root / 'reports/art_direction/room_upgrades.html'
report.parent.mkdir(parents=True,exist_ok=True)
report.write_text('''<!doctype html><meta charset="utf-8"><title>Castle Survivor · 방 강화</title><style>
body{background:#102331;color:#e7e2cf;font-family:system-ui;margin:24px}h1{color:#e8bd68}.stages{display:grid;grid-template-columns:repeat(6,minmax(130px,1fr));gap:8px;overflow:auto}figure{margin:0}img{width:100%;height:auto}figcaption{text-align:center;padding:8px}.atlas{max-width:1000px}section{margin:32px 0}summary{cursor:pointer;padding:12px}
</style><h1>성별 기능성 방 · 기본 + 5단계 업그레이드</h1><p>기존 성·방 위치와 크기 유지. 생산 / 장비 연구 / 식음료·공연 / 도서·종교 / 왕실 특화. 아래는 실제 게임 캡처입니다.</p>'''+''.join(sections),encoding='utf-8')
print(f'PASS {len(audit)} atlases, {sum(a["rooms"] for a in audit)} facilities, {sum(len(a["frames"]) for a in audit)} distinct states; original images unchanged')
