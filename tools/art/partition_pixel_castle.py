"""Partition the approved generated castle; preserve original UI and runtime anchors."""
from pathlib import Path
import shutil
from PIL import Image, ImageDraw
import json

ROOT = Path(__file__).resolve().parents[2]
DEST = ROOT / 'Resources/res/castle_pixel_01_v1'
DEST.mkdir(parents=True, exist_ok=True)
source = Image.open(DEST / 'source.png').convert('RGBA')
canvas = Image.new('RGBA', (1089, 1445))
# Align the roof/deck, room floors and chassis with the existing native anchors.
bands = [(0,320,83,369),(320,500,369,520),(500,770,520,748),
         (770,1065,748,1000),(1065,1418,1000,1335)]
for sy, ey, dy, by in bands:
    part = source.crop((20,sy,1068,ey)).resize((1000,by-dy), Image.Resampling.NEAREST)
    canvas.alpha_composite(part, (48,dy))
rooms = [(196,569,222,160),(441,569,215,160),(681,569,221,160),
         (196,795,319,180),(550,795,352,180)]
hull = canvas.copy()
for i,(x,y,w,h) in enumerate(rooms):
    canvas.crop((x,y,x+w,y+h)).save(DEST / f'room-{i+1}.png')
    ImageDraw.Draw(hull).rectangle((x,y,x+w-1,y+h-1), fill=(0,0,0,0))
# Independent wheel sprites rotate around the original hubs.
for i,(x,y,r) in enumerate([(110,1347,91),(978,1347,91)]):
    wheel = source.crop((x-r,y-r,x+r,y+r))
    mask = Image.new('L', wheel.size)
    ImageDraw.Draw(mask).ellipse((0,0,181,181), fill=255)
    wheel.putalpha(mask)
    wheel.save(DEST / f'wheel-{i+1}.png')
    # Cut baked wheels out of the chassis; the separate wheels cover this cut.
    cx=48+(x-20)*1000/1048; cy=1000+(y-1065)*335/353
    ImageDraw.Draw(hull).ellipse((cx-92,cy-92,cx+92,cy+92), fill=(0,0,0,0))
hull.save(DEST / 'hull.png')
# Flat opaque shutter: subdued horizontal boards, no columns, ornaments or relief.
cover = Image.new('RGBA',(1000,610),(64,43,35,255))
draw = ImageDraw.Draw(cover)
for row,y in enumerate(range(0,610,50)):
    draw.rectangle((0,y,999,min(609,y+47)),
                   fill=(68,46,37,255) if row%2==0 else (64,43,35,255))
    if y+48<610:
        draw.rectangle((0,y+48,999,min(609,y+49)),fill=(53,36,30,255))
if (DEST / 'cover-convex-source.png').exists():
    # Preserve the generated shallow-convex wall, including its return faces.
    shutil.copyfile(DEST / 'cover-convex-source.png', DEST / 'cover.png')
else:
    cover.save(DEST / 'cover.png')
(DEST / 'parts.json').write_text(json.dumps({'canvas':[1089,1445], 'rooms':rooms,
    'bands':bands,'source':'built-in image_gen toned edit',
    'parts':['hull','room-1','room-2','room-3','room-4','room-5','wheel-1','wheel-2','cover']},indent=2))
print('Partitioned castle into hull, five rooms, two wheels and opaque timber cover')
