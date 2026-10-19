"""Register intact generated battle-gallery modules and their floor anchors."""
from pathlib import Path
from PIL import Image
import shutil,json

ROOT=Path(__file__).resolve().parents[2]
SOURCE=ROOT/'content/castles/combat_galleries_v2'
GAME=ROOT/'Resources/res/castle_combat_galleries'

def main():
    GAME.mkdir(parents=True,exist_ok=True)
    rows=[];manifest=[]
    for castle in range(1,11):
        name=f'gallery-{castle:02}.png'
        src=SOURCE/'originals'/name
        im=Image.open(src).convert('RGBA')
        alpha=im.getchannel('A')
        assert alpha.getextrema()[0]==0,src
        x,y,right,bottom=alpha.point(lambda a:255 if a>=192 else 0).getbbox()
        w,h=right-x,bottom-y
        assert 1.8<w/h<4.5,(castle,w,h)
        # All modules are authored with the walking line at 80% of height.
        foot=round(h*.8)
        assert alpha.getpixel((x+w//2,y+h//2))>=192,('transparent back wall',castle)
        shutil.copy2(src,GAME/name)
        rows.append(f' {{{x},{y},{w},{h},{foot}}},')
        manifest.append(dict(castle=castle,file=name,crop=[x,y,w,h],foot=foot))
    (ROOT/'Classes/Data/CombatGalleryLayout.h').write_text(
        '#pragma once\nnamespace CombatGalleryLayout {\nstruct Piece {int x,y,w,h,foot;};\n'
        'static const Piece Pieces[10]={\n'+'\n'.join(rows)+'\n};\n}\n',encoding='utf-8')
    (SOURCE/'manifest.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
    print('PASS ten solid-backed battle galleries, original PNGs and floor anchors')

if __name__=='__main__': main()
