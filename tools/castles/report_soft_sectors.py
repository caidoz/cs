from pathlib import Path
from PIL import Image
import json,hashlib,shutil
root=Path(__file__).resolve().parents[2];assets=root/'Resources/res/castle_soft_sectors_v1'
report=root/'reports/art_direction/soft-sectors';report.mkdir(parents=True,exist_ok=True)
audit=[]
for p in sorted(assets.glob('*.png')):
 im=Image.open(p);assert im.mode=='RGBA' and im.getchannel('A').getextrema()[0]==0,p
 audit.append(dict(file=p.name,size=im.size,sha256=hashlib.sha256(p.read_bytes()).hexdigest()))
assert len(audit)==12
(assets/'asset-audit.json').write_text(json.dumps(audit,indent=2),encoding='utf-8')
counts=[1,2,2,3,3,4,4,5,5,5]
html=['<!doctype html><meta charset="utf-8"><title>Castle Survivor · soft castle sectors</title><style>body{background:#172735;color:#f4eddf;font:16px system-ui;margin:24px}section{display:flex;gap:12px;overflow:auto}img{width:300px;height:auto}article{margin-bottom:28px}a{color:#fc9}</style><h1>Warm SD castles · integrated interior sectors</h1><p>Ten castles, 1–5 unequal architectural sectors, matte warm materials, bulkier distinct artillery. Catapult and triple missile launcher retain their original shape. Native 640px-wide captures at four heights; base/max and closed/open.</p>']
for c in range(1,11):
 html.append(f'<article><h2>Castle {c} · {counts[c-1]} sectors</h2>')
 for height in [850,1136,1280,1408]:
  source=root/f'output/soft-sectors-{height}';dest=report/str(height);dest.mkdir(exist_ok=True)
  html.append(f'<h3>640 × {height}</h3><section>')
  for grade in ['base','max']:
   for state in ['closed','open']:
    name=f'castle-{c:02d}-{grade}-{state}.png'
    if (source/name).exists():
     shutil.copy2(source/name,dest/name)
     html.append(f'<div><p>{grade} · {state}</p><a href="soft-sectors/{height}/{name}"><img loading="lazy" src="soft-sectors/{height}/{name}"></a></div>')
  html.append('</section>')
 html.append('</article>')
(report.parent/'soft-sectors-review.html').write_text(''.join(html),encoding='utf-8')
print('Audited 12 PNGs; native screenshots:',len(list(report.glob('*/*.png'))))
