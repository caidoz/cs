"""Create a local gallery of native captures (no image processing)."""
from pathlib import Path
import html
root=Path(__file__).resolve().parents[2]
out=root/'reports/art_direction/functional_castles.html'
parts=['<!doctype html><meta charset="utf-8"><title>Functional castle review</title>',
 '<style>body{background:#172531;color:#eee;font:16px sans-serif;margin:24px}section{display:flex;gap:12px;overflow:auto}figure{margin:8px;flex:none}img{width:320px;height:auto}a{color:#90dfd2}</style>',
 '<h1>생산 시설 · NPC · 대포 시험 발사</h1>',
 '<p>저등급 식량·공방 → 고등급 문화·럭셔리. 식량은 에너지 회복 속도, 그 외 시설은 골드 생산량에 연결됩니다.</p>']
for height in (850,1136,1280,1408):
 folder=root/f'output/functional-castles-{height}'
 parts.append(f'<h2>640 × {height}</h2><section>')
 for c in range(1,11):
  name=f'castle-{c:02}-crowd.png'
  if not (folder/name).exists():continue
  src=f'../../output/{folder.name}/{name}'
  parts.append(f'<figure><a href="{src}"><img loading="lazy" src="{src}"></a><figcaption>성 {c} · NPC 배치</figcaption></figure>')
 for name in ('facilities.png','facility-confirm.png'):
  if (folder/name).exists():
   src=f'../../output/{folder.name}/{name}'
   parts.append(f'<figure><a href="{src}"><img loading="lazy" src="{src}"></a><figcaption>{html.escape(name)}</figcaption></figure>')
 parts.append('</section>')
for height in (850,1136,1280,1408):
 folder=root/f'output/facility-economy-{height}'
 parts.append(f'<h2>실제 재화 연결 · 640 × {height}</h2><section>')
 for name in ('economy.png','confirm.png'):
  if (folder/name).exists():
   src=f'../../output/{folder.name}/{name}'
   parts.append(f'<figure><a href="{src}"><img loading="lazy" src="{src}"></a><figcaption>{html.escape(name)}</figcaption></figure>')
 parts.append('</section>')
out.parent.mkdir(parents=True,exist_ok=True);out.write_text('\n'.join(parts),encoding='utf-8')
print(out)
