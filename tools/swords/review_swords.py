"""Offline CMF comparison sheet; effects are omitted to expose grip alignment."""
import json
import math
from pathlib import Path
from PIL import Image, ImageDraw, ImageOps
from build_sword_poses import ROOT, array


def build():
    blob=(ROOT/'Classes/Data/CmfBlob.cpp').read_text(encoding='utf-8-sig')
    mi,cnt,off=[array(blob,n) for n in ('cmfMotionImgBlob','cmfMotionImgCntBlob','cmfOffBlob')]
    poses=json.loads((ROOT/'content/swords/poses.json').read_text())
    by_name={p['name']:p for p in poses}
    sprites=json.loads((ROOT/'content/swords/sprites.json').read_text())
    selected=['PO_C0_N0','PO_C0_A0','PO_C0_A1_2','PO_C0_A2','PO_C0_A5','PO_C0_CRASH4_2']
    sheets={n:Image.open(ROOT/f'Resources/res/{n}.png').convert('RGBA')
            for n in ('cc','a0_0','p0_0','c0','d0_0','l0_0','h0_0')}
    out=Image.new('RGB',(6*800,4*660),'#282b32')
    draw=ImageDraw.Draw(out)
    for col,name in enumerate(selected):
        p=by_name[name]; m=p['motion']
        parts=[mi[i:i+4] for i in range(cnt[m*2]*4,(cnt[m*2]+cnt[m*2+1])*4,4)]
        for row,(sword,legacy,facing) in enumerate(((11,True,False),(11,False,False),(35,False,False),(35,False,True))):
            tile=Image.new('RGBA',(800,630)); ox,oy=400,515; drawn=False
            for img,x,y,flags in parts:
                if img>=110:continue
                if img in (108,109) and not legacy:
                    if drawn:continue
                    drawn=True
                    info=sprites[sword-1]
                    im=Image.open(ROOT/f'Resources/res/w0_{sword}.png')
                    hx=ox+(-p['handX'] if facing else p['handX']);hy=oy+p['handY']
                    angle=math.radians(-p['angleDegrees'] if facing else p['angleDegrees'])
                    f=-1 if (p['flipX'] != facing) else 1
                    c,s=math.cos(angle)/p['scale'],math.sin(angle)/p['scale']
                    affine=(f*c,f*s,info['pivotX']-f*c*hx-f*s*hy,-s,c,info['pivotY']+s*hx-c*hy)
                    layer=im.transform(tile.size,Image.Transform.AFFINE,affine,Image.Resampling.NEAREST)
                    tile.alpha_composite(layer)
                    continue
                source=(Image.open(ROOT/f'content/swords/source/w0_{sword}.png') if img>=108 else
                        sheets['cc' if img<62 else 'a0_0' if img<65 else 'p0_0' if img<67 else
                               'c0' if img<72 else 'd0_0' if img<95 else 'l0_0' if img<106 else 'h0_0'])
                sx,sy,w,h=off[img*4:img*4+4]
                im=source.crop((sx,sy,sx+w,sy+h))
                flip=bool(flags&1) != facing
                if flip:im=ImageOps.mirror(im)
                q=(flags&6)>>1;angle=(-1 if flip else 1)*q*90
                im=im.rotate(-angle,expand=True,resample=Image.Resampling.NEAREST)
                scale=(flags>>6)+1
                if scale!=1:im=im.resize((im.width*scale,im.height*scale),Image.Resampling.NEAREST)
                x=ox+(-x-im.width if facing else x);y=oy+y
                tile.alpha_composite(im,(x,y))
            out.paste(tile,(col*800,row*660+27),tile)
            draw.text((col*800+8,row*660+8),f'{name}  w0_{sword} '+('OLD' if legacy else 'NEW')+(' RIGHT' if facing else ''),fill='white')
    out.save(ROOT/'output/swords/motion-review.png')
    print('output/swords/motion-review.png')


if __name__=='__main__':build()
