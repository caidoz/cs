"""Package unmodified combined exterior concepts with a side-by-side review."""
from pathlib import Path
from PIL import Image
import json,zipfile

ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'content/castles/outdoor_castles_v2'

def main():
    rows=[];cards=[]
    for castle in range(1,11):
        path=OUT/'originals'/f'castle-{castle:02}.png'
        im=Image.open(path).convert('RGBA')
        assert im.getchannel('A').getextrema()[0]==0,path
        bounds=im.getchannel('A').point(lambda a:255 if a>=192 else 0).getbbox()
        x,y,right,bottom=bounds
        wheels=2 if castle<=4 else 3 if castle<=7 else 4
        rows.append(dict(castle=castle,file=str(path.relative_to(OUT)),width=im.width,height=im.height,
            wheelCount=wheels,targetWheelDiameterScale=2/3,transparent=True))
        width=220+(castle-1)*4
        scale=width/(right-x)
        cards.append(f'<article><a class="art" href="originals/{path.name}" style="width:{width}px"><span style="position:relative;overflow:hidden;display:block;width:{width}px;height:{(bottom-y)*scale:.2f}px"><img style="position:absolute;width:{im.width*scale:.2f}px;left:{-x*scale:.2f}px;top:{-y*scale:.2f}px" src="originals/{path.name}" alt="Castle {castle}"></span></a><p>{castle:02} · 바퀴 {wheels}개</p></article>')
    (OUT/'manifest.json').write_text(json.dumps(rows,indent=2),encoding='utf-8')
    html='''<!doctype html><html lang="ko"><meta charset="utf-8"><title>야외 데크 성 10종</title>
<style>body{margin:28px;background:#142032;color:#ecf2ff;font:16px system-ui}h1{font-size:24px}p{color:#c8d7e8}main{display:flex;gap:24px;overflow-x:auto;align-items:end;padding:20px 0}article{flex:none;text-align:center}.art{height:750px;display:flex;align-items:end}img{width:100%;height:auto;display:block}a{color:inherit}.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(250px,1fr));gap:20px}.grid img{max-height:650px;object-fit:contain}</style>
<h1>난간 없는 야외 전투 데크 · 성 10종</h1><p>동일한 접지선으로 비교합니다. 이미지를 누르면 원본을 엽니다. 바퀴: 1–4단계 2개 / 5–7단계 3개 / 8–10단계 4개. 새 원화이며 게임에는 아직 적용하지 않았습니다.</p><main>'''+''.join(cards)+'''</main><p>하단 슬라이더로 좌우 이동해 전체 진행을 확인할 수 있습니다.</p></html>'''
    (OUT/'index.html').write_text(html,encoding='utf-8')
    with zipfile.ZipFile(OUT/'outdoor-castles-10.zip','w',zipfile.ZIP_DEFLATED) as z:
        for row in rows:z.write(OUT/row['file'],row['file'])
        z.write(OUT/'manifest.json','manifest.json')
        z.write(OUT/'index.html','index.html')
    print('PASS ten intact transparent originals, manifest, review HTML and ZIP')

if __name__=='__main__':main()
