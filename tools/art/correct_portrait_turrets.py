"""Import generated weapon silhouettes at the castle's native pixel density."""
from pathlib import Path
import json
import shutil
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'asset_library/work/portrait-turret-correction'
manifest=json.loads((WORK/'generation.json').read_text(encoding='utf-8'))
catalog=json.loads((ROOT/'content/runtime-assets.json').read_text(encoding='utf-8'))
assets={a['target']:a for a in catalog['assets']}
for item in manifest['images']:
    index=item['castle']
    source=Path(item['source'])
    saved=WORK/'source'/source.name
    saved.parent.mkdir(parents=True,exist_ok=True)
    shutil.copy2(source,saved)
    image=Image.open(saved).convert('RGBA')
    box=image.getchannel('A').point(lambda a:255 if a>16 else 0).getbbox()
    assert box,source
    image=image.crop(box)
    width=round(100*(1+.2*index/18))
    image=image.resize((width,round(image.height*width/image.width)),Image.Resampling.NEAREST)
    final=WORK/'final'/f'portrait-turret-{index+1:02d}.png'
    final.parent.mkdir(parents=True,exist_ok=True)
    image.save(final)
    record=assets['res/'+final.name]
    master=ROOT/record.get('original_source',record['source'])
    shutil.copy2(final,master)
    print(f'{index+1:02d}: {image.width}x{image.height} -> {master.relative_to(ROOT)}')
