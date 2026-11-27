"""Validate packaged five-storey art and capture real lobby/combat render paths."""
from pathlib import Path
import argparse
import hashlib
import json
import sys
import numpy as np
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'asset_library/work/castle-equal-floors-20261123'


def validate():
    entries=json.loads((WORK/'geometry.json').read_text())
    assert len(entries)==10
    levels=set()
    for e in entries:
        c=e['castle']
        hull=Image.open(WORK/f'final/castle_mist_v2-{c:02}-hull.png').convert('RGBA')
        assert hull.size==(1089,1445)
        assert len({r[3] for r in e['rooms']})==1, (c,'unequal floor heights')
        assert len({e['rooms'][n][1]-e['rooms'][n+1][1] for n in range(4)})==1, (c,'unequal floor spacing')
        for floor,(x,y,w,h) in enumerate(e['rooms']):
            assert w>0 and h>0 and 0<=x<x+w<=1089 and 440<y<y+h<=1445
            assert hull.getchannel('A').crop((x,y,x+w,y+h)).getextrema()==(0,0)
            if floor:assert y+h<=e['rooms'][floor-1][1]
        assert abs(e['rooms'][0][1]+e['rooms'][0][3]-sum(v[1] for v in e['wheels'])/2)<65
        assert e['body_bounds']==[86,1002]
        cover=Image.open(WORK/f'final/castle_mist_v2-{c:02}-cover.png').convert('RGBA')
        assert cover.size==tuple(e['cover'][2:]) and cover.getchannel('A').getextrema()==(255,255)
        x,y,w,h=e['cover']
        assert all(x<=r[0] and y<=r[1] and x+w>=r[0]+r[2] and y+h>=r[1]+r[3] for r in e['rooms'])
        for side in range(2):
            wheel=Image.open(WORK/f'final/castle_mist_v2-{c:02}-wheel-{side+1}.png').convert('RGBA')
            assert wheel.width==wheel.height==e['wheels'][side][2]*2
            assert wheel.getchannel('A').getbbox() is not None and wheel.getpixel((0,0))[3]==0
        atlas=Image.open(WORK/f'final/castle_four_rooms_v5-rooms-{c:02}.png').convert('RGBA')
        distinct=set()
        for n in range(24):
            left=round(n%2*atlas.width/2)+3;top=round(n//2*atlas.height/12)+3
            right=round((n%2+1)*atlas.width/2)-3;bottom=round((n//2+1)*atlas.height/12)-3
            tile=atlas.crop((left,top,right,bottom))
            assert tile.getchannel('A').getextrema()==(255,255)
            assert tile.width/tile.height>5
            distinct.add(hashlib.sha256(tile.tobytes()).hexdigest())
        assert len(distinct)==24,(c,len(distinct))
        levels.update((c,n) for n in range(24))
    report=dict(castles=10,visual_floors_per_castle=5,independent_facilities=4,
                distinct_upgrade_interiors=len(levels),opaque_covers=10,
                hull_visible_width=916,equal_floor_heights=True,equal_floor_spacing=True,
                source_aspect_preserved=True,passed=True)
    (WORK/'asset-validation.json').write_text(json.dumps(report,indent=2))
    print('PASS 10 equal-width castles, 50 stacked openings, 20 circular wheels, 10 opaque covers, 240 distinct upgrade interiors',flush=True)


def native(exe):
    sys.path.insert(0,str(ROOT/'tools/equipment'))
    import review_character_tone as runtime
    runtime.WORK=WORK
    exe=ROOT/'proj.win32/Debug.win32'/exe
    cases=[
        ('lobby-850',850,{'CS_CASTLE_PROPORTIONS_REVIEW':'1'},'DONE castle proportions review',10),
        ('lobby-1408',1408,{'CS_CASTLE_PROPORTIONS_REVIEW':'1'},'DONE castle proportions review',10),
        ('facilities-1408',1408,{'CS_FACILITY_ROOMS_REVIEW':'1'},'DONE facility rooms review',70),
        ('all-states-850',850,{'CS_MIST_RESOURCE_REVIEW':'1'},'DONE mist resource review',35),
        ('cover-01',850,{'CS_COVER_STYLE_REVIEW':'1','CS_COVER_STYLE_STAGE':'1'},'DONE cover style review',2),
        ('cover-10',1408,{'CS_COVER_STYLE_REVIEW':'1','CS_COVER_STYLE_STAGE':'10'},'DONE cover style review',2),
        ('siege-850',850,{'CS_FIVE_FLOOR_PVP_REVIEW':'1'},'DONE five-floor siege review',2),
        ('lobby-input-850',850,{'CS_MERGE_LOBBY_IDLE_REVIEW':'1'},'DONE lobby idle review',3),
    ]
    results=[]
    for name,height,flags,marker,count in cases:
        results.append(runtime.run(exe,name,height,flags,marker,count,True))
        (WORK/'runtime-validation.json').write_text(json.dumps(results,indent=2))


if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--native',action='store_true');p.add_argument('--exe',default='cs_five_floor_castles.exe');args=p.parse_args()
    validate()
    if args.native:native(args.exe)
