"""Pack approved current exteriors into the existing map/entrance icon slots."""
from pathlib import Path
from PIL import Image
import json,shutil

ROOT=Path(__file__).resolve().parents[2]
SOURCE=ROOT/'content/castles/outdoor_castles_v2'
OUT=SOURCE/'map-icons'
GAME=ROOT/'Resources/res/castle_map_icons'

def main():
    OUT.mkdir(parents=True,exist_ok=True)
    contacts=[];entries=[]
    for castle in range(1,11):
        im=Image.open(SOURCE/'originals'/f'castle-{castle:02}.png').convert('RGBA')
        x,y,right,bottom=im.getchannel('A').point(lambda a:255 if a>=192 else 0).getbbox()
        art=im.crop((max(0,x-4),max(0,y-4),min(im.width,right+4),min(im.height,bottom+4)))
        scale=min(952/art.width,952/art.height)
        fitted=art.resize((round(art.width*scale),round(art.height*scale)),Image.Resampling.LANCZOS)
        icon=Image.new('RGBA',(1024,1024))
        icon.alpha_composite(fitted,((1024-fitted.width)//2,992-fitted.height))
        contact=icon.getchannel('A').point(lambda a:255 if a>=192 else 0).getbbox()[3]
        assert 980<=contact<=992,(castle,contact)
        name=f'castle-map-{castle:02}.png';icon.save(OUT/name)
        shutil.copy2(OUT/name,GAME/f'castle_map_{castle:02}.png')
        contacts.append(contact);entries.append(dict(castle=castle,file='map-icons/'+name,wheelContactY=contact))
    (SOURCE/'map-icon-registration.json').write_text(json.dumps(entries,indent=2),encoding='utf-8')
    (ROOT/'Classes/Data/CastleMapIconLayout.h').write_text(
        '#pragma once\nnamespace CastleMapIconLayout {\nstatic const int Size=1024;\n'
        'static const int WheelY[10]={'+','.join(map(str,contacts))+'};\n}\n',encoding='utf-8')
    print('PASS ten current outdoor castle map icons; contacts:',contacts)

if __name__=='__main__':main()
