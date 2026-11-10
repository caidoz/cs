import json
from pathlib import Path
from PIL import Image
import numpy as np
from collections import deque
root=Path('Resources/res/merge_castle_rebuild')
for p in sorted(root.glob('*.png')):
 im=Image.open(p).convert('RGBA'); a=im.getchannel('A'); print(p.name,im.size,'bbox',a.point(lambda v:255 if v>128 else 0).getbbox(),'corner',im.getpixel((0,0)))
 if p.name.startswith('chassis'):
  mask=np.array(a)[::4,::4]<32;hh,ww=mask.shape;regions=[]
  for yy in range(hh):
   for xx in range(ww):
    if not mask[yy,xx]:continue
    q=deque([(xx,yy)]);mask[yy,xx]=False;pts=[]
    while q:
     x,y=q.popleft();pts.append((x,y))
     for nx,ny in ((x+1,y),(x-1,y),(x,y+1),(x,y-1)):
      if 0<=nx<ww and 0<=ny<hh and mask[ny,nx]:mask[ny,nx]=False;q.append((nx,ny))
    xs,ys=zip(*pts)
    if min(xs)==0 or min(ys)==0 or max(xs)==ww-1 or max(ys)==hh-1:continue
    if len(pts)>500:regions.append((min(xs)*4,min(ys)*4,(max(xs)+1)*4,(max(ys)+1)*4))
  print('holes',regions)
