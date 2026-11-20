"""Build a review page using original atlas pixels and native game captures."""
from pathlib import Path
import json

root=Path(__file__).resolve().parents[2]
spec=json.loads((root/'content/castles/four_facilities.json').read_text(encoding='utf-8-sig'))
data=json.dumps(spec['castles'],ensure_ascii=False)
page='''<!doctype html><html lang="ko"><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>성 시설 · 10개 성 × 6단계</title>
<style>
*{box-sizing:border-box}body{margin:0;background:#111b22;color:#e9dfc9;font:16px/1.6 system-ui,sans-serif}main{max-width:1400px;margin:auto;padding:24px}h1{font-size:26px;margin:0}p{color:#acc2c4}nav{display:flex;flex-wrap:wrap;gap:8px;margin:22px 0}button{background:#203c44;color:#e9dfc9;border:1px solid #648181;border-radius:6px;padding:10px 16px;cursor:pointer}button[aria-current=true]{background:#47613c;border-color:#d1af66}.controls{display:flex;align-items:center;gap:18px;background:#1b3039;padding:12px 18px;border-radius:8px}.controls input{flex:1}.cutaway{display:grid;grid-template-columns:1fr 1fr;gap:8px;margin:16px 0}.room{border:1px solid #657475;background:#19252b}.art{aspect-ratio:2;background-size:400% 600%;image-rendering:pixelated}.room p{font-size:14px;margin:8px 12px;color:#d8ccae}.captures{display:grid;grid-template-columns:1fr 1fr;gap:18px}.captures img{width:100%;display:block}.captures figure{margin:0}.captures figcaption{padding:8px;background:#1b3039}a{color:#b4d8e2}.links{display:flex;flex-wrap:wrap;gap:18px;margin-top:18px}details{margin-top:20px}summary{cursor:pointer}small{color:#acc2c4}@media(max-width:700px){main{padding:12px}.captures{gap:8px}.room p{font-size:12px}.controls{gap:8px}}
</style><main>
<h1>성 시설 리디자인 · 10개 성 × 6단계</h1>
<p>위층은 공격·방어, 아래층은 생산·활력. 성마다 생활 공간과 과학 설비를 다르게 구성했습니다. 실내 비교에는 게임과 같은 128×64 픽셀 단위와 톤 보정을 적용했고, 실제 게임 캡처에서는 걷는 동료와 함께 확인할 수 있습니다.</p>
<nav id="castles"></nav><div class="controls"><b id="selected"></b><input id="level" aria-label="강화 단계" type="range" min="0" max="5" value="5"><strong id="lv"></strong></div>
<div class="cutaway" id="rooms"></div>
<div class="captures"><figure><figcaption>실제 게임 · 기본 단계</figcaption><img id="base" alt="기본 단계 실제 게임 캡처"></figure><figure><figcaption>실제 게임 · 최대 강화</figcaption><img id="max" alt="최대 강화 실제 게임 캡처"></figure></div>
<div class="links"><a id="atlas">6단계 원본 아틀라스</a><a href="../four-facility-menu/850/facilities.png">강화 메뉴</a><a href="../four-facility-menu/850/upgrade-confirm.png">강화 확인</a><a href="../four-facility-menu/850/castle-10-rooms.png">후반 성 시설 메뉴</a></div>
<details><summary>기능·성장 규칙</summary><p>방 네 곳은 성을 바꿔도 강화 단계가 유지됩니다. 생산 시설은 골드 생산·저장, 공격 시설은 히어로 공격력, 휴식 시설은 최대 체력, 방어 시설은 방어력을 강화합니다. 포탑은 성별로 강화하며, 첨탑은 고유 실루엣을 유지하고 연결부와 지지대만 함께 보강합니다.</p></details>
<small>목재 성의 닭·토끼 재배 공간부터 비취 양식장, 봉황 온천, 수정 결계 연구실, 왕실 스위트까지 서로 다른 구성을 사용합니다. 앞쪽 바닥은 동료의 이동 공간으로 비워 둡니다.</small>
</main><script>
const themes=__DATA__;
let castle=0;
const roles=['생산 · 골드','공격 · 히어로 공격력','활력 · 최대 체력','방어 · 방어력'];
const nav=document.getElementById('castles'),slider=document.getElementById('level');
themes.forEach((c,i)=>{let b=document.createElement('button');b.textContent=`성 ${c.id}`;b.onclick=()=>{castle=i;render()};nav.append(b)});
function render(){const c=themes[castle],lv=+slider.value;
 document.getElementById('selected').textContent=`성 ${c.id}`;document.getElementById('lv').textContent=`Lv.${lv} / 5`;
 [...nav.children].forEach((b,i)=>b.setAttribute('aria-current',i===castle));
 const path=`../../asset_library/reference/Resources/res/castle_four_rooms_v5/rooms-${c.id}.png`;
 document.getElementById('rooms').replaceChildren();
 [1,3,0,2].forEach(i=>{let box=document.createElement('section');box.className='room';let art=document.createElement('canvas');art.className='art';art.width=128;art.height=64;art.style.width='100%';art.style.display='block';let image=new Image();image.onload=()=>{let ctx=art.getContext('2d');ctx.imageSmoothingEnabled=false;const shade=[.92,.70,.85,.92,.92,.92,.92,.80,.92,.90][castle];ctx.filter=`saturate(.84) brightness(${shade})`;ctx.drawImage(image,image.width*i/4,image.height*lv/6,image.width/4,image.height/6,0,0,128,64)};image.src=path;let label=document.createElement('p');label.textContent=`${c.names[i]} · ${roles[i]}`;box.append(art,label);document.getElementById('rooms').append(box)});
 document.getElementById('base').src=`../item-series/runtime/facility-rooms-850/facility-c${c.id}-level-0.png`;
 document.getElementById('max').src=`../item-series/runtime/facility-rooms-850/facility-c${c.id}-level-5.png`;
 document.getElementById('atlas').href=path;
}
slider.oninput=render;render();
</script></html>'''.replace('__DATA__',data)
dest=root/'output/castle-four-room-design/index.html'
dest.parent.mkdir(parents=True,exist_ok=True)
dest.write_text(page,encoding='utf-8')
print(dest)
