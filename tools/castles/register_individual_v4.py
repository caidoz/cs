"""Register selected exterior originals and circular rotating wheel overlays.

No painting, stretching or replacement of the approved original artwork.
"""
from pathlib import Path
import json
import shutil
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / 'content/castles/individual_castles_v4'
OUT = ROOT / 'Resources/res/castle_individual_v4'
OUT.mkdir(parents=True, exist_ok=True)
# Original-image pixel coordinates, measured against the selected artwork.
# wheel left/right x, center y, inner rotating radius, floor y, hero x, muzzle x/y
RIGS = [
 (465,1075,835,122,714,1230,985,322),
 (388,958,963,122,800,1175,1140,420),
 (397,834,1074,96,940,983,1120,650),
 (392,776,1155,103,1014,955,1055,680),
 (340,740,1257,105,1105,920,1055,710),
 (366,695,1361,87,1250,920,1020,900),
 (295,711,1382,94,1240,892,1010,920),
 (287,708,1408,92,1280,895,960,955),
 (261,629,1492,94,1370,855,923,1000),
 (278,655,1507,91,1390,804,887,1105),
]
# Width grows 15% as much as height overall; native aspect is always preserved.
WIDTHS = [342,348,354,359,365,371,376,399,405,411]
rows=[]
names=[]
for i,(rig,width) in enumerate(zip(RIGS,WIDTHS),1):
    file=f'castle-{i:02}.png'
    im=Image.open(SOURCE/file).convert('RGBA')
    box=im.getchannel('A').point(lambda x:255 if x>=192 else 0).getbbox()
    shutil.copy2(SOURCE/file, OUT/file)
    lx,rx,cy,r,floor,hero,mx,my=rig
    for side,cx in enumerate((lx,rx)):
        wheel=im.crop((cx-r,cy-r,cx+r,cy+r))
        mask=Image.new('L',wheel.size)
        ImageDraw.Draw(mask).ellipse((0,0,2*r-1,2*r-1),fill=255)
        from PIL import ImageChops
        wheel.putalpha(ImageChops.multiply(wheel.getchannel('A'),mask))
        wheel.save(OUT/f'wheel-{i:02}-{side}.png')
    x,y,x2,y2=box
    row=[x,y,x2-x,y2-y,lx,rx,cy,r,floor,hero,mx,my,width]
    rows.append(row)
    names += [f'\t"castle_individual_v4/castle-{i:02}",',f'\t"castle_individual_v4/wheel-{i:02}-0",',f'\t"castle_individual_v4/wheel-{i:02}-1",']
heights=[r[3]*r[-1]/r[2] for r in rows]
assert all(b>a for a,b in zip(heights,heights[1:])), heights
assert heights[-1] < 761
(ROOT/'Classes/IndividualCastleNames.inc').write_text('\n'.join(names)+'\n',encoding='utf-8')
(ROOT/'Classes/Data/IndividualCastleV4.h').write_text(
 '#pragma once\nnamespace IndividualCastleV4 {\n'
 'struct Rig { int x,y,w,h,lx,rx,cy,r,floor,hero,mx,my; float width; };\n'
 'static const Rig Rigs[10]={\n'+''.join(' {'+','.join(map(str,r[:-1]))+f',{r[-1]}.0f'+'},\n' for r in rows)+'};\n}\n',encoding='utf-8')
(SOURCE/'runtime-registration.json').write_text(json.dumps({'widths':WIDTHS,'heights':heights,'rigs':rows,'room_interior':'pending','upgrade_exteriors':'base exterior shared'},indent=2),encoding='utf-8')
print('Registered 10 originals, 20 wheel overlays. Heights:', [round(h,1) for h in heights])
