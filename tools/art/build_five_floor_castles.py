"""Package AI castle repaints; only final, referenced parts enter the catalog."""
from pathlib import Path
import argparse
import json
import math
import shutil
import subprocess
import numpy as np
from PIL import Image, ImageDraw

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'asset_library/work/castle-equal-floors-20261123'
W,H=1089,1445
DECK=440
BODY_WIDTH=916
# Source positions in the approved 768x1024 open frame, bottom to top.
# Include the narrow dark margin above furniture so no baked-in item tips remain.
ROOMS=[(154,400+104*n,464,90) for n in range(4,-1,-1)]
COVER=(112,399,536,537)


def rgba(path):
    return Image.open(path).convert('RGBA')


def clean(image):
    a=np.array(image)
    a[a[:,:,3]<128]=0
    a[:,:,3][a[:,:,3]>=245]=255
    return Image.fromarray(a)


def uniform(image,scale):
    size=(max(1,round(image.width*scale)),max(1,round(image.height*scale)))
    result=image.resize(size,Image.Resampling.NEAREST)
    result.putalpha(image.getchannel('A').resize(size,Image.Resampling.LANCZOS))
    return result


def registration(frame):
    mask=np.array(frame.getchannel('A'))>128
    bbox=frame.getchannel('A').getbbox()
    wanted=(bbox[2]-bbox[0])*.72
    counts=mask.sum(axis=1)
    deck=next(y for y in range(round(frame.height*.20),round(frame.height*.48))
              if all(counts[y:y+4]>wanted))
    ys,xs=np.nonzero(mask[deck:round(frame.height*.84)])
    left,right=int(xs.min()),int(xs.max()+1)
    scale=BODY_WIDTH/(right-left)
    ox=(W-BODY_WIDTH)/2-left*scale
    oy=DECK-deck*scale
    assert oy+bbox[1]*scale>=-3, ('tower outside canvas',oy,bbox,scale)
    assert oy+bbox[3]*scale<H, ('chassis outside canvas',oy,bbox,scale)
    return scale,ox,oy,deck


def native(frame,reg):
    scale,ox,oy,_=reg
    result=Image.new('RGBA',(W,H))
    painted=uniform(frame,scale)
    result.alpha_composite(painted,(round(ox),round(oy)))
    return result


def source_rect(rect,frame):
    x,y,w,h=rect
    return [round(x*frame.width/768),round(y*frame.height/1024),
            round((x+w)*frame.width/768),round((y+h)*frame.height/1024)]


def native_rect(rect,frame,reg):
    s,ox,oy,_=reg
    x,y,r,b=source_rect(rect,frame)
    left,top,right,bottom=round(ox+x*s),round(oy+y*s),round(ox+r*s),round(oy+b*s)
    return [left,top,right-left,bottom-top]


def wheel_geometry(frame,reg,side):
    mask=np.array(frame.getchannel('A'))>128
    points=[]
    for y in range(round(frame.height*.89),frame.height):
        start,end=(0,round(frame.width*.28)) if side==0 else (round(frame.width*.72),frame.width)
        xs=np.flatnonzero(mask[y,start:end])
        if len(xs):points.append((start+xs[0 if side==0 else -1],y))
    xy=np.asarray(points,dtype=float)
    fit=np.c_[2*xy[:,0],2*xy[:,1],np.ones(len(xy))]
    x,y,k=np.linalg.lstsq(fit,(xy**2).sum(1),rcond=None)[0]
    radius=math.sqrt(max(1,k+x*x+y*y))
    assert frame.width*.06<radius<frame.width*.16, (side,x,y,radius)
    s,ox,oy,_=reg
    return [round(ox+x*s),round(oy+y*s),round(radius*s)]


