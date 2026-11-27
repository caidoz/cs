"""Extract approved imagegen components; authoring stays outside runtime res."""
from pathlib import Path
import json
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'asset_library/work/castle-front-cannon-tone-sync'
OUT=WORK/'starter-production-final'
OUT.mkdir(exist_ok=True)
sheet=Image.open(WORK/'production-parts-source.png').convert('RGBA')
def fit(im,width):
    return im.resize((width,round(im.height*width/im.width)),Image.Resampling.LANCZOS)
def alpha_crop(im):
    return im.crop(im.getchannel('A').point(lambda a:255 if a>128 else 0).getbbox())
hull=fit(sheet.crop((35,11,885,986)),256)
wheel=fit(sheet.crop((978,715,1203,940)),50)
base=fit(alpha_crop(Image.open(WORK/'production-carriage-fixed-source.png').convert('RGBA')),86)
arm=fit(sheet.crop((968,507,1388,612)),74)
rock=fit(sheet.crop((1331,788,1411,865)),14)
atlas=Image.new('RGBA',(336,96))
atlas.alpha_composite(base,(17,36))
atlas.alpha_composite(arm,(112+12,37))
atlas.alpha_composite(rock,(225,1))
for name,im in [('portrait-castle-01.png',hull),('portrait-wheel-01.png',wheel),('portrait-turret-01.png',atlas)]:
    im.save(OUT/name)
rail=Image.open(WORK/'rail-stone/native-review/res/portrait-wheel-01.png')
rail.save(OUT/'portrait-rail-stone.png')
report={'hull':hull.size,'wheel':wheel.size,'base':base.size,'arm':arm.size,'stone':rock.size,
        'atlas':atlas.size,'pivot':[77,48],'cup_center':[23,31],'stone_render_scale':1.8,
        'rail':rail.size,'rail_contact_y':26,'source':'built-in image_gen separated approved matte castle',
        'components_resampled_uniformly':True,'atlas_registration':'base(17,36), arm(124,37), rock(225,1)'}
(OUT/'rig-registration.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
