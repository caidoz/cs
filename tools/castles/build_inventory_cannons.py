"""Pack the authored 6-column / 10-row cannon sheet into reusable item sprites."""
from pathlib import Path
import json
from collections import deque
from PIL import Image, ImageDraw, ImageFilter

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / 'content/castles/inventory_cannon'
OUT = ROOT / 'Resources/res/inventory_cannon'
PARTS = ROOT / 'Resources/res/castle_cannon_v2'
THEMES=['stone_catapult','flamethrower','rocket_battery','gatling','guided_missiles',
        'heavy_siege','ice_crystal','laser','tesla','gravity']
MUZZLES=[(.20,.10),(.96,.43),(.92,.28),(.98,.36),(.96,.18),
         (.94,.28),(.98,.20),(.98,.35),(.97,.30),(.97,.43)]


def isolate(cell):
    """Keep the gun body; authored sheet rows can contain stray neighbor pixels."""
    width,height=cell.size
    alpha=list(cell.getchannel('A').tobytes())
    seen=set()
    largest=[]
    for start,a in enumerate(alpha):
        if a<128 or start in seen:
            continue
        queue=deque([start]); seen.add(start); component=[]
        while queue:
            at=queue.popleft(); component.append(at)
            x,y=at%width,at//width
            for ny in range(max(0,y-1),min(height,y+2)):
                for nx in range(max(0,x-1),min(width,x+2)):
                    n=ny*width+nx
                    if alpha[n]>=128 and n not in seen:
                        seen.add(n); queue.append(n)
        if len(component)>len(largest):
            largest=component
    assert largest
    values=bytearray(width*height)
    for at in largest:
        values[at]=255
    mask=Image.frombytes('L',cell.size,bytes(values)).filter(ImageFilter.MaxFilter(3))
    clean=Image.composite(cell,Image.new('RGBA',cell.size),mask)
    return clean.crop(clean.getbbox())


