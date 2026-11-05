"""Summarize native frame measurements and link unmodified review captures."""
from pathlib import Path
import re,json,statistics
root=Path(__file__).resolve().parents[2]
def samples(name):
 rows=re.findall(r'^detail cpu_ms=([\d.]+) frame_ms=([\d.]+) sprites=([\d.]+)',(root/'output'/name).read_text(),re.M)
 return dict(zip(('cpu_ms','frame_ms','sprites'),[statistics.mean(float(row[i]) for row in rows) for i in range(3)]))
result={'before':samples('ui-metal-profile.log'),'after':samples('ui-retro-profile.log'),'platform':'Win32 Debug, native equipment detail, 640 x 1408; CPU preparation and frame intervals, not GPU timing'}
folder=root/'reports/ui_retro';folder.mkdir(parents=True,exist_ok=True)
(folder/'performance.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
parts=['<!doctype html><meta charset="utf-8"><title>Retro UI review</title><style>body{background:#172531;color:#e4e6e4;font:16px sans-serif;margin:24px}section{display:flex;gap:16px;overflow:auto}img{width:320px}figure{margin:8px}a{color:#b8d6ca}</style>',
 '<h1>레트로 UI · 장비 상세 성능 수정</h1>',
 '<p>평면 색상, 얇은 픽셀 테두리. 장비 상세창 중복 렌더링 제거와 스프라이트·문자열 재사용 표 유지.</p>',
 f'<p>Win32 Debug 측정: 평균 프레임 {result["before"]["frame_ms"]:.1f} → {result["after"]["frame_ms"]:.1f} ms · 스프라이트 {result["before"]["sprites"]:.0f} → {result["after"]["sprites"]:.0f}. 기기별 실제 성능은 달라집니다.</p>']
for h in (850,960,1136,1408):
 parts.append(f'<h2>640 × {h}</h2><section>')
 for name in ('equipment.png','equipment-detail.png','equipment-stat.png','equipment-codex.png'):
  src=f'../../output/equipment-v2-{h}/{name}'
  parts.append(f'<figure><a href="{src}"><img loading="lazy" src="{src}"></a><figcaption>{name}</figcaption></figure>')
 parts.append('</section>')
parts.append('<h2>상점</h2><section>')
for name in ('recommended.png','supplies.png','packages.png'):
 src=f'../../output/shop-spec-review/{name}';parts.append(f'<figure><img src="{src}"></figure>')
parts.append('</section>')
(folder/'index.html').write_text('\n'.join(parts),encoding='utf-8');print(json.dumps(result,indent=2))
