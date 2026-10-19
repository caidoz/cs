from pathlib import Path
from PIL import Image
import hashlib,json,zipfile
root=Path(__file__).resolve().parents[2]
assets=root/'content/castles/map_icons_v1'
rows=[]
for level in range(1,11):
 name=f'castle-map-{level:02}.png';p=assets/'png'/name
 with Image.open(p) as im:
  assert im.size==(1024,1024),(name,im.size)
  assert im.mode=='RGBA',(name,im.mode)
  a=im.getchannel('A');lo,hi=a.getextrema()
  assert lo==0 and hi==255,(name,lo,hi)
  assert all(a.getpixel(pos)==0 for pos in [(0,0),(1023,0),(0,1023),(1023,1023)]),name
  bounds=a.point(lambda v:255 if v>=192 else 0).getbbox()
  assert bounds and min(bounds[0],bounds[1],1024-bounds[2],1024-bounds[3])>=8,(name,bounds)
  zero=a.histogram()[0]/(1024*1024)
  assert .1<zero<.9,(name,zero)
  rows.append(dict(castleLevel=level,file='png/'+name,width=1024,height=1024,mode=im.mode,solidBounds=bounds,transparentFraction=round(zero,4),sha256=hashlib.sha256(p.read_bytes()).hexdigest()))
assert len(list((assets/'png').glob('*.png')))==10
assert len({row['sha256'] for row in rows})==10
manifest=json.loads((assets/'manifest.json').read_text(encoding='utf-8-sig'))
assert len(manifest['icons'])==10
for i,row in enumerate(manifest['icons']):
 assert row['castleIndex']==i and row['castleLevel']==i+1 and row['upgradeStage']==0
 assert (assets/row['file']).is_file()
with zipfile.ZipFile(assets/'castle-map-icons-1024.zip') as z:
 assert len(z.namelist())==10,z.namelist()
 assert {Path(n).name for n in z.namelist()}=={f'castle-map-{i:02}.png' for i in range(1,11)}
(assets/'validation.json').write_text(json.dumps({'status':'PASS','icons':rows},ensure_ascii=False,indent=2),encoding='utf-8')
print('PASS ten distinct 1024x1024 RGBA icons, transparent corners, framed silhouettes, manifest and ZIP contents')
