"""Uniformly sample selected imagegen hulls; never add foundation tiles/padding."""
from pathlib import Path
from PIL import Image, ImageDraw
import argparse
import json
import re
import shutil

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'asset_library/work/castle-integrated-chassis'
CHANGED=[5,6,7,8,9,10,11,12,14,15,16,17,19]
parser=argparse.ArgumentParser()
parser.add_argument('--promote',action='store_true')
args=parser.parse_args()
(WORK/'final').mkdir(exist_ok=True)
catalog=json.loads((ROOT/'content/runtime-assets.json').read_text(encoding='utf-8'))
assets={a['target']:a for a in catalog['assets']}
rows=[]
for n in range(1,20):
    target=f'res/portrait-castle-{n:02}.png'
    master=ROOT/assets[target].get('original_source',assets[target]['source'])
    original=Image.open(master).convert('RGBA')
    if n in CHANGED:
        source=WORK/f'stage-{n:02}-clean-source.png'
        if not source.exists():source=WORK/f'stage-{n:02}-source.png'
        im=Image.open(source).convert('RGBA')
        assert im.getchannel('A').getextrema()==(0,255),source
        bounds=im.getchannel('A').point(lambda a:255 if a>16 else 0).getbbox()
        im=im.crop(bounds)
        w=round(256*(1+.2*(n-1)/18))
        h=round(im.height*w/im.width)
        final=im.resize((w,h),Image.Resampling.LANCZOS)
        path=WORK/'final'/Path(target).name
        final.save(path,optimize=True)
        rows.append({'stage':n,'width':w,'height':h,'source':source.name,'uniform_scale':w/im.width,'final':str(path.relative_to(ROOT))})
    else:
        rows.append({'stage':n,'width':original.width,'height':original.height,'unchanged':True})
for a,b in zip(rows,rows[1:]):
    assert a['width']<b['width'] and a['height']<b['height'],(a,b)
assert rows[-1]['height']/rows[0]['height']>=2.5,rows
report={'stages':rows,'changed':CHANGED,'no_tiled_foundation':True,'all_resampling_uniform':True,
        'width_ratio':rows[-1]['width']/rows[0]['width'],'height_ratio':rows[-1]['height']/rows[0]['height'],
        'generation':'Built-in image_gen edits; no procedural foundation generation',
        'prompts':{p.name:p.read_text(encoding='utf-8') for p in sorted(WORK.glob('*-prompt.txt'))}}
(WORK/'selected-finals.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
if args.promote:
    backup=WORK/'previous-production';backup.mkdir(exist_ok=True)
    for row in rows:
        if row.get('unchanged'):continue
        n=row['stage'];target=f'res/portrait-castle-{n:02}.png';master=ROOT/assets[target].get('original_source',assets[target]['source'])
        if not (backup/master.name).exists():shutil.copy2(master,backup/master.name)
        shutil.copy2(ROOT/row['final'],master)
    header=ROOT/'Classes/Data/PortraitCastleArt.h'
    text=header.read_text(encoding='utf-8')
    sizes=','.join('{%d,%d}'%(r['width'],r['height']) for r in rows)
    text=re.sub(r'static const Size Sizes\[Count\]=\{.*?\};','static const Size Sizes[Count]={'+sizes+'};',text)
    header.write_text(text,encoding='utf-8')
print(json.dumps(report,indent=2))
