"""AI 가 그린 성 리소스를 고정 팔레트 픽셀아트로 바꾼다 (오프라인, 결정적).

    python tools/art/pixelize_act.py --act <팔레트.act> [--pixel 3] [--outline 1] 파일...

규칙
  - 화면에 찍히는 크기(--screen-width, 기본은 파일별 표)로 BOX 다운샘플해 "가상 픽셀"을 만든다.
    가상 1픽셀 = 화면 --pixel 픽셀. 동료 스프라이트 c0~c122 가 2X 라 기본 2 - 같은 도트 간격.
  - --sat/--val 로 채도·명도를 낮춘다. 성은 배경이라 0.65/0.92 를 쓴다(동료 채도 0.4~0.6 에 맞춤).
  - 색은 .act 팔레트(256색 RGB) 중 Lab 거리로 가장 가까운 것 하나로 바꾼다. 디더 없음.
  - 투명 경계(구멍 포함)에 가상 --outline 픽셀의 어두운 선을 두른다(팔레트에서 가장 어두운 색).
  - 결과는 원본과 같은 픽셀 크기로 NEAREST 확대해 저장한다. 좌표표(MergeCastleRebuild.h)가 그대로다.
원본은 git 에 있다. 되돌리려면 git checkout -- <파일>.
"""
import argparse, os, sys
import numpy as np
from PIL import Image

def to_lab(rgb):
    rgb=np.asarray(rgb,float)/255.0; m=rgb>0.04045
    rgb=np.where(m,((rgb+0.055)/1.055)**2.4,rgb/12.92)
    M=np.array([[0.4124,0.3576,0.1805],[0.2126,0.7152,0.0722],[0.0193,0.1192,0.9505]])
    xyz=rgb@M.T/np.array([0.95047,1.0,1.08883])
    f=np.where(xyz>0.008856,np.cbrt(xyz),7.787*xyz+16/116)
    return np.stack([116*f[...,1]-16,500*(f[...,0]-f[...,1]),200*(f[...,1]-f[...,2])],-1)

def load_act(path):
    b=open(path,'rb').read()
    n=min(256,len(b)//3)
    return np.array([[b[i*3],b[i*3+1],b[i*3+2]] for i in range(n)],float)

def tone(rgb,sat,val):
    """채도·명도를 줄인다(HSV). 성은 배경이라 동료 스프라이트(c0~c122, 채도 0.4~0.6)보다
    가라앉아야 사람이 앞으로 나온다. 원본 성은 채도 0.8 이다."""
    mx=rgb.max(-1); mn=rgb.min(-1); d=mx-mn
    s=np.where(mx>0,d/np.maximum(mx,1e-6),0)*sat; v=mx*val
    # 같은 색상(hue)을 유지한 채 채도·명도만 바꾼다: 각 채널을 mx 기준으로 재구성
    ratio=np.where(d[...,None]>0,(mx[...,None]-rgb)/np.maximum(d[...,None],1e-6),0)
    out=v[...,None]*(1-s[...,None]*ratio)
    return np.clip(out,0,255)

def dark_stage(rgb,lo,hi):
    """명도를 lo..hi 띠로 압축한다. 배경(성)은 화면 명도의 아래 절반에만 살게 해서
    캐릭터·숫자가 앞으로 나오게 하는 값 계층이다. 색상은 그대로 두고 밝기만 누른다."""
    mx=rgb.max(-1,keepdims=True)/255.0
    span=max(1e-6,float(mx.max()-mx.min()))
    v2=lo+(mx-mx.min())/span*(hi-lo)
    return np.clip(np.where(mx>0,rgb/np.maximum(mx,1e-6),0)*v2*255.0,0,255)

def pixelize(im,virtual_w,pal,outline,sat=1.0,val=1.0,virtual_h=0,dark_lo=0.0,dark_hi=0.0):
    k=im.width/virtual_w
    # 가로·세로가 다른 배율로 늘어나는 그림(전면 덮개)은 세로 가상 크기를 따로 받는다 -
    # 그래야 화면에서 도트가 정사각형이 된다.
    small=im.resize((virtual_w,max(1,virtual_h or round(im.height/k))),Image.BOX)
    arr=np.array(small).astype(float); alpha=arr[...,3]>96
    if sat!=1.0 or val!=1.0: arr[...,:3]=tone(arr[...,:3],sat,val)
    if dark_hi>0: arr[...,:3]=dark_stage(arr[...,:3],dark_lo,dark_hi)
    lab=to_lab(arr[...,:3]); lp=to_lab(pal)
    # 메모리: 줄 단위로 가장 가까운 팔레트 색을 찾는다
    idx=np.empty(alpha.shape,int)
    for y in range(lab.shape[0]):
        idx[y]=((lab[y][:,None,:]-lp[None,:,:])**2).sum(2).argmin(1)
    q=np.zeros_like(arr); q[...,:3]=pal[idx]; q[...,3]=np.where(alpha,255,0)
    edge=alpha.copy(); dark=pal[np.argmin(lp[:,0])]
    for _ in range(outline):
        inner=edge&np.roll(edge,1,0)&np.roll(edge,-1,0)&np.roll(edge,1,1)&np.roll(edge,-1,1)
        q[edge&~inner,:3]=dark; edge=inner
    out=Image.fromarray(q.astype(np.uint8))
    return out.resize(im.size,Image.NEAREST)

# 파일별로 화면에 찍히는 폭(640 기준). 없으면 --screen-width.
#  성채·전면 덮개: 모든 성이 1성의 고정 외곽(OriginalCastle::box(48,83,1000,1252))에 들어간다.
#  폭 1000 × (640/1089) = 588. 판이 커져도 성 자체는 커지지 않는다(castleMap).
SCREEN={}
for c in range(10):
    SCREEN[f'chassis-{c+1:02d}.png']=588
    SCREEN[f'front-cover-{c+1:02d}-v1.png']=588
    SCREEN[f'parts-{c+1:02d}.png']=6*110   # 6칸 아틀라스, 대포 한 칸이 화면 110

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--act',required=True); ap.add_argument('--pixel',type=float,default=2)
    ap.add_argument('--outline',type=int,default=1); ap.add_argument('--screen-width',type=int,default=0)
    ap.add_argument('--out',default='')
    ap.add_argument('--sat',type=float,default=1.0); ap.add_argument('--val',type=float,default=1.0)
    ap.add_argument('--screen-height',type=int,default=0,help='세로가 다른 배율로 늘어나는 그림의 화면 높이')
    ap.add_argument('--dark-lo',type=float,default=0.0); ap.add_argument('--dark-hi',type=float,default=0.0,help='명도를 lo..hi 로 압축(어두운 무대). 0 이면 끔')
    ap.add_argument('files',nargs='+')
    a=ap.parse_args(); pal=load_act(a.act)
    for f in a.files:
        im=Image.open(f).convert('RGBA'); name=os.path.basename(f)
        sw=a.screen_width or SCREEN.get(name)
        if not sw: print('skip (screen width unknown):',name); continue
        vw=max(8,round(sw/a.pixel)); vh=max(8,round(a.screen_height/a.pixel)) if a.screen_height else 0
        out=pixelize(im,vw,pal,a.outline,a.sat,a.val,vh,a.dark_lo,a.dark_hi)
        dest=os.path.join(a.out,name) if a.out else f
        if a.out: os.makedirs(a.out,exist_ok=True)
        out.save(dest); print(f'{name}: screen {sw} -> virtual {vw}px wide -> {dest}')
if __name__=='__main__': main()
