"""Select/extract imagegen components without stretching or authoring runtime copies."""
from pathlib import Path
import argparse,json,math,re,shutil
import cv2
import numpy as np
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'asset_library/work/all-castles-matte-20261125'
parser=argparse.ArgumentParser()
parser.add_argument('--promote',action='store_true')
parser.add_argument('--partial',action='store_true')
args=parser.parse_args()
plan=json.loads((WORK/'plan.json').read_text(encoding='utf-8-sig'))
OUT=WORK/'selected-final';OUT.mkdir(exist_ok=True)
rows=[dict(n=1,w=256,h=294,wheel=50,foot=77,deck=47,gunW=112,gunH=96,type='Stone')]
DECK={2:57,3:42,4:32,5:44,6:40,7:35,8:33,9:30,10:31,11:39,12:33,13:36,14:43,15:41,16:48,17:45,18:34,19:35}
def crop_alpha(im):
    b=im.getchannel('A').point(lambda a:255 if a>128 else 0).getbbox()
    if not b:raise ValueError('empty component')
    return im.crop(b)
def resize(im,w):
    return im.resize((w,round(im.height*w/im.width)),Image.Resampling.LANCZOS)
for spec in plan:
    n=spec['n'];path=WORK/f'stage-{n:02}-parts-source.png'
    if not path.exists():
        if args.partial:continue
        raise FileNotFoundError(path)
    im=Image.open(path).convert('RGBA');a=np.asarray(im)
    _,labels,stats,_=cv2.connectedComponentsWithStats((a[:,:,3]>128).astype('uint8'),8)
    parts=[tuple(map(int,s)) for s in stats[1:] if s[4]>800]
    hull=max(parts,key=lambda s:s[4])
    rights=[s for s in parts if s[0]+s[2]*.5>hull[0]+hull[2]]
    wheels=[s for s in rights if .82<s[2]/s[3]<1.22]
    if not wheels:raise ValueError((n,'no round wheel',parts))
    wheel=max(wheels,key=lambda s:s[1]+s[3]*.5)
    guns=[s for s in rights if s!=wheel]
    if not guns:raise ValueError((n,'no separate turret',parts))
    gun=max(guns,key=lambda s:s[4])
    def isolate(part):
        x,y,w,h,_=part;label=int(labels[y:y+h,x:x+w][(a[y:y+h,x:x+w,3]>128)][0])
        mask=cv2.dilate((labels==label).astype('uint8'),np.ones((3,3),np.uint8))
        pixels=a.copy();pixels[mask==0,3]=0
        return Image.fromarray(pixels).crop((x,y,x+w,y+h))
    body=isolate(hull)
    override=WORK/f'stage-{n:02}-hull-source.png'
    if override.exists():body=crop_alpha(Image.open(override).convert('RGBA'))
    scale=max(spec['w']/body.width,spec['h']/body.height,
              (rows[-1]['w']+1)/body.width,(rows[-1]['h']+1)/body.height)
    w,h=round(body.width*scale),round(body.height*scale)
    # One scale for the complete hull. Integer rounding is the only ratio error.
    body=body.resize((w,h),Image.Resampling.LANCZOS)
    wx,wy,ww,wh,_=wheel;gx,gy,gw,gh,_=gun
    whl=resize(isolate(wheel),spec['wheel'])
    turret=resize(isolate(gun),spec['gunW'])
    for kind,asset in [('castle',body),('wheel',whl),('turret',turret)]:
        asset.save(OUT/f'portrait-{kind}-{n:02}.png')
    rows.append(dict(n=n,w=w,h=h,wheel=whl.height,foot=round(turret.width*(.30 if n<=5 else .40)),deck=DECK[n],
                     gunW=turret.width,gunH=turret.height,type=spec['type'],source=path.name,hull_source=override.name if override.exists() else path.name,
                     source_bounds=dict(hull=hull,gun=gun,wheel=wheel),uniform_scale=scale))
assert all(b['w']>a['w'] and b['h']>a['h'] for a,b in zip(rows,rows[1:]))
if not args.partial:assert len(rows)==19 and rows[-1]['h']/rows[0]['h']>=2.5
report={'stages':rows,'generation':'built-in image_gen; approved first-castle matte reference',
        'source_aspect_preserved':True,'native_height_ratio':rows[-1]['h']/294,
        'native_width_ratio':rows[-1]['w']/256}
(WORK/'selected-finals.json').write_text(json.dumps(report,indent=2)+'\n')
if args.promote:
    assert not args.partial,'Partial drafts cannot be promoted'
    cat=json.loads((ROOT/'content/runtime-assets.json').read_text(encoding='utf-8'))
    known={a['target']:a for a in cat['assets']}
    backup=WORK/'previous-production';backup.mkdir(exist_ok=True)
    for p in OUT.glob('*.png'):
        master=ROOT/known['res/'+p.name].get('original_source',known['res/'+p.name]['source'])
        if not (backup/p.name).exists():shutil.copy2(master,backup/p.name)
        shutil.copy2(p,master)
    hp=ROOT/'Classes/Data/PortraitCastleArt.h';text=hp.read_text(encoding='utf-8')
    sizes=','.join('{%d,%d}'%(s['w'],s['h']) for s in rows)
    text=re.sub(r'static const Size Sizes\[Count\]=\{.*?\};','static const Size Sizes[Count]={'+sizes+'};',text)
    start=text.index('inline float WheelSize(')
    factor=max(1.,max((.80 if s['n']<=5 else .84)+(s['gunW']-s['foot'])/s['w'] for s in rows))
    text=text[:start]+('static constexpr float MaxAssemblyRatio='+str(round(factor+0.001,4))+'f;\n'
        'static const int WheelPixels[Count]={'+','.join(str(s['wheel']) for s in rows)+'};\n'
        'static const int DeckPixels[Count]={'+','.join(str(s['deck']) for s in rows)+'};\n'
        'inline float WheelSize(int c){return (float)WheelPixels[c];}\n'
        'inline float FrontWheelAt(int c){return c<5?.80f:.84f;}\n'
        'inline float CannonBaseFromFloor(int c){return (float)DeckPixels[c]-10.f;}\n'
        'static const int CannonFootX[Count]={'+','.join(str(s['foot']) for s in rows)+'};\n}\n')
    hp.write_text(text,encoding='utf-8')
print(json.dumps(report,indent=2))
