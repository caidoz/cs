"""Measure authored PNGs without changing pixels; emit runtime registration."""
from pathlib import Path
from PIL import Image
import numpy as np,json,hashlib
root=Path(__file__).resolve().parents[2];assets=root/'Resources/res/castle_soft_sectors_v1'
lines=['#pragma once','namespace SoftCastle {','struct Crop {int x,y,w,h;};','static const Crop Bodies[10][2]={'];audit=[]
for c in range(10):
 p=assets/f'castle-{c+1:02}.png';im=Image.open(p);a=np.asarray(im)[:,:,3];half=im.width//2;boxes=[]
 for i in range(2):
  start=i*half;end=(i+1)*half if i==0 else im.width
  ys,xs=np.nonzero(a[:,start:end]>200);x0=int(xs.min())+start;y0=int(ys.min());x1=int(xs.max())+start+1;y1=int(ys.max())+1
  boxes.append([x0,y0,x1-x0,y1-y0])
 lines.append(' {'+','.join('{'+','.join(map(str,b))+'}' for b in boxes)+'},')
 audit.append(dict(file=p.name,size=im.size,crops=boxes,sha256=hashlib.sha256(p.read_bytes()).hexdigest()))
lines+=['};','static const MountedCannons::Frame Guns[60]={']
im=Image.open(assets/'cannons.png');a=np.asarray(im)[:,:,3]
for row in range(10):
 for col in range(6):
  left=round(col*im.width/6);right=round((col+1)*im.width/6);top=round(row*im.height/10);bottom=round((row+1)*im.height/10)
  ys,xs=np.nonzero(a[top:bottom,left:right]>200);assert len(xs)>0
  x=left+int(xs.min());y=top+int(ys.min());w=int(xs.max()-xs.min()+1);h=int(ys.max()-ys.min()+1)
  # Static open muzzles sit around 40% down the weapon's bounding box.
  lines.append(f' {{{x},{y},{w},{h},{round(w*.94)},{round(h*.40)}}},')
lines+=['};','struct Sector {float x,y,w,h,foot;};',
'static const int Counts[10]={1,2,2,3,3,4,4,5,5,5};',
'static const Sector Sectors[10][5]={',
' {{.08f,.48f,.55f,.23f,.69f}},',
' {{.12f,.42f,.40f,.34f,.75f},{.53f,.40f,.19f,.21f,.61f}},',
' {{.12f,.66f,.40f,.15f,.80f},{.34f,.36f,.28f,.24f,.60f}},',
' {{.30f,.53f,.35f,.29f,.80f},{.10f,.50f,.20f,.17f,.66f},{.68f,.70f,.22f,.12f,.82f}},',
' {{.12f,.70f,.52f,.15f,.84f},{.14f,.50f,.24f,.15f,.64f},{.40f,.28f,.28f,.28f,.56f}},',
' {{.18f,.73f,.58f,.14f,.87f},{.17f,.58f,.24f,.13f,.71f},{.55f,.58f,.22f,.13f,.71f},{.31f,.39f,.38f,.16f,.55f}},',
' {{.15f,.76f,.43f,.10f,.86f},{.62f,.76f,.25f,.10f,.86f},{.25f,.58f,.42f,.16f,.73f},{.28f,.35f,.39f,.17f,.52f}},',
' {{.23f,.68f,.40f,.18f,.85f},{.64f,.72f,.20f,.14f,.85f},{.13f,.46f,.23f,.13f,.58f},{.38f,.36f,.35f,.23f,.58f},{.76f,.47f,.15f,.11f,.58f}},',
' {{.20f,.78f,.55f,.10f,.88f},{.14f,.60f,.25f,.13f,.73f},{.68f,.62f,.18f,.11f,.73f},{.14f,.43f,.20f,.09f,.51f},{.43f,.51f,.22f,.13f,.64f}},',
' {{.37f,.80f,.48f,.08f,.88f},{.10f,.79f,.25f,.09f,.88f},{.15f,.45f,.22f,.09f,.54f},{.73f,.52f,.18f,.09f,.61f},{.38f,.46f,.34f,.24f,.69f}},',
'};',
'struct Axle {float x,y,r;};',
'static const Axle Wheels[10][4]={',
' {{.20f,.89f,.095f},{.73f,.89f,.095f}},',
' {{.245f,.911f,.082f},{.719f,.911f,.082f}},',
' {{.23f,.93f,.077f},{.77f,.93f,.077f}},',
' {{.275f,.937f,.078f},{.685f,.937f,.078f}},',
' {{.285f,.948f,.060f},{.515f,.948f,.060f},{.747f,.948f,.060f}},',
' {{.265f,.949f,.060f},{.505f,.949f,.060f},{.74f,.949f,.060f}},',
' {{.245f,.947f,.079f},{.505f,.947f,.079f},{.765f,.947f,.079f}},',
' {{.245f,.95f,.069f},{.43f,.95f,.069f},{.615f,.95f,.069f},{.80f,.95f,.069f}},',
' {{.20f,.952f,.071f},{.417f,.952f,.071f},{.63f,.952f,.071f},{.845f,.952f,.071f}},',
' {{.15f,.958f,.075f},{.385f,.958f,.075f},{.625f,.958f,.075f},{.86f,.958f,.075f}},',
'};','inline bool Enabled(){return !getenv("CS_LEGACY_CASTLE_ART") && !getenv("CS_PREVIOUS_CASTLE_ART");}','}']
(root/'Classes/Data/SoftCastleSectors.h').write_text('\n'.join(lines)+'\n',encoding='utf-8')
(assets/'registration.json').write_text(json.dumps(audit,indent=2),encoding='utf-8')
print('Registered ten paired exteriors/cutaways, 60 weapon frames and 34 sectors')
