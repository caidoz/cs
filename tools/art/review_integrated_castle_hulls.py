"""Read-only lineup of all native-pixel hulls with their separate attachments."""
from pathlib import Path
from PIL import Image,ImageDraw,ImageFont
import json
import re

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'asset_library/work/castle-integrated-chassis'
report=json.loads((WORK/'selected-finals.json').read_text(encoding='utf-8'))
header=(ROOT/'Classes/Data/PortraitCastleArt.h').read_text(encoding='utf-8')
names=re.findall(r'u8"([^"]+)"',header)
feet=list(map(int,re.search(r'CannonFootX\[Count\]=\{([^}]+)',header).group(1).split(',')))
pitch=355;base=860
sheet=Image.new('RGBA',(pitch*19,950),'#101e29')
draw=ImageDraw.Draw(sheet)
font=ImageFont.truetype(str(ROOT/'Resources/fonts/neodgm.ttf'),18)
draw.line((0,base,pitch*19,base),fill='#537180',width=1)
for i,row in enumerate(report['stages']):
    n=i+1
    hull=Image.open(ROOT/f'asset_library/production/portrait-castle-{n:02}.png').convert('RGBA')
    wheel=Image.open(ROOT/f'asset_library/production/portrait-wheel-{n:02}.png').convert('RGBA')
    gun=Image.open(ROOT/f'asset_library/production/portrait-turret-{n:02}.png').convert('RGBA')
    diameter=78+16*i/18
    x=i*pitch+18
    bottom=base-diameter*.58
    sheet.alpha_composite(hull,(x,round(bottom-hull.height)))
    positions=(.17,.83) if i<5 else (.15,.5,.85)
    for at in positions:
        sheet.alpha_composite(wheel,(round(x+hull.width*at-wheel.width*.5),round(bottom+wheel.height*.08-wheel.height*.5)))
    front=.83 if i<5 else .85
    sheet.alpha_composite(gun,(round(x+hull.width*front-feet[i]),round(bottom-(diameter*.42+3)-gun.height)))
    draw.text((x,base+20),f'{n:02}  {names[i]}',font=font,fill='#f3e8cf')
    draw.text((x,base+48),f'{hull.width} x {hull.height} px',font=font,fill='#9ebac8')
sheet.save(WORK/'all-19-integrated.png')
sheet.save(WORK/'all-19-with-cannons.png')
# Enlarge complete assembled sections together; never scale weapons separately.
detail=Image.new('RGBA',(pitch*3,290),'#101e29')
detail_draw=ImageDraw.Draw(detail)
for col,n in enumerate((1,9,19)):
    section=sheet.crop(((n-1)*pitch,base-220,n*pitch,base+10))
    detail.alpha_composite(section,(col*pitch,36))
    detail_draw.text((col*pitch+18,8),f'{n:02}  {names[n-1]}',font=font,fill='#f3e8cf')
detail.resize((detail.width*2,detail.height*2),Image.Resampling.NEAREST).save(WORK/'cannon-connections-detail.png')
print(WORK/'all-19-with-cannons.png')
print(WORK/'cannon-connections-detail.png')
