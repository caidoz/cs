from pathlib import Path
from PIL import Image,ImageDraw,ImageFont
import json,math,re,shutil
R=Path.cwd();W=R/'asset_library/work/castle-weapons-runtime-20261127';O=W/'final';D=R/'docs/design/castle-weapons-runtime-v1'
plan=json.loads((W/'plan.json').read_text(encoding='utf8'));rows=[]
def crop(im):return im.crop(im.getchannel('A').point(lambda a:255 if a>100 else 0).getbbox())
def fit(im,w):return im.resize((round(w),round(im.height*w/im.width)),Image.Resampling.LANCZOS)
for kind in ['castle','turret','wheel']:shutil.copy2(W/'backup'/f'portrait-{kind}-01.png',O/f'portrait-{kind}-01.png')
rows.append(dict(stage=1,name='목재 투석기',w=256,h=190,wheel=50,gunW=112,gunH=96,deck=36,foot=61))
pw,ph=256,190;area=6500
decks={2:32,3:38,4:43,5:46,6:76,7:43,8:43,9:72,10:66,11:49,12:75,13:52,14:40,15:81,16:65,17:80,18:74,19:75}
for s in plan:
 n=s['stage'];p=W/f'sources/hull-fixed-{n:02}.png';p=p if p.exists() else W/f'parts/portrait-castle-{n:02}.png'
 raw=crop(Image.open(p).convert('RGBA'));z=max(s['width']/raw.width,(pw+6)/raw.width,(ph+10)/raw.height)
 body=fit(raw,raw.width*z);pw,ph=body.size
 gunraw=crop(Image.open(W/f'parts/portrait-turret-{n:02}.png').convert('RGBA'))
 gw=max(s['gunWidth'],math.sqrt(area*1.025*gunraw.width/gunraw.height));gun=fit(gunraw,gw);area=gun.width*gun.height
 wheel=fit(crop(Image.open(W/f'parts/portrait-wheel-{n:02}.png').convert('RGBA')),s['wheel'])
 for k,im in [('castle',body),('turret',gun),('wheel',wheel)]:im.save(O/f'portrait-{k}-{n:02}.png')
 rows.append(dict(stage=n,name=s['name'],w=pw,h=ph,wheel=wheel.height,gunW=gun.width,gunH=gun.height,deck=decks[n],foot=round(gun.width*.56),source=str(p.relative_to(R)),uniform_scale=z,source_size=raw.size))
assert all(b['w']>a['w'] and b['h']>a['h'] for a,b in zip(rows,rows[1:]))
assert max(b['w']/a['w'] for a,b in zip(rows,rows[1:]))<1.07
assert rows[-1]['h']/rows[0]['h']>2.5
(W/'runtime-registration.json').write_text(json.dumps(rows,ensure_ascii=False,indent=2),encoding='utf8')
font=ImageFont.truetype('C:/Windows/Fonts/malgun.ttf',18)
def assembled(r):
 n=r['stage'];body=Image.open(O/f'portrait-castle-{n:02}.png').convert('RGBA');wheel=Image.open(O/f'portrait-wheel-{n:02}.png').convert('RGBA');gun=Image.open(O/f'portrait-turret-{n:02}.png').convert('RGBA')
 bottom=body.height+12;axle=body.width*(.80 if n<=5 else .84)
 ext=max(body.width,axle-r['foot']+r['gunW']);im=Image.new('RGBA',(math.ceil(ext+36),math.ceil(bottom+wheel.height*.58+5)))
 poss=[.17,.8] if n<=5 else [.15,.495,.84]
 for at in poss:im.alpha_composite(wheel,(round(12+body.width*at+26*body.width/256-wheel.width/2),round(bottom-wheel.height*.42-10*body.width/256)))
 im.alpha_composite(body,(12,12))
 for at in poss:im.alpha_composite(wheel,(round(12+body.width*at-wheel.width/2),round(bottom-wheel.height*.42)))
 x=round(12+axle-r['foot']);y=round(bottom-r['deck']-r['gunH'])
 if n==1:
  im.alpha_composite(gun.crop((0,0,112,96)),(x,y));im.alpha_composite(gun.crop((112,0,224,96)),(x,y));im.alpha_composite(gun.crop((225,1,239,14)).resize((25,23)),(x+11,y+19))
 else:im.alpha_composite(gun,(x,y))
 return im
parts=[assembled(r) for r in rows]
pitch=max(im.width for im in parts)+22;base=max(im.height for im in parts)+12
sheet=Image.new('RGB',(pitch*19,base+80),'#0b1421');d=ImageDraw.Draw(sheet);d.line((0,base,sheet.width,base),fill='#607980')
for i,(r,im) in enumerate(zip(rows,parts)):
 sheet.paste(im,(i*pitch+12,base-im.height),im);d.text((i*pitch+14,base+8),f"{i+1:02} {r['name']}",font=font,fill='#eee1bd');d.text((i*pitch+14,base+38),f"{r['w']}×{r['h']} / 무기 {r['gunW']}×{r['gunH']}",font=font,fill='#99b6ba')
sheet.save(D/'all-19-runtime-lineup.jpg',quality=94)
for start,end in [(0,5),(5,10),(10,15),(15,19)]:
 group=Image.new('RGB',(pitch*(end-start),base+80),'#0b1421');group.paste(sheet.crop((pitch*start,0,pitch*end,sheet.height)));group.save(D/f'stages-{start+1:02}-{end:02}.jpg',quality=94)
# Parts are concept artwork; export preserves alpha and uses only a uniform scale.
(D/'runtime-registration.json').write_text(json.dumps(rows,ensure_ascii=False,indent=2),encoding='utf8')
print('PASS nineteen complete rigs; strict width/height increase; max width step',round(max(b['w']/a['w'] for a,b in zip(rows,rows[1:])),4))
for r in rows:print(r['stage'],r['w'],r['h'],r['gunW'],r['gunH'],r['deck'])
