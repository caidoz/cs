"""Read-only alpha registration for generated atlases; never edits image pixels."""
from pathlib import Path
from PIL import Image
import json

ROOT = Path(__file__).resolve().parents[2]
ASSETS = ROOT / 'Resources/res/hybrid_sd3d'

def bounds(im, box):
    a = im.getchannel('A').crop(box).point(lambda v: 255 if v > 32 else 0)
    b = a.getbbox()
    assert b, box
    x,y,r,d = b
    return [box[0]+x, box[1]+y, r-x, d-y]

parts = Image.open(ASSETS/'parts.png')
assert parts.mode == 'RGBA' and parts.size == (1536,1024)
rows = [0,350,580,800,1024]
frames = [[bounds(parts,(c*256,rows[r],(c+1)*256,rows[r+1])) for c in range(6)] for r in range(4)]
wheels = Image.open(ASSETS/'wheels.png')
wheel_frames = [bounds(wheels,(round(c*wheels.width/6),0,round((c+1)*wheels.width/6),wheels.height)) for c in range(6)]
ui = Image.open(ASSETS/'ui.png')
ui_frames = [bounds(ui,(c*512,r*512,(c+1)*512,(r+1)*512)) for r in range(2) for c in range(3)]
for n in ['parts','wheels','ui','mid','rail']:
    im = Image.open(ASSETS/(n+'.png'))
    assert im.mode == 'RGBA', (n,im.mode)
    h = im.getchannel('A').histogram()
    assert h[0] > im.width*im.height*.05, (n,'missing alpha')

header = '#pragma once\n// Measured alpha bounds. Artwork is copied unchanged from image_gen.\nnamespace HybridSd3d {\nstruct Frame {int x,y,w,h;};\nstatic const Frame Parts[4][6]={\n'
for row in frames:
    header += ' {'+','.join('{'+','.join(map(str,f))+'}' for f in row)+'},\n'
header += '};\nstatic const Frame Wheels[6]={'+','.join('{'+','.join(map(str,f))+'}' for f in wheel_frames)+'};\n'
header += 'static const Frame Panels[6]={'+','.join('{'+','.join(map(str,f))+'}' for f in ui_frames)+'};\n}\n'
(ROOT/'Classes/Data/HybridSd3d.h').write_text(header,encoding='utf-8')
(ASSETS/'registration.json').write_text(json.dumps({'parts':frames,'wheels':wheel_frames,'panels':ui_frames},indent=2),encoding='utf-8')
print('PASS: 24 structural parts, 6 wheels, 6 UI panels; alpha validated')
print(header)
