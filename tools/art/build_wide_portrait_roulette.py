"""Fit a newly authored wide housing uniformly into a 5:1 UI canvas."""
from pathlib import Path
import json
import shutil
from PIL import Image

root=Path(__file__).resolve().parents[2]
work=root/'asset_library/work/portrait-wide-roulette'
source=Path('C:/Users/polyp/.codex/generated_images/01a207f5-96b6-74a1-b712-379018a739b4/exec-dd381d10-ce0d-43f2-a845-941a70973280.png')
(work/'source').mkdir(parents=True,exist_ok=True)
(work/'final').mkdir(exist_ok=True)
shutil.copy2(source,work/'source'/source.name)
im=Image.open(source).convert('RGBA')
im=im.crop(im.getchannel('A').point(lambda a:255 if a>16 else 0).getbbox())
scale=min(1000/im.width,200/im.height)
im=im.resize((round(im.width*scale),round(im.height*scale)),Image.Resampling.LANCZOS)
out=Image.new('RGBA',(1000,200))
out.alpha_composite(im,((1000-im.width)//2,(200-im.height)//2))
final=work/'final/portrait-ui-05.png'
out.save(final)
assets=json.loads((root/'content/runtime-assets.json').read_text(encoding='utf-8'))['assets']
record=next(a for a in assets if a['target']=='res/portrait-ui-05.png')
shutil.copy2(final,root/record.get('original_source',record['source']))
print('Selected new wide housing: 1000x200 canvas, uniform artwork scale, no axis stretching')
