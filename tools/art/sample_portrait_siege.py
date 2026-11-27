"""Standalone layout study; never writes to the runtime resource tree."""
from pathlib import Path
import base64
import html
import json
import re

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'asset_library/work/portrait-siege-1x2_2'
OUT.mkdir(parents=True, exist_ok=True)

def asset(name):
    p = ROOT / 'Resources/res' / name
    data = p.read_bytes()
    mime = 'image/webp' if data[:4] == b'RIFF' else 'image/png'
    return 'data:' + mime + ';base64,' + base64.b64encode(data).decode()

def image(name, x, y, w, h):
    return f'<image href="{asset(name)}" x="{x}" y="{y}" width="{w}" height="{h}" preserveAspectRatio="xMidYMid meet"/>'

def rect(x,y,w,h,fill='#101e27',stroke='#83dce1',radius=10):
    return f'<rect x="{x}" y="{y}" width="{w}" height="{h}" rx="{radius}" fill="{fill}" stroke="{stroke}" stroke-width="1.5"/>'

def text(x,y,label,size=14,color='#f6f0d6',anchor='start'):
    return f'<text x="{x}" y="{y}" font-size="{size}" fill="{color}" text-anchor="{anchor}">{html.escape(str(label))}</text>'

frames = re.findall(r'\{(\d+),(\d+),(\d+),(\d+),(\d+),(\d+)\}', (ROOT/'Classes/Data/MountedCannonSprites.h').read_text())[-60:]
counts=[]
for stage in range(10):
    floors=1+stage*4//9
    removed=(5-floors)*138
    z=.205
    ground=420
    height=(1445-removed)*z
    s=['<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="500" height="1100" viewBox="0 0 500 1100">',
       '<style>text{font-family:Malgun Gothic,Segoe UI,sans-serif;font-weight:700}image{image-rendering:pixelated}</style>',
       '<defs><linearGradient id="sky" x2="0" y2="1"><stop stop-color="#050c15"/><stop offset="1" stop-color="#183340"/></linearGradient></defs>',
       '<rect width="500" height="1100" fill="#060d13"/>',rect(0,75,500,350,'url(#sky)','#060d13',0),
       text(22,34,'WAVE 03 / 15',22),text(330,34,'1250 G',21,'#ffd86a'),rect(452,12,33,32),text(468,35,'II',22,anchor='middle'),
       '<path d="M25 61H475" stroke="#415864" stroke-width="3"/>']
    for n in range(11): s.append(f'<circle cx="{25+n*45}" cy="61" r="4" fill="'+('#ffcf4c' if n<3 else '#415864')+'"/>')
    for n in range(8):
        x=n*73-15
        s += [rect(x,310-n%3*22,55,110+n%3*22,'#102632','#102632',0),rect(x+15,285-n%3*22,24,90,'#102632','#102632',0)]
    s += [text(22,99,f'Castle {stage+1:02d} / {floors}F',14,'#83dce1')]
    full=image(f'castle_mist_v2-{stage+1:02d}-hull.png',0,0,1089,1445)
    full+=image(f'castle_mist_v2-{stage+1:02d}-cover.png',175,548,740,760)
    for side,x in enumerate((90,795)):
        full+=image(f'castle_mist_v2-{stage+1:02d}-wheel-{side+1}.png',x,1180,205,205)
    # Remove complete modular floor bands, preserving every remaining source pixel's aspect.
    s += [f'<svg x="5" y="{ground-height}" width="{1089*z}" height="{550*z}" viewBox="0 0 1089 550">{full}</svg>',
          f'<svg x="5" y="{ground-height+550*z}" width="{1089*z}" height="{(895-removed)*z}" viewBox="0 {550+removed} 1089 {895-removed}">{full}</svg>']
    # Mounted atlas crop, positioned at the lower front independently of roof height.
    fx,fy,fw,fh,_,_=map(int,frames[stage*6])
    s += [rect(175,366,36,25,'#475263','#27343e',3),f'<svg x="178" y="340" width="95" height="65" viewBox="{fx} {fy} {fw} {fh}">{image("castle_cannon_v2-atlas.png",0,0,2304,2560)}</svg>']
    for i in range(3):
        s += [f'<svg x="{268+i*43}" y="362" width="36" height="58" viewBox="{i*20} 0 20 32">{image("c0.png",0,0,140,32)}</svg>']
    s += [f'<svg x="410" y="344" width="48" height="76" viewBox="60 0 20 32">{image("c0.png",0,0,140,32)}</svg>',text(420,328,'128',23,'#ffcf4c'),rect(0,420,500,9,'#536469','#536469',0),rect(22,443,290,9,'#45d68c'),rect(383,443,94,9,'#45d68c')]
    widths=[4+2*((stage-(3-y)+3)//4 if stage>3-y else 0) for y in range(4)]
    rows=[list(range((max(widths)-w)//2,(max(widths)+w)//2)) for w in widths]
    cols=max(widths)
    if stage==9: cols=8;rows=[[3,4]]+[list(range(8)) for _ in range(4)]
    counts.append(sum(map(len,rows)))
    s += [text(22,483,f'MERGE GRID / {counts[-1]} cells',14,'#83dce1'),rect(18,494,464,284,'#0b151d')]
    cell=52;top=508+(5-len(rows))*cell;left=(500-cols*cell)/2
    k=0
    for y,row in enumerate(rows):
        for x in row:
            px=left+x*cell;py=top+y*cell
            s += [rect(px+2,py+2,48,48,'#101e27','#51818a',8)]
            if k%3!=2:s += [image(f'grid_items-grid{k%12}.png',px+6,py+4,40,42)]
            else:s += [text(px+26,py+34,'+',23,'#3c555f','middle')]
            k+=1
    s += [text(22,803,'ROULETTE',12,'#ffcf4c'),rect(86,814,328,100,'#222331','#dfb55a',17)]
    for n in range(3):s += [rect(105+n*99,826,91,74,'#101923','#786344'),image(f'grid_items-grid{n}.png',124+n*99,831,53,62)]
    s += [text(40,950,'E',32,'#ffd552'),rect(85,928,310,24)]
    for n in range(5): s += [rect(92+n*59,934,52,12,'#53dc99' if n<3 else '#2d3e48','#2d3e48',2)]
    s += [text(416,947,'3 / 5',17)]
    for n,(label,icon) in enumerate([('포격','C'),('공격','X'),('돌리기','R')]):
        x=18+n*158
        s += [rect(x,978,148,70,'#211b11' if n==1 else '#0c1921','#ffc468' if n==1 else '#83dce1'),text(x+22,1020,icon,28),text(x+91,1007,label,18,anchor='middle'),text(x+91,1034,'-1',16,anchor='middle')]
    s += [text(22,1080,'Exit',13,'#879fa9'),text(478,1080,'Castle management >',13,'#879fa9','end'),'</svg>']
    (OUT/f'stage-{stage+1:02d}.svg').write_text(''.join(s),encoding='utf-8')

page=(Path(__file__).with_name('portrait_siege_template.html')).read_text(encoding='utf-8')
(OUT/'index.html').write_text(page,encoding='utf-8')
(OUT/'layout.json').write_text(json.dumps({'viewport':[500,1100],'stages':[{'stage':i+1,'cells':c,'floors':1+i*4//9} for i,c in enumerate(counts)],'runtime_modified':False},indent=2),encoding='utf-8')
assert counts == list(range(16,35,2))
print(OUT/'index.html')
