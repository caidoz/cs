"""Export the user's original golden cog; palette tint is applied at runtime."""
from pathlib import Path
from PIL import Image
import shutil
import json

root=Path(__file__).resolve().parents[2]
work=root/'asset_library/work/square-grid-cog-roulette'
source=root/'asset_library/reference/Resources/res/merge_castle_rebuild/ui-gear.png'
(work/'source').mkdir(parents=True,exist_ok=True)
(work/'final').mkdir(exist_ok=True)
shutil.copy2(source,work/'source'/source.name)
im=Image.open(source).convert('RGBA')
im=im.crop(im.getchannel('A').point(lambda a:255 if a>16 else 0).getbbox())
scale=124/max(im.size)
im=im.resize((round(im.width*scale),round(im.height*scale)),Image.Resampling.NEAREST)
out=Image.new('RGBA',(128,128))
out.alpha_composite(im,((128-im.width)//2,(128-im.height)//2))
out.save(work/'final/portrait-roulette-gear.png')
assets=json.loads((root/'content/runtime-assets.json').read_text(encoding='utf-8'))['assets']
for item in assets:
    if item['target']=='res/portrait-roulette-gear.png':
        shutil.copy2(work/'final/portrait-roulette-gear.png',root/item.get('original_source',item['source']))
        break