def build():
    OUT.mkdir(parents=True, exist_ok=True)
    PARTS.mkdir(parents=True,exist_ok=True)
    master = Image.open(SOURCE / 'master_v2.png').convert('RGBA')
    assert master.getextrema()[3][0] == 0, 'Source must have real transparency'
    atlas = Image.new('RGBA', (576, 640))
    preview = Image.new('RGB', (1152, 1000), '#142337')
    draw = ImageDraw.Draw(preview)
    entries, frames = [], []
    gravity=Image.open(SOURCE/'gravity_sideview.png').convert('RGBA')
    ga=gravity.getchannel('A'); gravity_spans=[]; start=None
    for xx in range(gravity.width):
        occupied=sum(a>=128 for a in ga.crop((xx,0,xx+1,gravity.height)).tobytes())>2
        if occupied and start is None: start=xx
        if not occupied and start is not None: gravity_spans.append((start,xx)); start=None
    if start is not None: gravity_spans.append((start,gravity.width))
    assert len(gravity_spans)==6, gravity_spans
    alpha_bytes=master.getchannel('A').tobytes()
    row_counts=[sum(a>=128 for a in alpha_bytes[y*master.width:(y+1)*master.width]) for y in range(master.height)]
    row_cuts=[0]
    for row in range(1,10):
        expected=round(row*master.height/10)
        radius=round(master.height/10*.25)
        row_cuts.append(min(range(expected-radius,expected+radius+1),
            key=lambda y:(sum(row_counts[max(0,y-1):y+2]),abs(y-expected))))
    row_cuts.append(master.height)
    for castle in range(10):
        band=master.crop((0,row_cuts[castle],master.width,row_cuts[castle+1]))
        alpha=band.getchannel('A')
        col_counts=[sum(a>=128 for a in alpha.crop((x,0,x+1,band.height)).tobytes()) for x in range(master.width)]
        col_cuts=[0]
        for col in range(1,6):
            expected=round(col*master.width/6)
            radius=round(master.width/6*.2)
            col_cuts.append(min(range(expected-radius,expected+radius+1),
                key=lambda x:(sum(col_counts[max(0,x-1):x+2]),abs(x-expected))))
        col_cuts.append(master.width)
        for level in range(6):
            source_rect = (col_cuts[level],row_cuts[castle],col_cuts[level+1],row_cuts[castle+1])
            cell = master.crop(source_rect)
            source_file='master_v2.png'
            if castle==9:
                lo,hi=gravity_spans[level]
                source_rect=(lo,0,hi,gravity.height)
                cell=gravity.crop(source_rect)
                source_file='gravity_sideview.png'
            art = isolate(cell)
            cols, rows = (2 if level < 3 else 3), 2
            width, height = cols*32, rows*32
            body_width=[36,46,58,68,78,90][level]
            body_height=[28,34,42,48,54,58][level]
            scale = min(body_width/art.width, body_height/art.height)
            fitted = art.resize((max(1, round(art.width*scale)), max(1, round(art.height*scale))), Image.Resampling.NEAREST)
            icon = Image.new('RGBA', (width, height))
            icon.alpha_composite(fitted, ((width-fitted.width)//2, (height-fitted.height)//2))
            alpha=icon.getchannel('A').point(lambda a: 255 if a>=128 else 0)
            icon=icon.convert('RGB').quantize(colors=47,method=Image.Quantize.MEDIANCUT,
                dither=Image.Dither.NONE).convert('RGBA')
            icon.putalpha(alpha)
            icon=Image.composite(icon,Image.new('RGBA',icon.size),alpha)
            bx,by,right,bottom=icon.getbbox()
            bw,bh=right-bx,bottom-by
            muzzle_x=bx+round((bw-1)*MUZZLES[castle][0])
            muzzle_y=by+round((bh-1)*MUZZLES[castle][1])
            name = f'castle_{castle+1:02d}_lv_{level}.png'
            icon.save(OUT/name, optimize=True)
            part=icon.crop((bx,by,right,bottom)).resize((bw*2,bh*2),Image.Resampling.NEAREST)
            part.save(PARTS/name,optimize=True)
            sx, sy = level*96+(96-width)//2, castle*64
            atlas.alpha_composite(icon, (sx, sy))
            mask = 0x33 if cols == 2 else 0x77
            grade_names=['normal','superior','rare','set','epic','legend']
            entries.append(dict(castle=castle+1, level=level, grade=level, gradeName=grade_names[level], file=name, cols=cols, rows=rows,
                                cells=mask, size=[width,height], atlasRect=[sx,sy,width,height],
                                sourceRect=source_rect,sourceFile=source_file,theme=THEMES[castle],bodyRect=[bx,by,bw,bh],
                                muzzle=[muzzle_x,muzzle_y],partFile=f'castle_cannon_v2/{name}',
                                partSize=list(part.size)))
            frames.append(f'    {{{sx},{sy},{width},{height},{cols},{rows},0x{mask:X},{bx},{by},{bw},{bh},{muzzle_x},{muzzle_y}}},')
            x,y=level*192,castle*100
            draw.text((x+8,y+4), f'C{castle+1}  Lv.{level}  {cols}x{rows}',fill='#DFE9F2')
            for row in range(rows):
                for col in range(cols):
                    gx=x+(192-width)//2+col*32
                    draw.rectangle((gx,y+27+row*32,gx+31,y+58+row*32),outline='#3B506B')
            preview.paste(icon,(x+(192-width)//2,y+27),icon)
    atlas.save(OUT/'atlas.png', optimize=True)
    preview.save(SOURCE/'preview.png', optimize=True)
    (OUT/'manifest.json').write_text(json.dumps(dict(tileSize=32, castles=10, levels=6,
        atlas='atlas.png', atlasSize=list(atlas.size), items=entries),indent=2),encoding='utf-8')
    header = '''#pragma once
// Generated by tools/castles/build_inventory_cannons.py. Castle and level are zero based.
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
    for e in entries:
        icon = Image.open(OUT/e['file']).convert('RGBA')
        x,y,w,h=e['atlasRect']
        assert icon.tobytes()==atlas.crop((x,y,x+w,y+h)).tobytes()
        assert icon.getbbox() and icon.getextrema()[3][0]==0
        assert set(icon.getchannel('A').tobytes())<=set([0,255])
        assert len(icon.convert('RGB').getcolors(maxcolors=256))<=48
        assert e['cells'].bit_count()==e['cols']*e['rows']
    for castle in range(10):
        areas=[e['bodyRect'][2]*e['bodyRect'][3] for e in entries if e['castle']==castle+1]
        assert all(a<b for a,b in zip(areas,areas[1:])), (castle,areas)
    print('60 cannon sprites: increasing bodies, binary alpha, 48-color pixel art, masks, atlas and 2x castle parts verified')


if __name__ == '__main__':
    import sys
    current=ROOT/'content/castles/current_cannon_icons_v1/originals'
    if '--legacy' not in sys.argv and all((current/f'cannon-{i:02}.png').is_file() for i in range(1,11)):
        from register_current_cannon_icons import build as build_current
        build_current()
    else:
        build()
