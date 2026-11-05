"""Register fleet PNGs without changing any pixels. Runtime cuts use uniform scale."""
from pathlib import Path
from PIL import Image
import json
from collections import deque
root=Path(__file__).resolve().parents[2]
assets=root/'Resources/res/hybrid_sd3d'
# Authored landmarks measured from each complete assembled castle, in source pixels.
# width,height,row stride, roof beam, facade bottom/width, deck floor, room aperture, visual rows.
landmarks=[
(658,389,389,138,330,395,285,(150,138,130,174),2),
(512,512,512,212,460,350,425,(150,214,110,222),3),
(512,512,512,176,452,350,420,(146,180,110,248),3),
(512,512,512,215,452,310,350,(155,224,100,205),5),
(512,512,512,200,452,320,350,(145,205,120,225),5),
(512,512,512,190,440,345,405,(113,194,130,220),6),
(512,512,512,142,452,365,420,(178,145,102,282),6),
(512,512,512,155,465,350,392,(137,158,100,281),7),
(512,512,512,155,435,345,400,(135,158,88,245),6),
]
def largest_bounds(mask):
 w,h=mask.size; data=bytearray(mask.tobytes()); best=(0,None)
 for start in range(w*h):
  if not data[start]:continue
  data[start]=0;q=deque([start]);count=0;x0=w;y0=h;x1=y1=0
  while q:
   k=q.popleft();x=k%w;y=k//w;count+=1;x0=min(x0,x);x1=max(x1,x);y0=min(y0,y);y1=max(y1,y)
   for xx,yy in ((x-1,y),(x+1,y),(x,y-1),(x,y+1)):
    if 0<=xx<w and 0<=yy<h:
     j=yy*w+xx
     if data[j]:data[j]=0;q.append(j)
  if count>best[0]:best=(count,(x0,y0,x1+1,y1+1))
 return best[1]
rows=[];manifest=[]
for n,entry in enumerate(landmarks,2):
 w,h,stride,roof,bottom,facade,deck,room,count=entry
 frames=[]
 for kind in ('closed','open','parts'):
  im=Image.open(assets/f'fleet-{n:02}-{kind}.png')
  assert im.mode=='RGBA'
  if kind!='parts': assert im.size==((1974,797) if n==2 else (1536,1024))
 im=Image.open(assets/f'fleet-{n:02}-parts.png')
 alpha=im.getchannel('A').point(lambda v:255 if v>=160 else 0)
 for row in range(2):
  group=[]
  for lv in range(6):
   x=lv*362;y=0 if row==0 else 390
   # Hide the generated gun carriage wheels below its mounting saddle.
   box=(x,y,x+362,226 if row==0 else 724)
   b=(alpha.crop(box).getbbox() if row==0 else largest_bounds(alpha.crop(box)));assert b
   group.append([x+b[0],y+b[1],b[2]-b[0],b[3]-b[1]])
  frames.append(group)
 wheels=2 if n<5 else 3 if n<8 else 4
 radius=42 if n==2 else 34 if wheels==2 else 27 if wheels==3 else 24
 axle=(360 if n==2 else 488 if wheels==4 else 486)
 total=max(h,axle+radius)
 data=[w,h,stride,roof,bottom,facade,deck,*room,count,wheels,radius,axle,total]
 rows.append(' {'+','.join(map(str,data))+',{'+','.join('{'+','.join(map(str,f))+'}' for f in frames[0])+'},{'+','.join('{'+','.join(map(str,f))+'}' for f in frames[1])+'}}')
 manifest.append(dict(castle=n,landmarks=data,cannons=frames[0],wheels=frames[1]))
header='''#pragma once
namespace HybridFleet {
struct Frame {int x,y,w,h;};
struct Rig {
 int w,h,stride,roof,facadeBottom,facadeWidth,deckY;
 int roomX,roomY,roomW,roomH,rooms,wheelCount,radius,axleY,totalH;
 Frame guns[6],wheels[6];
};
static const Rig Rigs[9]={
'''+',\n'.join(rows)+'\n};\ninline int Image(int castle,int kind){return HYBRID_FLEET_FIRST_IMG+(castle-1)*3+kind;}\n}\n'
(root/'Classes/Data/HybridCastleFleet.h').write_text(header,encoding='utf-8')
(assets/'fleet-registration.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
print('Registered 9 complete castle atlases, 54 cannons, 54 rotating wheels; PNGs unchanged.')