def package():
    records=[]
    for i in range(1,11):
        pair_path=WORK/f'generated/castle-{i:02}.png'
        if not pair_path.exists():continue
        pair=rgba(pair_path)
        open_frame=clean(pair.crop((0,0,pair.width//2,pair.height)))
        closed_frame=clean(pair.crop((pair.width//2,0,pair.width,pair.height)))
        reg=registration(open_frame)
        full=native(open_frame,reg)
        closed=native(closed_frame,registration(closed_frame))
        full.save(WORK/f'final/castle-{i:02}-open.png')
        closed.save(WORK/f'final/castle-{i:02}-closed.png')
        hull=full.copy()
        # Quantize once so rounding never changes the height or spacing of a floor.
        top=native_rect(ROOMS[-1],open_frame,reg)
        pitch=round(104*open_frame.height/1024*reg[0])
        rooms=[[top[0],top[1]+pitch*n,top[2],top[3]] for n in range(4,-1,-1)]
        for room,(x,y,w,h) in enumerate(rooms):
            full.crop((x,y,x+w,y+h)).save(WORK/f'final/castle_mist_v2-{i:02}-room-{5 if room==0 else room}.png')
            ImageDraw.Draw(hull).rectangle((x,y,x+w-1,y+h-1),fill=(0,0,0,0))
        wheels=[]
        for side in range(2):
            x,y,r=wheel_geometry(open_frame,reg,side)
            wheel=full.crop((x-r,y-r,x+r,y+r))
            mask=Image.new('L',wheel.size)
            ImageDraw.Draw(mask).ellipse((0,0,2*r-1,2*r-1),fill=255)
            wheel.putalpha(Image.fromarray(np.minimum(np.array(wheel.getchannel('A')),np.array(mask))))
            wheel.save(WORK/f'final/castle_mist_v2-{i:02}-wheel-{side+1}.png')
            ImageDraw.Draw(hull).ellipse((x-r,y-r,x+r-1,y+r-1),fill=(0,0,0,0))
            wheels.append([x,y,r])
        hull.save(WORK/f'final/castle_mist_v2-{i:02}-hull.png')
        # All skins and the siege renderer share one registered closure area.
        cover=[175,548,740,760]
        x,y,w,h=cover
        # Both states share architecture; copy the continuous closed front only.
        panel=closed.crop((x,y,x+w,y+h)).convert('RGB').convert('RGBA')
        panel.save(WORK/f'final/castle_mist_v2-{i:02}-cover.png')
        # Wide room atlases use 2 columns x 12 rows; every tile keeps its aspect.
        atlas_path=WORK/f'generated/rooms-wide-{i:02}.png'
        if atlas_path.exists():
            art=rgba(atlas_path)
            out=Image.new('RGBA',art.size)
            for n in range(24):
                x0=round(n%2*art.width/2)+2;y0=round(n//2*art.height/12)+2
                x1=round((n%2+1)*art.width/2)-2;y1=round((n//2+1)*art.height/12)-2
                painted=clean(art.crop((x0,y0,x1,y1)))
                tile=Image.new('RGBA',painted.size,(33,27,40,255))
                tile.alpha_composite(painted)
                out.paste(tile,(x0,y0))
            out.save(WORK/f'final/castle_four_rooms_v5-rooms-{i:02}.png')
        records.append(dict(castle=i,rooms=rooms,cover=cover,wheels=wheels,registration=list(reg),
                            body_bounds=[round((W-BODY_WIDTH)/2),round((W+BODY_WIDTH)/2)]))
        print(f'PACKAGED castle {i:02}: five floors, continuous front, two registered wheels',flush=True)
    (WORK/'geometry.json').write_text(json.dumps(records,indent=2))
    gallery(records)


def gallery(records):
    rows=[]
    sheet=Image.new('RGB',(1600,5*510),'#303039')
    draw=ImageDraw.Draw(sheet)
    for n,r in enumerate(records):
        i=r['castle'];x=n%2*800;y=n//2*510
        for side,state in enumerate(('open','closed')):
            im=rgba(WORK/f'final/castle-{i:02}-{state}.png');im.thumbnail((370,460),Image.Resampling.LANCZOS)
            sheet.paste(im,(x+side*390+(370-im.width)//2,y+35),im)
            draw.text((x+side*390+25,y+10),f'{i:02} / {state.upper()}',fill='#e9dec5')
        rows.append(f'<h2>Castle {i:02}</h2><p><a href="../prompts/castle-{i:02}.txt">Castle prompt</a> / <a href="../prompts/rooms-wide-{i:02}.txt">Facility prompt</a></p><section><img src="../final/castle-{i:02}-open.png"><img src="../final/castle-{i:02}-closed.png"></section>')
    sheet.save(WORK/'review/all-ten-open-closed.png')
    live='<h2>Native game captures</h2><section><img src="../runtime/lobby-850/castle-proportions-01.png"><img src="../runtime/lobby-1408/castle-proportions-10.png"></section><p><a href="../asset-validation.json">Asset validation</a> / <a href="../runtime-validation.json">Native validation</a> / <a href="../scope-validation.json">Runtime resource scope</a></p>'
    (WORK/'review/index.html').write_text('<!doctype html><meta charset="utf-8"><title>Five-floor castles</title><style>body{background:#303039;color:#e9dec5;font:16px sans-serif;margin:24px}section{display:flex;gap:20px}img{max-width:44vw;width:440px;object-fit:contain}a{color:#c6d9fc}</style><h1>Five-floor castles / open and closed</h1><p>Five full-width floors from wheel level. No deck posts or room plaques. Matte pixels with fine exterior contours. Built-in image generation edits; selected prompts linked per castle.</p>'+live+''.join(rows),encoding='utf-8')


def apply():
    records=json.loads((WORK/'geometry.json').read_text())
    assert len(records)==10
    current=json.loads((ROOT/'content/runtime-assets.json').read_text())
    assets={a['target']:a for a in current['assets']}
    selected=[]
    for r in records:
        i=r['castle']
        names=[f'castle_mist_v2-{i:02}-{p}.png' for p in ['hull','cover','wheel-1','wheel-2','room-5']]
        names.append(f'castle_four_rooms_v5-rooms-{i:02}.png')
        for name in names:
            final=WORK/'final'/name
            assert final.exists(), final
            selected.append((name,final))
    # The authored clear deck replaces the predecessor floor overlay.
    current['assets']=[a for a in current['assets'] if a['target']!='res/castle_mist_v2-deck-surfaces.png']
    (ROOT/'content/runtime-assets.json').write_text(json.dumps(current,indent=2)+'\n')
    for name,final in selected:
        if 'res/'+name not in assets:
            subprocess.run(['python',str(ROOT/'tools/assets/runtime_assets.py'),'add',str(final),'--name',name],check=True,cwd=ROOT)
    for name,final in selected:
        a=assets.get('res/'+name)
        if a:
            master=ROOT/a.get('original_source',a['source'])
            shutil.copy2(final,master)
    write_geometry(records)
    print(f'Updated {len(selected)} directly consumed castle assets; optimize then stage',flush=True)


def geometry():
    records=json.loads((WORK/'geometry.json').read_text())
    assert len(records)==10
    write_geometry(records)


def write_geometry(records):
    rect=lambda v:'{'+','.join(map(str,v))+'}'
    code='#pragma once\n// Generated by tools/art/build_five_floor_castles.py. Bottom-to-top visual floors.\nnamespace CastleFiveFloors {\nconstexpr int DeckY=440;\nstruct Rect {int x,y,w,h;};\nstatic const Rect Rooms[10][5]={\n'+',\n'.join('{'+','.join(rect(v) for v in r['rooms'])+'}' for r in records)+'\n};\nstatic const Rect Covers[10]={\n'+',\n'.join(rect(r['cover']) for r in records)+'\n};\n}\n'
    (ROOT/'Classes/Data/CastleFiveFloorArt.h').write_text(code)
    wheels='static const int wheelAnchors[10][2][3]={\n'+',\n'.join('{'+','.join(rect(v) for v in r['wheels'])+'}' for r in records)+'\n};\n'
    (ROOT/'Classes/CastleMistWheels.inc').write_text(wheels)


if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('command',choices=['package','apply','geometry']);args=p.parse_args()
    globals()[args.command]()
