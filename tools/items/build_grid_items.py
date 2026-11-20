"""Package AI repaints as grid-only RGBA art, preserving original canvas ratios."""
from pathlib import Path
import hashlib
import json
from PIL import Image
import numpy as np

ROOT = Path(__file__).resolve().parents[2]
WORK = ROOT / 'output/grid-items'
DEST = ROOT / 'asset_library/reference/Resources/res/grid_items'

def boundaries(sheet, count, axis):
    """Find transparent gutters near expected cell edges, not through blade tips."""
    alpha=np.array(sheet.getchannel('A'))
    profile=(alpha>160).sum(axis=axis)
    length=len(profile);cuts=[0]
    for edge in range(1,count):
        lo=round((edge-.22)*length/count);hi=round((edge+.22)*length/count)
        section=profile[lo:hi]
        if section.min()>2: raise ValueError('Atlas has no clear gutter')
        candidates=np.flatnonzero(section<=section.min()+2)+lo
        cuts.append(int(np.median(candidates)))
    return cuts+[length]

def clean_cell(tile):
    """Discard faint atlas matte and tiny detached fragments at cell boundaries."""
    alpha=np.array(tile.getchannel('A'))
    active=alpha>32
    seen=np.zeros(active.shape,dtype=bool)
    components=[]
    height,width=active.shape
    for y,x in zip(*np.nonzero(active)):
        if seen[y,x]: continue
        seen[y,x]=True
        stack=[(int(y),int(x))];pixels=[]
        while stack:
            py,px=stack.pop();pixels.append((py,px))
            for ny,nx in ((py-1,px),(py+1,px),(py,px-1),(py,px+1)):
                if 0<=ny<height and 0<=nx<width and active[ny,nx] and not seen[ny,nx]:
                    seen[ny,nx]=True;stack.append((ny,nx))
        components.append(pixels)
    if not components: raise ValueError('Empty generated cell')
    cutoff=max(3,max(map(len,components))*.01)
    keep=np.zeros(active.shape,dtype=bool)
    for pixels in components:
        if len(pixels)>=cutoff:
            ys,xs=zip(*pixels);keep[ys,xs]=True
    alpha[~keep]=0
    tile.putalpha(Image.fromarray(alpha))
    return tile

def build():
    catalog = json.loads((WORK/'catalog.json').read_text())
    generation = json.loads((WORK/'generation.json').read_text())
    sheets = {r['name']: Image.open(ROOT/r['saved']).convert('RGBA') for r in generation['sheets']}
    cuts={name:(boundaries(sheet,catalog['groups'][name]['cols'],0),
                boundaries(sheet,catalog['groups'][name]['rows'],1)) for name,sheet in sheets.items()}
    DEST.mkdir(parents=True, exist_ok=True)
    entries = catalog['entries']
    for e in entries:
        sheet = sheets[e['group']]
        group = catalog['groups'][e['group']]
        c,r = e['cell']%group['cols'], e['cell']//group['cols']
        xs,ys=cuts[e['group']]
        rect=(xs[c],ys[r],xs[c+1],ys[r+1])
        tile = clean_cell(sheet.crop(rect))
        bbox = tile.getchannel('A').point(lambda a:255 if a>32 else 0).getbbox()
        if bbox is None: raise ValueError(f'Empty grid sprite {e["id"]}')
        tile = tile.crop(bbox)
        # Native canvas and occupied rectangle are retained at 4x resolution.
        # This keeps narrow swords tall without forcing a square icon silhouette.
        width,height = (v*4 for v in e['size'])
        target = Image.new('RGBA',(width,height))
        x0,y0,x1,y1 = (v*4 for v in e['bbox'])
        tile.thumbnail((x1-x0,y1-y0),Image.Resampling.LANCZOS)
        # thumbnail avoids upscaling: explicitly resize small generated objects.
        scale=min((x1-x0)/tile.width,(y1-y0)/tile.height)
        tile=tile.resize((max(1,round(tile.width*scale)),max(1,round(tile.height*scale))),Image.Resampling.LANCZOS)
        target.alpha_composite(tile,(x0+(x1-x0-tile.width)//2,y0+(y1-y0-tile.height)//2))
        filename=f'grid{e["id"]}.png'
        target.save(DEST/filename)
        e['file']=f'asset_library/reference/Resources/res/grid_items/{filename}'
        e['output_size']=[width,height]
        e['source_sha256']=hashlib.sha256((ROOT/e['source']).read_bytes()).hexdigest()
    (DEST/'manifest.json').write_text(json.dumps(dict(entries=entries),indent=2))
    # Original and replacement side by side for every item, rendered at useful size.
    cards=[]
    for e in entries:
        cards.append(f'<article><b>{e["group"]} {e["detail"]+1} / type {e["type"]}</b><div><img src="../../{e["source"]}"><img src="../../{e["file"]}"></div></article>')
    (WORK/'index.html').write_text('<!doctype html><meta charset="utf-8"><title>Grid equipment: original / repaint</title><style>body{background:#19272a;color:#ead7b7;font:14px sans-serif}main{display:grid;grid-template-columns:repeat(auto-fill,minmax(270px,1fr));gap:12px}article{background:#384446;padding:10px}article div{display:flex;gap:12px;height:180px}img{width:46%;height:100%;object-fit:contain}</style><h1>Grid equipment: original / repaint (225)</h1><main>'+''.join(cards)+'</main>')
    print(f'Packaged {len(entries)} grid-only sprites')

if __name__=='__main__': build()
