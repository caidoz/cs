"""Register distinct grade art at inventory and mounted resolutions."""
from pathlib import Path
import json, shutil, hashlib
from PIL import Image, ImageDraw
from register_current_cannon_icons import THEMES, MUZZLES

ROOT=Path(__file__).resolve().parents[2]
SOURCE=ROOT/'content/castles/cannon_upgrades_v3'
OUT=ROOT/'Resources/res/inventory_cannon'
PARTS=ROOT/'Resources/res/castle_cannon_v2'
# Original source-coordinate mount rectangles; bottom is the existing balcony.
MOUNTS=[(920,290,510,345),(850,345,355,190),(790,530,375,245),
 (770,615,335,205),(700,615,400,265),(730,805,320,200),
 (675,850,365,190),(700,855,300,220),(625,915,325,215),(625,1000,300,190)]

def build():
    OUT.mkdir(parents=True,exist_ok=True); PARTS.mkdir(parents=True,exist_ok=True)
    inventory=Image.new('RGBA',(576,640)); mounted=Image.new('RGBA',(2304,2560))
    preview=Image.new('RGB',(1536,1600),'#142337'); draw=ImageDraw.Draw(preview)
    entries=[]; frames=[]; mountframes=[]
    for c in range(10):
        original=Image.open(ROOT/f'content/castles/outdoor_castles_v2/originals/castle-{c+1:02}.png').convert('RGBA')
        clean=Image.open(SOURCE/f'clean_castles/castle-{c+1:02}.png').convert('RGBA')
        assert abs(clean.width-original.width)<=1 and abs(clean.height-original.height)<=1, ('Clean castle canvas mismatch',c+1,clean.size,original.size)
        if clean.size!=original.size: clean=clean.resize(original.size,Image.Resampling.LANCZOS)
        # Register only the locally edited weapon aperture; all other original
        # castle pixels, including wheels and room geometry, stay byte exact.
        mx,my,mw,mh=MOUNTS[c]
        patch=(max(0,mx-15),max(0,my-85),min(original.width,mx+mw+35),min(original.height,my+mh+5))
        original.paste(clean.crop(patch),patch[:2])
        original.save(PARTS/f'unarmed-{c+1:02}.png')
        hashes=[]
        for level in range(6):
            name=f'castle_{c+1:02}_lv_{level}.png'
            source=SOURCE/'originals'/name
            if level==0:
                shutil.copy2(ROOT/f'content/castles/current_cannon_icons_v2/originals/cannon-{c+1:02}.png',source)
            art=Image.open(source).convert('RGBA')
            assert art.getextrema()[3][0]==0, source
            bounds=art.getchannel('A').point(lambda a:255 if a>=24 else 0).getbbox()
            art=art.crop(bounds); hashes.append(hashlib.sha256(art.tobytes()).hexdigest())
            cols=2 if level<3 else 3; rows=2; w=cols*32; h=64
            # Same physical grade progression in both exports, while retaining bag masks.
            icon=Image.new('RGBA',(w,h))
            s=min((w-6)/art.width,(h-6)/art.height)
            fitted=art.resize((max(1,round(art.width*s)),max(1,round(art.height*s))),Image.Resampling.LANCZOS)
            icon.alpha_composite(fitted,((w-fitted.width)//2,(h-fitted.height)//2))
            bx,by,rx,ry=icon.getbbox(); bw=rx-bx;bh=ry-by
            mx=bx+round((bw-1)*MUZZLES[c][0]);my=by+round((bh-1)*MUZZLES[c][1])
            x=level*96+(96-w)//2;y=c*64;mask=0x33 if cols==2 else 0x77
            icon.save(OUT/name);inventory.alpha_composite(icon,(x,y))
            frames.append('    {'+','.join(map(str,[x,y,w,h,cols,rows]))+f',0x{mask:X},'+','.join(map(str,[bx,by,bw,bh,mx,my]))+'},')
            # High-resolution export is independently fitted from original, never upscaled inventory pixels.
            s=min(372/art.width,244/art.height)
            part=art.resize((round(art.width*s),round(art.height*s)),Image.Resampling.LANCZOS)
            px=level*384+(384-part.width)//2;py=c*256+256-part.height
            mounted.paste(part,(px,py));part.save(PARTS/name)
            pmx=round((part.width-1)*MUZZLES[c][0]);pmy=round((part.height-1)*MUZZLES[c][1])
            mountframes.append('    {'+','.join(map(str,[px,py,part.width,part.height,pmx,pmy]))+'},')
            entries.append(dict(castle=c+1,level=level,grade=level,file=name,theme=THEMES[c],cols=cols,rows=rows,cells=mask,size=[w,h],atlasRect=[x,y,w,h],bodyRect=[bx,by,bw,bh],muzzle=[mx,my],sourceFile=str(source.relative_to(ROOT)),partFile=f'castle_cannon_v2/{name}',partRect=[px,py,part.width,part.height],sourceHash=hashes[-1]))
            thumb=part.copy();thumb.thumbnail((242,134),Image.Resampling.LANCZOS)
            tx=level*256;ty=c*160
            preview.paste(thumb,(tx+(256-thumb.width)//2,ty+24+(134-thumb.height)//2),thumb)
            draw.text((tx+8,ty+5),f'C{c+1:02}  Grade {level}',fill='white')
        assert len(set(hashes))==6, f'Castle {c+1}: repeated upgrade art'
    inventory.save(OUT/'atlas.png');mounted.save(PARTS/'atlas.png');preview.save(SOURCE/'preview.png')
    (OUT/'manifest.json').write_text(json.dumps(dict(tileSize=32,castles=10,levels=6,atlas='atlas.png',atlasSize=list(inventory.size),items=entries),indent=2),encoding='utf-8')
    header='''#pragma once
namespace InventoryCannons {
enum { Castles=10, Levels=6, Count=60, TileSize=32 };
struct Frame { int x,y,w,h,cols,rows; unsigned int cells; int bx,by,bw,bh,muzzleX,muzzleY; };
static const Frame frames[Count]={
'''+ '\n'.join(frames)+'''
};
inline const Frame& Get(int castle,int level) {
 castle=castle<0?0:castle>=Castles?Castles-1:castle;
 level=level<0?0:level>=Levels?Levels-1:level;
 return frames[castle*Levels+level];
}
}
'''
    (ROOT/'Classes/Data/InventoryCannonSprites.h').write_text(header,encoding='utf-8')
    header='''#pragma once
namespace MountedCannons {
struct Frame { int x,y,w,h,mx,my; };
struct Mount {int x,y,w,h;};
static const Mount mounts[10]={
'''+ '\n'.join(' {'+','.join(map(str,r))+'},' for r in MOUNTS)+'''
};
static const Frame frames[60]={
'''+ '\n'.join(mountframes)+'''
};
inline const Frame& Get(int c,int l) { return frames[(c<0?0:c>9?9:c)*6+(l<0?0:l>5?5:l)]; }
}
'''
    (ROOT/'Classes/Data/MountedCannonSprites.h').write_text(header,encoding='utf-8')
    for e in entries:
        x,y,w,h=e['atlasRect']
        assert Image.open(OUT/e['file']).convert('RGBA').tobytes()==inventory.crop((x,y,x+w,y+h)).tobytes()
        x,y,w,h=e['partRect']
        assert Image.open(PARTS/e['file']).convert('RGBA').tobytes()==mounted.crop((x,y,x+w,y+h)).tobytes()
        assert e['cells'].bit_count()==e['cols']*e['rows']
    print('PASS 60 distinct sources, 60 inventory frames, 60 high-resolution mounted frames, masks and atlas copies')

if __name__=='__main__':build()
