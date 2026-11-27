"""Compare authored castle silhouettes at one scale, never fit each to a box."""
from pathlib import Path
from PIL import Image
import base64
import html
import json
import argparse

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'asset_library/work/portrait-redesign-implementation'
parser=argparse.ArgumentParser()
parser.add_argument('--art-dir',type=Path,default=WORK/'final')
parser.add_argument('--output',type=Path,default=WORK/'lineup')
args=parser.parse_args()
ART=args.art_dir
OUT=args.output
OUT.mkdir(parents=True,exist_ok=True)
NAMES=['목조 전초성','숲의 수호성','사막의 황금성','해적 선상성','빙하 요새',
       '철갑 공업성','흑요 화산성','태엽 기계성','망령 고딕성','수정 마도성',
       '산호 해양성','비취 천수각','거대 버섯성','별빛 관측성','적룡 요새',
       '뇌전 강철성','마계 흑철성','천상 성채','최종 왕궁성']
SIZE=[(Image.open(ART/f'portrait-castle-{i+1:02d}.png').size) for i in range(19)]

def embed(name,x,y,w,h):
    raw=(ART/name).read_bytes()
    return f'<image href="data:image/png;base64,{base64.b64encode(raw).decode()}" x="{x}" y="{y}" width="{w}" height="{h}" preserveAspectRatio="xMidYMid meet"/>'

def label(x,y,s,size=16,color='#d4e6e4',anchor='middle'):
    return f'<text x="{x}" y="{y}" font-size="{size}" fill="{color}" text-anchor="{anchor}">{html.escape(s)}</text>'

def render(columns,scale,name):
    cell=round(342*scale)
    rows=(19+columns-1)//columns
    rowheights=[round((max(h for w,h in SIZE[row*columns:min(19,(row+1)*columns)])+120)*scale)+80 for row in range(rows)]
    width=cell*columns+40;height=sum(rowheights)+130
    pieces=[f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}">',
            '<style>text{font-family:Malgun Gothic,sans-serif;font-weight:700}image{image-rendering:pixelated}</style>',
            f'<rect width="{width}" height="{height}" fill="#080e18"/>',
            label(24,38,'19 CASTLES · 외관 / 바퀴 / 포탑 분리 시안',26,anchor='start'),
            label(24,68,'전 단계 같은 배율 · 같은 바닥선 · 단계별 자동 크기 맞춤 없음',16,'#8aa5b5','start')]
    for row in range(rows):
        ground=95+sum(rowheights[:row+1])-72
        pieces+=[f'<path d="M20 {ground}H{width-20}" stroke="#516471" stroke-width="2"/>']
        for index in range(row*columns,min(19,(row+1)*columns)):
            col=index%columns;x=20+col*cell+12*scale
            w,h=SIZE[index];w*=scale;h*=scale
            wheel_art=Image.open(ART/f'portrait-wheel-{index+1:02d}.png')
            wheel=(wheel_art.width if ART.name=='art' else 78)*scale;bottom=ground-wheel*.58
            # Large wheels and a common ground contact make the load path visible.
            pieces += [f'<ellipse cx="{x+w*.5}" cy="{ground+2}" rx="{w*.52}" ry="{8*scale}" fill="#020407"/>']
            pieces += [embed(f'portrait-castle-{index+1:02d}.png',x,bottom-h,w,h)]
            for axle in ([.15,.5,.85] if index>=5 else [.17,.83]):
                pieces += [embed(f'portrait-wheel-{index+1:02d}.png',x+w*axle-wheel/2,ground-wheel,wheel,wheel)]
            gun=Image.open(ART/f'portrait-turret-{index+1:02d}.png')
            gw=(gun.width if ART.name=='art' else 100)*scale;gh=gw*gun.height/gun.width
            pieces += [embed(f'portrait-turret-{index+1:02d}.png',x+w*.82-gw*.15,bottom-gh+8*scale,gw,gh)]
            pieces += [label(x+w*.5,ground+30,f'{index+1:02d}  {NAMES[index]}',max(12,round(19*scale))),
                       label(x+w*.5,ground+51,f'본체 {SIZE[index][0]} × {SIZE[index][1]} px',max(10,round(14*scale)),'#7f9aaa')]
    pieces+=['</svg>']
    (OUT/(name+'.svg')).write_text(''.join(pieces),encoding='utf-8')
    (OUT/(name+'.html')).write_text(f'<!doctype html><meta charset="utf-8"><style>html,body{{margin:0;background:#080e18}}img{{display:block;width:{width}px;height:{height}px}}</style><img src="{name}.svg">',encoding='utf-8')
    print(name,width,height)

render(19,1,'full-lineup')
render(5,.68,'overview')
(OUT/'index.html').write_text('''<!doctype html><meta charset="utf-8"><style>body{margin:20px;background:#080e18;color:#eee;font:16px system-ui}img{max-width:100%}a{color:#9ce4df}</style><h1>19개 성 · 크기와 콘셉트 비교</h1><p>동일 배율로 비교한 초안입니다. 최종 리소스로 확정하지 않았습니다.</p><a href="full-lineup.png">19개 한 줄 원본 이미지</a> · <a href="overview.png">전체 비교 이미지</a><p><img src="overview.png"></p>''',encoding='utf-8')
