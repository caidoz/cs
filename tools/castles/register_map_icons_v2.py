"""Fit current castle icons uniformly and register their measured wheel baselines."""
from pathlib import Path
from PIL import Image
import json,shutil,hashlib

ROOT=Path(__file__).resolve().parents[2]
SOURCE=ROOT/'content/castles/map_icons_v2'
OUT=SOURCE/'png'
GAME=ROOT/'Resources/res/castle_map_icons'

def build():
    OUT.mkdir(parents=True,exist_ok=True);GAME.mkdir(parents=True,exist_ok=True)
    entries=[];contacts=[]
    for c in range(1,11):
        name=f'castle-map-{c:02}.png'
        original=SOURCE/'originals'/name
        im=Image.open(original).convert('RGBA')
        assert im.getchannel('A').getextrema()[0]==0,original
        bounds=im.getchannel('A').point(lambda a:255 if a>=192 else 0).getbbox()
        assert bounds,original
        x,y,x2,y2=bounds
        crop=(max(0,x-4),max(0,y-4),min(im.width,x2+4),min(im.height,y2+4))
        art=im.crop(crop)
        unit=min(952/art.width,952/art.height)
        fitted=art.resize((max(1,round(art.width*unit)),max(1,round(art.height*unit))),Image.Resampling.LANCZOS)
        icon=Image.new('RGBA',(1024,1024))
        icon.alpha_composite(fitted,((1024-fitted.width)//2,992-fitted.height))
        visible=icon.getchannel('A').point(lambda a:255 if a>=192 else 0).getbbox()
        wheel=visible[3]
        assert visible[0]>=28 and visible[1]>=28 and visible[2]<=996 and 984<=wheel<=992,(c,visible)
        icon.save(OUT/name)
        target=GAME/f'castle_map_{c:02}.png';shutil.copy2(OUT/name,target)
        contacts.append(wheel)
        entries.append(dict(castleLevel=c,castleIndex=c-1,upgradeStage=0,file='png/'+name,
            source='originals/'+name,currentCastleReference=f'../individual_castles_v4/castle-{c:02}.png',
            gameFile=str(target.relative_to(ROOT)),imageId=f'CASTLE_MAP_ICON_{c:02}_IMG',wheelContactY=wheel,
            opaqueBounds=list(visible),sha256=hashlib.sha256(target.read_bytes()).hexdigest()))
    (SOURCE/'manifest.json').write_text(json.dumps(dict(width=1024,height=1024,transparentBackground=True,
        camera='side elevation icon, two wheels, no diorama slab',icons=entries),indent=2),encoding='utf-8')
    (ROOT/'Classes/Data/CastleMapIconLayout.h').write_text('#pragma once\nnamespace CastleMapIconLayout {\nstatic const int Size=1024;\nstatic const int WheelY[10]={'+','.join(map(str,contacts))+'};\n}\n',encoding='utf-8')
    print('PASS ten current 1024px RGBA icons, padding, game hashes and measured wheel baselines:',contacts)

if __name__=='__main__':build()
