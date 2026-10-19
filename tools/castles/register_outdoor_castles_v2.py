"""Register approved exteriors and split circular wheel animation overlays.

The approved full PNGs are copied unchanged. Wheel overlays use the existing
sprite-registration workflow (circular crops), without repainting the castle.
"""
from pathlib import Path
import json,shutil
import numpy as np
from PIL import Image,ImageDraw,ImageChops

ROOT=Path(__file__).resolve().parents[2]
SOURCE=ROOT/'content/castles/outdoor_castles_v2'
GAME=ROOT/'Resources/res/castle_individual_v4'
WIDTHS=[342,350,358,366,374,382,390,406,414,422]
# deck x/y/width, commander x/y, muzzle x/y, safe interior aperture x/y/w/h
ANCHORS=[
 (220,730,900,1360,660,1020,350,250,470,700,240),
 (185,808,815,1190,808,1180,430,320,360,520,430),
 (250,945,600,1000,945,1145,600,375,420,400,510),
 (185,1040,690,1000,1040,1080,680,390,440,410,580),
 (120,1145,700,940,1145,1080,725,260,470,420,650),
 (210,1248,590,930,1248,1030,875,350,400,400,830),
 (150,1255,670,940,1255,1015,925,300,420,420,815),
 (125,1260,675,920,1260,980,965,330,390,420,850),
 (140,1370,630,865,1370,930,1015,300,450,360,900),
 (110,1360,665,860,1360,905,1115,325,450,350,890),
]

def wheels(im,count):
    alpha=np.asarray(im.getchannel('A'))>=224
    bottom=np.where(alpha)[0].max()
    runs=[];start=None
    for x,value in enumerate(list(alpha[bottom-20])+[False]):
        if value and start is None:start=x
        if not value and start is not None:
            if x-start>10:runs.append((start,x))
            start=None
    assert len(runs)==count,(len(runs),count)
    circles=[]
    for lo,hi in runs:
        center=(lo+hi-1)/2
        guess=(hi-lo)**2/160+10
        points=[]
        for x in range(max(0,int(center-guess*.85)),min(im.width,int(center+guess*.85))):
            ys=np.flatnonzero(alpha[:,x])
            if len(ys) and ys[-1]>bottom-guess*.7:points.append((x,ys[-1]))
        pts=np.array(points,float)
        matrix=np.column_stack((2*pts[:,0],2*pts[:,1],np.ones(len(pts))))
        cx,cy,c=np.linalg.lstsq(matrix,(pts*pts).sum(1),rcond=None)[0]
        outer=np.sqrt(c+cx*cx+cy*cy)
        # Keep the fixed outermost anti-aliased rim; rotate the opaque inner disc.
        circles.append((round(cx),round(cy),round(outer*.94),round(outer)))
    return circles

def main():
    GAME.mkdir(parents=True,exist_ok=True)
    rows=[];names=[];entries=[];rooms=[]
    for index,(width,anchor) in enumerate(zip(WIDTHS,ANCHORS)):
        castle=index+1;name=f'castle-{castle:02}.png'
        im=Image.open(SOURCE/'originals'/name).convert('RGBA')
        x,y,right,bottom=im.getchannel('A').point(lambda a:255 if a>=192 else 0).getbbox()
        count=2 if castle<=4 else 3 if castle<=7 else 4
        circles=wheels(im,count)
        shutil.copy2(SOURCE/'originals'/name,GAME/name)
        names.append(f'\t"castle_individual_v4/castle-{castle:02}",')
        for slot in range(4):
            cx,cy,r,outer=circles[min(slot,count-1)]
            wheel=im.crop((cx-r,cy-r,cx+r,cy+r))
            mask=Image.new('L',wheel.size)
            ImageDraw.Draw(mask).ellipse((0,0,2*r-1,2*r-1),fill=255)
            wheel.putalpha(ImageChops.multiply(wheel.getchannel('A'),mask))
            wheel.save(GAME/f'wheel-{castle:02}-{slot}.png')
            names.append(f'\t"castle_individual_v4/wheel-{castle:02}-{slot}",')
        dx,dy,dw,hero,heroY,mx,my,ax,ay,aw,ah=anchor
        wheelRows=','.join('{'+','.join(map(str,w[:3]))+'}' for w in circles+[(0,0,0,0)]*(4-count))
        rows.append(f' {{{x},{y},{right-x},{bottom-y},{heroY},{hero},{mx},{my},{dx},{dy},{dw},{count},{width}.0f,{{{wheelRows}}}}},')
        rooms.append(f' {{{ax},{ay},{aw},{ah},1}},')
        height=(bottom-y)*width/(right-x)
        entries.append(dict(castle=castle,width=width,height=height,source='originals/'+name,
            opaqueBounds=[x,y,right,bottom],wheels=circles,wheelCount=count,anchors=anchor))
    heights=[e['height'] for e in entries]
    assert all(b>a for a,b in zip(heights,heights[1:])),heights
    assert max(heights)<761,heights
    (ROOT/'Classes/Data/IndividualCastleV4.h').write_text(
        '#pragma once\nnamespace IndividualCastleV4 {\n'
        'static const int Stride=5;\nstruct Wheel {int x,y,r;};\n'
        'struct Rig {int x,y,w,h,floor,hero,mx,my,deckX,deckY,deckW,wheelCount;float width;Wheel wheels[4];};\n'
        'static const Rig Rigs[10]={\n'+'\n'.join(rows)+'\n};\n}\n',encoding='utf-8')
    (ROOT/'Classes/Data/IndividualCastleRooms.h').write_text(
        '#pragma once\nnamespace IndividualCastleRooms {\n'
        'struct Aperture {int x,y,w,h,columns;};\n'
        'static const float RoomWidth=140.0f,FloorHeight=40.0f,BottomLift=4.0f;\n'
        'static const Aperture Rooms[10]={\n'+'\n'.join(rooms)+'\n};\n}\n',encoding='utf-8')
    (ROOT/'Classes/IndividualCastleNames.inc').write_text('\n'.join(names)+'\n',encoding='utf-8')
    (SOURCE/'runtime-registration.json').write_text(json.dumps(entries,indent=2),encoding='utf-8')
    print('PASS ten approved exteriors, 29 rotating wheels, 50 image slots; heights:',[round(h,1) for h in heights])

if __name__=='__main__':main()
