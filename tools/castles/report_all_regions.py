"""Audit unchanged source PNGs and publish native screenshots (no raster edits)."""
from pathlib import Path
from PIL import Image
import json,hashlib,shutil
root=Path(__file__).resolve().parents[2]
assets=root/'Resources/res/stage_sd3d_v2'
report=root/'reports/art_direction/all-regions'
report.mkdir(parents=True,exist_ok=True)
audit=[]
for p in sorted(assets.glob('*.png')):
 im=Image.open(p)
 item=dict(file=p.name,size=im.size,mode=im.mode,sha256=hashlib.sha256(p.read_bytes()).hexdigest())
 if '-far' not in p.name:
  assert im.mode=='RGBA',p
  a=im.getchannel('A');item['alpha_extrema']=a.getextrema();assert item['alpha_extrema']==(0,255),p
  if '-rail' in p.name:
   x0=int(im.width*.01);x1=int(im.width*.99)
   rows=[sum(a.getpixel((x,y))>230 for x in range(x0,x1))/(x1-x0) for y in range(im.height//3)]
   item['rail_top_px']=next(i for i,r in enumerate(rows) if r>.99)
 audit.append(item)
(assets/'asset-audit.json').write_text(json.dumps(audit,indent=2),encoding='utf-8')
names=['Swamp','Forbidden Canyon','Atlantis','Underground Sewer','Adeline Plains','Firelands','Icelands','Thunderlands','Land of Light','Golem Gorge','Dark Gorge','Dragon Gorge','City of the Dead','Demon Castle','Space']
html=['<!doctype html><meta charset="utf-8"><title>All regional backgrounds</title><style>body{background:#101b28;color:#eef;font:16px system-ui;margin:24px}section{display:flex;gap:12px;overflow:auto}img{width:280px;height:auto}article{margin-bottom:32px}a{color:#8df}</style><h1>15 regions · SD 3D backgrounds</h1><p>Original pixel characters and bosses retained. Each row compares two scrolling phases in native game captures. Four viewport heights: 850 / 1136 / 1280 / 1408.</p>']
for n,name in enumerate(names,1):
 html.append(f'<article><h2>{n:02} · {name}</h2><section>')
 for height in [850,1136,1280,1408]:
  source=root/f'output/all-regions-{height}'
  dest=report/str(height);dest.mkdir(exist_ok=True)
  for phase in [0,1]:
   filename=f'region-{n:02d}-phase-{phase}.png'
   if (source/filename).exists():
    shutil.copy2(source/filename,dest/filename)
    html.append(f'<div><p>640 × {height} · phase {phase}</p><a href="all-regions/{height}/{filename}"><img loading="lazy" src="all-regions/{height}/{filename}"></a></div>')
 html.append('</section></article>')
(report.parent/'all-regions-review.html').write_text(''.join(html),encoding='utf-8')
print(json.dumps([x for x in audit if 'rail_top_px' in x],indent=2))
