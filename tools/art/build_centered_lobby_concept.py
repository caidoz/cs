"""Review-only lobby composition using actual game artwork, outside runtime resources."""
from pathlib import Path
import shutil
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'asset_library/work/lobby-centered-concept'
ASSETS=WORK/'assets'
ASSETS.mkdir(parents=True,exist_ok=True)
art=ROOT/'asset_library/work/portrait-redesign-implementation'
for n in (0,2,3,4,6,7):
    shutil.copy2(art/f'final/portrait-ui-{n:02d}.png',ASSETS/f'ui-{n}.png')
shutil.copy2(art/'final/portrait-night.png',ASSETS/'night.png')
for kind in ('castle','wheel'):
    shutil.copy2(art/f'smooth-review-v2/art/portrait-{kind}-01.png',ASSETS/f'{kind}.png')
shutil.copy2(ROOT/'asset_library/work/portrait-turret-correction/final/portrait-turret-01.png',ASSETS/'catapult.png')
atlas=Image.open(art/'final/portrait-icons.png').convert('RGBA')
cw,ch=atlas.width//4,atlas.height//3
bounds=[(77,131,323,312),(78,102,291,312),(56,102,270,320),(67,106,247,322),(95,70,303,292),(71,83,297,282),(59,75,264,284),(40,80,277,285),(77,36,324,282),(44,15,296,294),(22,44,296,282),(21,53,292,278)]
for i,name in ((1,'swords'),(3,'bolt'),(4,'shield'),(5,'heart'),(6,'coin'),(7,'gem'),(8,'settings'),(9,'fort'),(10,'shop'),(11,'chest')):
    b=bounds[i];x,y=(i%4)*cw,(i//4)*ch
    atlas.crop((x+b[0],y+b[1],x+b[2],y+b[3])).save(ASSETS/f'{name}.png')
lobby=Image.open(ROOT/'output/portrait-redesign/lobby-selected-hero-clean.png').convert('RGBA')
lobby.crop((18,14,62,58)).save(ASSETS/'hero.png')
lobby.crop((372,760,420,806)).save(ASSETS/'armor.png')
battle=Image.open(ROOT/'output/portrait-redesign/850/stage-02/battle.png').convert('RGBA')
battle.crop((230,360,282,436)).save(ASSETS/'crew.png')
font=(ROOT/'Resources/fonts/neodgm.ttf').as_uri()
html='''<!doctype html><html lang="ko"><meta charset="utf-8"><title>중앙 성 로비 시안</title>
<style>
@font-face{font-family:game;src:url("FONT_URI")}*{box-sizing:border-box}html,body{margin:0;background:#030a13;color:#f2ead6;font-family:game,"Malgun Gothic",sans-serif}body{width:640px;overflow:hidden}.screen{width:640px;height:var(--height);position:relative;overflow:hidden;background:#030a13}.frame{border:10px solid transparent;border-image:url(assets/ui-2.png) 38 fill / 10px}.stat{border-image-source:url(assets/ui-4.png);border-image-slice:28;border-image-width:8px}.wood{border-image-source:url(assets/ui-6.png);border-image-slice:34;border-image-width:10px}.gold{border-image-source:url(assets/ui-7.png);border-image-slice:48;border-image-width:16px}img{object-fit:contain;image-rendering:pixelated}.bar{position:absolute;left:12px;top:10px;width:548px;height:50px}.avatar{position:absolute;left:12px;top:10px;width:56px;height:50px;padding:3px}.avatar img{width:38px;height:38px}.header-label{position:absolute;top:25px;font-size:24px;height:28px;line-height:28px;text-align:center}.currency{position:absolute;top:23px;width:28px;height:28px}.settings{position:absolute;left:572px;top:10px;width:56px;height:50px;display:flex;align-items:center;justify-content:center}.settings img{width:32px;height:32px}.scene{position:absolute;left:0;top:74px;width:640px;height:calc(336px + var(--extra));overflow:hidden;background:#030a13}.night{position:absolute;width:640px;height:auto;bottom:-31px;left:0}.stars{position:absolute;inset:0;background:radial-gradient(circle at 10% 17%,#d4d5bd 0 1px,transparent 1.5px),radial-gradient(circle at 76% 10%,#c9d9ca 0 1px,transparent 1.5px),radial-gradient(circle at 91% 38%,#e7dcbd 0 1px,transparent 1.5px),radial-gradient(circle at 17% 60%,#b8d4d7 0 1px,transparent 1.5px),radial-gradient(circle at 69% 48%,#cdd4c7 0 1px,transparent 1.5px)}.assembly{position:absolute;bottom:8px;left:50%;transform:translateX(-50%)}.assembly img{position:absolute;height:auto}.vault{position:absolute;right:24px;top:10px;text-align:center;font-size:18px;color:#c9d9cd}.vault img{width:36px;height:36px;display:block;margin-bottom:4px}.pvp{position:absolute;right:24px;bottom:16px;width:58px;height:28px;text-align:center;font-size:18px;line-height:11px;border-width:8px}.castle-name{position:absolute;left:168px;top:calc(414px + var(--extra));width:304px;height:28px;text-align:center;font-size:20px;line-height:10px;border-width:8px}.stats{position:absolute;left:24px;top:calc(450px + var(--extra));width:592px;height:48px;display:flex;gap:8px}.stat-card{position:relative;width:192px;height:48px;display:flex;align-items:flex-start;justify-content:center;gap:10px;padding-top:1px}.stat-card img{width:25px;height:25px}.stat-card strong{font-weight:normal;font-size:26px;line-height:26px;white-space:nowrap}.segments{position:absolute;left:7px;right:7px;bottom:0;height:6px;display:flex;gap:2px}.segments i{height:6px;flex:1;background:var(--color);border-radius:1px}.manage{position:absolute;top:calc(506px + var(--extra));height:106px;width:290px}.manage h2{margin:0;position:absolute;top:2px;left:0;right:0;text-align:center;font-size:22px;font-weight:normal}.upgrade{left:24px}.gear-card{left:326px}.fort-icon{position:absolute;left:12px;top:27px;width:57px;height:57px}.up{position:absolute;left:72px;top:37px;width:22px;height:35px;background:#96e85e;clip-path:polygon(50% 0,100% 38%,72% 38%,72% 100%,28% 100%,28% 38%,0 38%)}.level{position:absolute;left:118px;right:8px;top:30px;text-align:center;font-size:21px}.price{position:absolute;left:116px;top:56px;width:145px;height:32px;display:flex;align-items:center;justify-content:center;gap:8px;border-image-source:url(assets/ui-3.png);border-image-slice:40;border-image-width:8px}.price img{width:18px;height:18px}.price span{font-size:22px;line-height:20px}.shortcut{position:absolute;top:27px;width:112px;height:64px;display:flex;flex-direction:column;justify-content:center;align-items:center;gap:0;border-width:8px;font-size:18px;line-height:18px}.shortcut img{height:30px;width:34px}.shortcut.crew{left:14px}.shortcut.equip{right:14px}.stage{position:absolute;left:24px;top:calc(620px + var(--extra));width:592px;height:50px}.stage-picture{position:absolute;left:7px;top:0;width:84px;height:30px;object-fit:cover;object-position:bottom}.stage-title{position:absolute;left:112px;top:-2px;font-size:20px}.stage-line{position:absolute;left:112px;top:19px;font-size:14px;color:#e5d9ae}.reward{position:absolute;right:10px;top:0;display:flex;align-items:center;gap:8px;height:30px;font-size:17px}.reward img{width:28px;height:28px}.start{position:absolute;left:140px;top:calc(680px + var(--extra));width:360px;height:64px;display:flex;align-items:center;justify-content:center;gap:14px;border-width:14px;font-size:28px;text-shadow:2px 2px #39200e}.start img{width:34px;height:34px}.nav{position:absolute;left:24px;top:calc(756px + var(--extra));height:74px;width:592px;display:flex;gap:8px}.nav-item{position:relative;width:112px;height:74px;display:flex;align-items:center;justify-content:center;flex-direction:column;gap:3px;font-size:18px;line-height:19px}.nav-item img{width:34px;height:32px}.nav-item.active{border-image-source:url(assets/ui-3.png);border-image-slice:40;filter:drop-shadow(0 0 4px #d49c38);color:#ffe49b}.nav-item.active:after{content:"";position:absolute;inset:2px;border:1px solid #ffe49b;pointer-events:none}
</style>
<div class="screen" id="screen"><div class="bar frame stat"></div><div class="avatar frame"><img src="assets/hero.png"></div>
<span class="header-label" style="left:77px;width:80px">Lv.1</span><img class="currency" style="left:170px" src="assets/coin.png"><span class="header-label" style="left:203px;width:90px">442</span><img class="currency" style="left:314px" src="assets/gem.png"><span class="header-label" style="left:352px;width:48px">0</span><img class="currency" style="left:416px" src="assets/bolt.png"><span class="header-label" style="left:449px;width:98px">40/40</span><div class="settings frame"><img src="assets/settings.png"></div>
<div class="scene"><img class="night" src="assets/night.png"><div class="stars"></div><div class="assembly" id="assembly"></div><div class="vault"><img src="assets/chest.png">56</div><div class="pvp frame">PVP</div></div>
<div class="castle-name frame stat">목재 개척 성 · 1단계</div>
<div class="stats"><div class="stat-card frame stat"><img src="assets/swords.png"><strong>27</strong><div class="segments" style="--color:#d6b35c"></div></div><div class="stat-card frame stat"><img src="assets/shield.png"><strong>60</strong><div class="segments" style="--color:#7abbd7"></div></div><div class="stat-card frame stat"><img src="assets/heart.png"><strong>60/60</strong><div class="segments" style="--color:#5ed59f"></div></div></div>
<div class="manage upgrade frame wood"><h2>성 강화</h2><img class="fort-icon" src="assets/fort.png"><div class="up"></div><div class="level">강화 Lv.0</div><div class="price frame"><img src="assets/coin.png"><span>300</span></div></div>
<div class="manage gear-card frame wood"><h2>동료 · 장비</h2><div class="shortcut crew frame"><img src="assets/crew.png"><span>동료</span></div><div class="shortcut equip frame"><img src="assets/armor.png"><span>장비</span></div></div>
<div class="stage frame stat"><img class="stage-picture" src="assets/night.png"><div class="stage-title">늪지대</div><div class="stage-line">STAGE 01 · WAVE 01 / 15</div><div class="reward"><img src="assets/chest.png"><span>보상</span></div></div>
<div class="start frame gold"><img src="assets/swords.png"><span>전투 시작</span></div>
<div class="nav"><div class="nav-item frame"><img src="assets/shop.png"><span>상점</span></div><div class="nav-item frame"><img src="assets/hero.png"><span>영웅</span></div><div class="nav-item frame active"><img src="assets/swords.png"><span>모험</span></div><div class="nav-item frame"><img src="assets/crew.png"><span>동료</span></div><div class="nav-item frame"><img src="assets/fort.png"><span>성</span></div></div></div>
<script>
const h=Number(new URLSearchParams(location.search).get('height')||850),extra=h-850;
const screen=document.querySelector('#screen');screen.style.setProperty('--height',h+'px');screen.style.setProperty('--extra',extra+'px');
const f=h>1000?1.85:.95,a=document.querySelector('#assembly');a.style.width=320*f+'px';a.style.height=346*f+'px';
function part(name,left,bottom,width){const im=document.createElement('img');im.src='assets/'+name+'.png';im.style.left=left*f+'px';im.style.bottom=bottom*f+'px';im.style.width=width*f+'px';a.append(im)}
part('castle',0,45.24,256);part('wheel',4.52,0,78);part('wheel',173.48,0,78);part('catapult',217,47.99,100);
document.querySelectorAll('.nav-item').forEach(item=>{item.setAttribute('role','button');item.tabIndex=0;item.setAttribute('aria-pressed',item.classList.contains('active'));function select(){document.querySelectorAll('.nav-item').forEach(el=>{el.classList.toggle('active',el===item);el.setAttribute('aria-pressed',el===item)})}item.addEventListener('click',select);item.addEventListener('keydown',e=>{if(e.key==='Enter'||e.key===' '){e.preventDefault();select()}})});
document.querySelectorAll('.segments').forEach(el=>{for(let i=0;i<8;i++)el.append(document.createElement('i'))});
</script></html>'''.replace('FONT_URI',font)
(WORK/'index.html').write_text(html,encoding='utf-8')
(WORK/'concept.json').write_text('''{
  "scope": "Design preview only; no game code or runtime assets changed",
  "castle": "Stage 1 wooden pioneer castle, separate original wheels and catapult at one common scale",
  "navigation": ["상점", "영웅", "모험", "동료", "성"],
  "start_button": {"width":360,"screen_width":640},
  "viewports": [[640,850],[640,1408]],
  "implementation": "HTML/CSS composition of existing native game resources; no generated substitute artwork"
}''',encoding='utf-8')
print(WORK/'index.html')
