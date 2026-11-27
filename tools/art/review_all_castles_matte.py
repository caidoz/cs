"""Composite selected independent sprites at shared scale, with no asset edits."""
from pathlib import Path
from PIL import Image,ImageDraw,ImageFont
import json,math

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'asset_library/work/all-castles-matte-20261125'
rows=json.loads((WORK/'selected-finals.json').read_text())['stages']
font=ImageFont.truetype(str(ROOT/'Resources/fonts/neodgm.ttf'),18)
def asset(kind,n):
    p=WORK/'selected-final'/f'portrait-{kind}-{n:02}.png'
    if n==1:p=ROOT/f'asset_library/production/portrait-{kind}-01.png'
    return Image.open(p).convert('RGBA')
def render(row,scale=1):
    n=row['n'];body=asset('castle',n);wheel=asset('wheel',n);gun=asset('turret',n)
    pad=12;ground=row['h']+row['wheel']*.58+pad
    extent=max(row['w'],row['w']*(.8 if n<=5 else .84)+row['gunW']-row['foot'])
    im=Image.new('RGBA',(math.ceil(extent+pad*2),math.ceil(ground+8)))
    bottom=ground-row['wheel']*.58
    count=2 if n<=5 else 3;positions=[.17,.8] if count==2 else [.15,.495,.84]
    dx=26*row['w']/256;dy=10*row['w']/256
    for at in positions:im.alpha_composite(wheel,(round(pad+row['w']*at+dx-wheel.width*.5),round(bottom+wheel.height*.08-dy-wheel.height*.5)))
    im.alpha_composite(body,(pad,round(bottom-row['h'])))
    for at in positions:im.alpha_composite(wheel,(round(pad+row['w']*at-wheel.width*.5),round(bottom+wheel.height*.08-wheel.height*.5)))
    x=round(pad+row['w']*positions[-1]-row['foot']);y=round(bottom-row['deck']-row['gunH'])
    if n==1:
        im.alpha_composite(gun.crop((0,0,112,96)),(x,y))
        rock=gun.crop((225,1,239,14)).resize((25,23),Image.Resampling.LANCZOS)
        im.alpha_composite(rock,(round(x+23-12.5),round(y+31-11.5)))
        im.alpha_composite(gun.crop((112,0,224,96)),(x,y));sx,sy,sw,sh=146,236,110,16
    else:
        split=int(gun.height*.72)
        base=gun.crop((0,split,min(gun.width,pad+row['w']-x),gun.height))
        im.alpha_composite(base,(x,y+split));im.alpha_composite(gun.crop((0,0,gun.width,split)),(x,y))
        sx=round(row['w']*.56);sy=row['h']-row['deck']+2;sw=row['w']-sx;sh=12
    im.alpha_composite(body.crop((sx,sy,sx+sw,sy+sh)),(pad+sx,round(bottom-row['h']+sy)))
    if scale!=1:im=im.resize((round(im.width*scale),round(im.height*scale)),Image.Resampling.LANCZOS)
    return im
pitch=600;base=max(r['h']+r['wheel'] for r in rows)+30
line=Image.new('RGBA',(pitch*19,base+90),'#10202b');d=ImageDraw.Draw(line)
d.line((0,base,pitch*19,base),fill='#54707c')
for i,row in enumerate(rows):
    im=render(row);line.alpha_composite(im,(i*pitch+8,base-im.height))
    d.text((i*pitch+16,base+12),f"{row['n']:02} | {row['w']} x {row['h']} | cannon {row['gunW']}",font=font,fill='#ecdfc4')
line.save(WORK/'all-19-native-lineup.png')
# Equal visible hull width matches the actual runtime camera rule.
pitch=430;base=850
line=Image.new('RGBA',(pitch*19,base+70),'#10202b');d=ImageDraw.Draw(line)
for i,row in enumerate(rows):
    im=render(row,256/row['w']);line.alpha_composite(im,(i*pitch+4,base-im.height));d.text((i*pitch+12,base+12),f"{row['n']:02}",font=font,fill='#ecdfc4')
line.save(WORK/'all-19-equal-width-lineup.png')
detail=Image.new('RGBA',(600*5,260*4),'#10202b');d=ImageDraw.Draw(detail)
for i,row in enumerate(rows):
    im=render(row);section=im.crop((0,max(0,im.height-215),min(590,im.width),im.height))
    x=(i%5)*600;y=(i//5)*260;detail.alpha_composite(section,(x,y+32));d.text((x+10,y+5),f"{row['n']:02}",font=font,fill='#ecdfc4')
detail.save(WORK/'all-19-emplacements.png')
print(WORK/'all-19-native-lineup.png')
