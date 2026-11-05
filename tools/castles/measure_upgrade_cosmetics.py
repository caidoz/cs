"""Measure generated alpha bounds and emit metadata; never changes image pixels."""
from PIL import Image
from pathlib import Path
import re,json
root=Path(__file__).resolve().parents[2]
all_frames=[]
for c in range(10):
 name='parts.png' if c==0 else f'parts-{c+1:02}.png'
 im=Image.open(root/'Resources/res/castle_upgrades_v1'/name)
 assert im.size==(1536,1024) and im.mode=='RGBA',(name,im.size,im.mode)
 alpha=im.getchannel('A');hist=alpha.histogram()
 assert hist[0]>im.width*im.height*.2,(name,'background not transparent')
 counts=[]
 for y in range(im.height):
  hist=alpha.crop((0,y,im.width,y+1)).histogram();counts.append(sum(hist[21:]))
 boundaries=[0]
 for lo,hi in [(243,280),(480,520),(720,785)]:
  minimum=min(counts[lo:hi]);ys=[y for y in range(lo,hi) if counts[y]==minimum]
  boundaries.append(ys[len(ys)//2])
 boundaries.append(1024)
 frames=[]
 for row in range(4):
  rowframes=[]
  for lv in range(6):
   box=(lv*256,boundaries[row],(lv+1)*256,boundaries[row+1])
   bb=alpha.crop(box).point(lambda a:255 if a>20 else 0).getbbox();assert bb,(name,row,lv)
   x,y,x1,y1=bb;assert x>1 and x1<255,(name,'touching column',row,lv,bb)
   rowframes.append([box[0]+x,box[1]+y,x1-x,y1-y])
  frames.append(rowframes)
 all_frames.append(frames)
rigtext=(root/'Classes/Data/IndividualCastleV4.h').read_text(encoding='utf-8-sig')
rigs=[]
for line in rigtext.splitlines():
 if line.strip().startswith('{'):
  n=[float(x) for x in re.findall(r'\d+(?:\.\d+)?',line)]
  if len(n)>18:rigs.append(n)
mounts=[]
for c,r in enumerate(rigs):
 im=Image.open(root/f'Resources/res/castle_cannon_v2/unarmed-{c+1:02}.png');a=im.getchannel('A')
 x,y,w,h=map(int,r[:4]);tip=None
 for yy in range(y,min(y+80,im.height)):
  xs=[xx for xx in range(x,min(x+w,im.width)) if a.getpixel((xx,yy))>180]
  if xs:tip=(sum(xs)/len(xs),yy);break
 assert tip;mounts.append([round(tip[0]),tip[1]+134,120])
mounts[7]=[207,350,100] # Castle 8's crown mounts to the left dome, not the barrel vault.
header='#pragma once\n// Read-only alpha bounds; every mount is in the original castle source coordinate system.\nnamespace CastleUpgradeCosmetics {\nstruct Frame {int x,y,w,h;};\nstatic const Frame Frames[10][4][6]={\n'
for frames in all_frames:
 header+=' {\n'
 for row in frames:header+='  {'+','.join('{'+','.join(map(str,f))+'}' for f in row)+'},\n'
 header+=' },\n'
header+='};\nstruct SpireMount {int x,bottom,width;};\nstatic const SpireMount Spires[10]={\n'
for m in mounts:header+=' {'+','.join(map(str,m))+'},\n'
header+='};\nstruct ArmorMount {float x,y,width;};\nstatic const ArmorMount Armor[10]={\n'
# Centers measured from each original crest, rather than an inferred room rectangle.
armor=[[630,589,194],[599,578,272],[618,799,176],[568,844,213],[517,868,231],[601,950,214],[528,939,204],[542,983,204],[505,1039,191],[484,1080,174]]
for m in armor:header+=' {'+','.join(map(str,m))+'},\n'
header+='};\n}\n' 
(root/'Classes/Data/CastleUpgradeCosmetics.h').write_text(header,encoding='utf-8')
meta={'atlasSize':[1536,1024],'frames':all_frames,'spires':mounts,'armor':armor,'source':'built-in image_gen','policy':'images copied unchanged; frame bounds measured from alpha'}
p=root/'reports/castle_upgrades';p.mkdir(parents=True,exist_ok=True)
(p/'metadata.json').write_text(json.dumps(meta,indent=2),encoding='utf-8')
print('PASS 10 transparent atlases, 240 frame bounds, registered castle mounts')
