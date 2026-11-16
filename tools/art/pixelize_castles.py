"""열 성의 그림을 전부 같은 규칙으로 픽셀아트화한다 (pixelize_act 의 묶음 실행).

    python tools/art/pixelize_castles.py --act <팔레트.act> [--sat .75 --val .92 --pixel 2]

대상과 화면 배율
  - chassis-XX / parts-XX / rooms-XX (merge_castle_rebuild): 성채 588폭, 파츠 한 칸 110, 방 한 칸 150
  - front-cover-XX-v1: MergeCastleFronts::Frames[c] 가 battleFrontOuter(588×359)로 늘어나므로
    가로·세로 배율을 따로 준다(안 그러면 도트가 세로로 길어진다)
  - castle_cannon_v2/atlas.png: MountedCannonSprites.h 의 성별 6프레임 띠만 변환(한 칸 110폭)
  - 1성 로비: merge_castle_original/reference.png · deck-repair.png (640폭), wheel.png (116폭)
원본은 git 에 있다. 이 스크립트는 먼저 git checkout 으로 전부 되돌린 뒤 변환한다.
"""
import argparse, io, os, re, subprocess, sys
sys.path.insert(0,os.path.dirname(__file__))
import pixelize_act as px
from PIL import Image

ROOT=os.path.normpath(os.path.join(os.path.dirname(__file__),'..','..'))
REBUILD='Resources/res/merge_castle_rebuild'; ORIGINAL='Resources/res/merge_castle_original'
ATLAS='Resources/res/castle_cannon_v2/atlas.png'

def read_frames(path,name,count):
    text=open(os.path.join(ROOT,path),encoding='utf-8').read()
    body=text[text.index(name):]
    nums=re.findall(r'\{\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)',body)
    return [tuple(map(int,n)) for n in nums[:count]]

def load_rgba(path):
    # 파일 핸들을 잡은 채로 같은 자리에 쓰면 윈도우가 거부한다. 통째로 읽어 닫는다.
    with open(path,'rb') as f: data=f.read()
    return Image.open(io.BytesIO(data)).convert('RGBA')
def save_png(im,path):
    tmp=path+'.tmp'; im.save(tmp,format='PNG'); os.replace(tmp,path)
def convert(path,sw,sh,pal,a):
    im=load_rgba(path)
    vw=max(8,round(sw/a.pixel)); vh=max(8,round(sh/a.pixel)) if sh else 0
    save_png(px.pixelize(im,vw,pal,a.outline,a.sat,a.val,vh,a.dark_lo,a.dark_hi),path)
    print(f'{os.path.relpath(path,ROOT)}: screen {sw}x{sh or "-"} -> virtual {vw}x{vh or "-"}')

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--act',required=True); ap.add_argument('--pixel',type=float,default=2)
    ap.add_argument('--outline',type=int,default=1); ap.add_argument('--sat',type=float,default=.75); ap.add_argument('--val',type=float,default=.92)
    ap.add_argument('--dark-lo',type=float,default=0.0); ap.add_argument('--dark-hi',type=float,default=0.0,help='명도를 lo..hi 로 압축(어두운 무대)')
    ap.add_argument('--castles',default='1-10',help='예: 1  또는 1-3  또는 1,4,7')
    a=ap.parse_args(); pal=px.load_act(a.act); os.chdir(ROOT)
    sel=set()
    for part in a.castles.split(','):
        if '-' in part: lo,hi=part.split('-'); sel.update(range(int(lo),int(hi)+1))
        else: sel.add(int(part))
    castles=[c for c in range(10) if c+1 in sel]
    targets=[f'{REBUILD}/{k}-{c+1:02d}{"-v1" if k=="front-cover" else ""}.png' for c in castles for k in ('chassis','parts','rooms','front-cover')]
    if 0 in castles: targets+=[f'{ORIGINAL}/reference.png',f'{ORIGINAL}/deck-repair.png',f'{ORIGINAL}/wheel.png']
    subprocess.run(['git','checkout','--']+targets,check=True)
    fronts=read_frames('Classes/Data/MergeCastleFronts.h','Frame',10)
    cannons=read_frames('Classes/Data/MountedCannonSprites.h','frames[60]',60)
    for c in castles:
        convert(f'{REBUILD}/chassis-{c+1:02d}.png',588,0,pal,a)
        convert(f'{REBUILD}/parts-{c+1:02d}.png',6*110,0,pal,a)
        convert(f'{REBUILD}/rooms-{c+1:02d}.png',5*150,0,pal,a)
        cover=f'{REBUILD}/front-cover-{c+1:02d}-v1.png'; im=load_rgba(cover); fx,fy,fw,fh=fronts[c]
        convert(cover,round(im.width*588/fw),round(im.height*359/fh),pal,a)
    # 대포 아틀라스: 성마다 띠 하나씩. 고른 성의 띠만 원본으로 되돌려 다시 변환한다.
    atlas=load_rgba(ATLAS)
    original=Image.open(io.BytesIO(subprocess.run(['git','show','HEAD:'+ATLAS],capture_output=True).stdout)).convert('RGBA')
    for c in castles:
        fr=cannons[c*6:c*6+6]; y0=max(0,min(f[1] for f in fr)-4); y1=min(atlas.height,max(f[1]+f[3] for f in fr)+4)
        base_w=fr[0][2]; strip=original.crop((0,y0,atlas.width,y1))
        vw=max(8,round(atlas.width*110/base_w/a.pixel))
        atlas.paste(px.pixelize(strip,vw,pal,a.outline,a.sat,a.val,0,a.dark_lo,a.dark_hi),(0,y0))
        print(f'cannon atlas castle {c+1}: rows {y0}..{y1} -> virtual {vw}')
    save_png(atlas,ATLAS)
    if 0 in castles:
        convert(f'{ORIGINAL}/reference.png',640,0,pal,a); convert(f'{ORIGINAL}/deck-repair.png',640,0,pal,a); convert(f'{ORIGINAL}/wheel.png',116,0,pal,a)
if __name__=='__main__': main()
