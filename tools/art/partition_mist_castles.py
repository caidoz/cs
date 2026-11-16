"""Register approved clean castle sprites against the live game's fixed anchors.

No characters/UI are baked into these assets. Cropping and alpha partitioning only.
"""
from pathlib import Path
from PIL import Image, ImageDraw
import json
import sys
wheels_only = "--wheels-only" in sys.argv
import numpy as np

ROOT = Path(__file__).resolve().parents[2]
DEST = ROOT / 'Resources/res/castle_mist_v2'
ROOMS = [(196,569,222,160),(441,569,215,160),(681,569,221,160),
         (196,795,319,180),(550,795,352,180)]
LANDMARKS = [(.318,.390,.545,.715),(.285,.390,.550,.715),
             (.280,.375,.520,.690),(.280,.375,.525,.690),
             (.310,.400,.560,.735),(.345,.430,.580,.735),
             (.320,.410,.565,.720),(.345,.435,.590,.735),
             (.355,.445,.605,.760),(.355,.440,.585,.725)]
parts = ['hull','room-1','room-2','room-3','room-4','room-5','wheel-1','wheel-2','cover']
wheel_anchors = []
for stage, landmarks in enumerate(LANDMARKS, 1):
    src = Image.open(DEST / 'source' / f'castle-{stage:02}.png').convert('RGBA')
    src = src.crop(src.getchannel('A').getbbox())
    out = DEST / f'{stage:02}'
    out.mkdir(exist_ok=True)
    source_y = [0] + [round(v*src.height) for v in landmarks] + [src.height]
    target_y = [83,369,520,748,1000,1335]
    canvas = Image.new('RGBA',(1089,1445))
    for top,bottom,y,end in zip(source_y,source_y[1:],target_y,target_y[1:]):
        band = src.crop((0,top,src.width,bottom)).resize((1000,end-y),Image.Resampling.NEAREST)
        canvas.alpha_composite(band,(48,y))
    hull = canvas.copy()
    for i,(x,y,w,h) in enumerate(ROOMS):
        if not wheels_only: canvas.crop((x,y,x+w,y+h)).save(out / f'room-{i+1}.png')
        ImageDraw.Draw(hull).rectangle((x,y,x+w-1,y+h-1),fill=(0,0,0,0))
    anchors = []
    alpha = np.asarray(src)[:,:,3] > 128
    for side in range(2):
        points = []
        for y in range(int(src.height*.925),src.height-2):
            left = 0 if side == 0 else src.width*3//4
            row = alpha[y,:src.width//4] if side == 0 else alpha[y,left:]
            xs = np.flatnonzero(row)
            if len(xs): points.append((left+xs[0 if side==0 else -1],y))
        xy = np.asarray(points)
        fit = np.c_[2*xy[:,0],2*xy[:,1],np.ones(len(xy))]
        x,y,k = np.linalg.lstsq(fit,(xy**2).sum(1),rcond=None)[0]
        radius = (k+x*x+y*y)**.5
        cx = round(48+x*1000/src.width)
        cy = round(1000+(y-source_y[-2])*335/(src.height-source_y[-2]))
        # Registration stretches the source wheel differently on X and Y.
        # Remove its entire ellipse from the hull, then normalize the detached
        # wheel to a circle before rotation. A smaller circular cut leaves a
        # stationary crescent of the original rim outside the rotating sprite.
        rx = round(radius*1000/src.width)+2
        ry = round(radius*335/(src.height-source_y[-2]))+2
        if stage == 1:
            # The irregular chassis outline biases the contour fit toward the wall.
            # Use the actual painted hubs and outer tyre ellipse for this skin.
            cx,cy,rx,ry = (167,1223,108,88) if side == 0 else (940,1223,108,88)
        r = max(rx,ry)
        anchors.append([cx,cy,r])
        wheel = canvas.crop((cx-rx,cy-ry,cx+rx,cy+ry))
        mask = Image.new('L',wheel.size)
        ImageDraw.Draw(mask).ellipse((0,0,2*rx-1,2*ry-1),fill=255)
        from PIL import ImageChops
        wheel.putalpha(ImageChops.multiply(wheel.getchannel('A'),mask))
        wheel = wheel.resize((2*r,2*r),Image.Resampling.NEAREST)
        wheel.save(out / f'wheel-{side+1}.png')
        ImageDraw.Draw(hull).ellipse((cx-rx,cy-ry,cx+rx-1,cy+ry-1),fill=(0,0,0,0))
    hull.save(out / 'hull.png')
    wheel_anchors.append(anchors)
    if wheels_only: continue
    cover = Image.open(DEST / 'source' / f'cover-{stage:02}.png').convert('RGB')
    cover.resize((1000,610),Image.Resampling.NEAREST).save(out / 'cover.png')
    turret = Image.open(DEST / 'source' / f'turret-{stage:02}.png').convert('RGBA')
    turret = turret.crop(turret.getchannel('A').point(lambda v:255 if v>64 else 0).getbbox())
    turret.save(out / 'turret.png')
    if stage==1:
        empty = Image.open(DEST/'source/turret-empty-01.png').convert('RGBA')
        empty = empty.crop(empty.getchannel('A').point(lambda v:255 if v>64 else 0).getbbox())
        empty.resize(turret.size,Image.Resampling.NEAREST).save(out/'turret-empty.png')
(DEST / 'parts.json').write_text(json.dumps(dict(canvas=[1089,1445],rooms=ROOMS,
    landmarks=LANDMARKS,parts=parts,wheels=wheel_anchors,stages=10),indent=2))
(ROOT / 'Classes/CastleMistWheels.inc').write_text('static const int wheelAnchors[10][2][3]={\n'+
    ',\n'.join('{'+','.join('{'+','.join(map(str,w))+'}' for w in pair)+'}' for pair in wheel_anchors)+'\n};\n')
names = ''.join(f'\t"castle_mist_v2/{stage:02}/{part}",\n'
    for stage in range(1,11) for part in parts)
(ROOT / 'Classes/CastleMistNames.inc').write_text(names)
(ROOT / 'Classes/CastleMistTurretNames.inc').write_text(''.join(
    f'\t"castle_mist_v2/{stage:02}/turret",\n' for stage in range(1,11)))
print('Registered 101 runtime parts across ten castles')
