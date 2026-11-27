"""Extract approved generated sheets into final, flat, directly used assets.

No authoring files are written into Resources. Resizing always uses one scale.
"""
from pathlib import Path
from PIL import Image
import argparse
import json
import shutil
import subprocess
import sys
import cv2
import numpy as np

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'asset_library/work/portrait-redesign-implementation'
SOURCES=WORK/'source'
FINALS=WORK/'final'
SOURCES.mkdir(parents=True,exist_ok=True);FINALS.mkdir(parents=True,exist_ok=True)
GENERATED=Path('C:/Users/polyp/.codex/generated_images/01a207f5-96b6-74a1-b712-379018a739b4')

def source(name):
    dst=SOURCES/name
    if not dst.exists():shutil.copy2(GENERATED/name,dst)
    return Image.open(dst).convert('RGBA')

def tight(im):
    # Retain real alpha and avoid one-pixel generated fringe deciding registration.
    mask=im.getchannel('A').point(lambda a:255 if a>100 else 0)
    bounds=mask.getbbox()
    if bounds is None:raise ValueError('Empty generated sprite')
    return im.crop(bounds)

def save(im,name):
    im.save(FINALS/name,optimize=True)
    return im.size

def isolated(im):
    """Remove only unrelated neighbouring sheet fragments, without deforming art."""
    a=np.array(im)
    count,labels,stats,_=cv2.connectedComponentsWithStats((a[:,:,3]>100).astype('uint8'),8)
    if count<2:return im
    main=1+int(np.argmax(stats[1:,cv2.CC_STAT_AREA]))
    x,y,w,h,_=stats[main]
    keep=labels==main
    for component in range(1,count):
        px,py,pw,ph,area=stats[component]
        if area>=12 and px>=x-8 and py>=y-12 and px+pw<=x+w+8 and py+ph<=y+h+8:
            keep|=labels==component
    a[~keep]=0
    return tight(Image.fromarray(a))

def ui():
    im=source('exec-f779d09c-4d80-4dab-aef1-f6170963e6a0.png')
    # Authoring sheet's final inspected cell regions, not assumed model coordinates.
    boxes=[(0,0,443,600),(443,0,887,600),(0,600,443,1000),(443,600,887,1000),
           (0,1000,443,1320),(443,1000,887,1320),(0,1320,443,1774),(443,1320,887,1774)]
    for i,box in enumerate(boxes):save(tight(im.crop(box)),f'portrait-ui-{i:02d}.png')
    bg=source('exec-4df15827-388e-4d74-8ee2-68f77bc8ebcd.png')
    save(bg,'portrait-night.png')

GROUPS=['exec-0bcee42f-a5a6-4544-939c-c70442222c87.png',
        'exec-c65c8f2e-9715-4e39-8dd4-f3617ec240f5.png',
        'exec-5d99e6e1-9dd9-4922-8141-173fded81502.png',
        'exec-37f4edb1-f242-4861-be34-28680e272ff2.png']

def castles():
    tall=json.loads((WORK/'tall-sources.json').read_text()) if (WORK/'tall-sources.json').exists() else {}
    dimensions=[]
    for group,name in enumerate(GROUPS):
        im=source(name);cols=4 if group==3 else 5
        # Three rows: hulls, wheels, and independently mounted cannons.
        # The first authored row is taller than the two equipment rows.
        row_edges=[0,round(im.height*.375),round(im.height*.69),im.height]
        if group==3:row_edges=[0,round(im.height*.385),round(im.height*.69),im.height]
        for col in range(cols):
            stage=group*5+col
            for row,kind in enumerate(('castle','wheel','turret')):
                x0=round(col*im.width/cols);x1=round((col+1)*im.width/cols)
                art=isolated(im.crop((x0,row_edges[row],x1,row_edges[row+1])))
                if row==0:
                    if str(group) in tall:
                        tower=source(tall[str(group)]);a=round(col*tower.width/cols);b=round((col+1)*tower.width/cols)
                        art=isolated(tower.crop((a,0,b,tower.height)))
                    # Native production master widths grow 20%; never stretch axes.
                    width=round(256*(1+.2*stage/18))
                    z=width/art.width
                    art=art.resize((width,round(art.height*z)),Image.Resampling.NEAREST)
                    dimensions.append(art.size)
                elif row==1:
                    z=128/max(art.size);art=art.resize((round(art.width*z),round(art.height*z)),Image.Resampling.NEAREST)
                else:
                    z=192/art.width;art=art.resize((192,round(art.height*z)),Image.Resampling.NEAREST)
                save(art,f'portrait-{kind}-{stage+1:02d}.png')
    h=['#pragma once','namespace PortraitCastleArt {','constexpr int Count=19;','struct Size {int w,h;};',
       'static const Size Sizes[Count]={'+','.join('{%d,%d}'%v for v in dimensions)+'};','}']
    (ROOT/'Classes/Data/PortraitCastleArt.h').write_text('\n'.join(h)+'\n')
    report={'count':19,'masters':[{'stage':i+1,'width':v[0],'height':v[1]} for i,v in enumerate(dimensions)],
            'width_ratio':dimensions[-1][0]/dimensions[0][0],'height_ratio':dimensions[-1][1]/dimensions[0][1]}
    (WORK/'original-dimensions.json').write_text(json.dumps(report,indent=2))
    print(json.dumps(report))

def register():
    c=json.loads((ROOT/'content/runtime-assets.json').read_text())
    known={a['target'] for a in c['assets']}
    for p in sorted(FINALS.glob('*.png')):
        target='res/'+p.name
        if target in known:
            record=next(a for a in c['assets'] if a['target']==target)
            master=ROOT/record.get('original_source',record['source'])
            shutil.copy2(p,master)
        else:
            subprocess.run([sys.executable,str(ROOT/'tools/assets/runtime_assets.py'),'add',str(p),'--name',p.name],check=True)

if __name__=='__main__':
    parser=argparse.ArgumentParser();parser.add_argument('--castles',action='store_true');parser.add_argument('--register',action='store_true');a=parser.parse_args()
    ui()
    if a.castles:castles()
    if a.register:register()
