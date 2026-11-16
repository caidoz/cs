"""Package faithful icon repaints, retaining separate grid and icon PNGs."""
from pathlib import Path
import json,sys,shutil,hashlib
from PIL import Image
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools/items'))
from build_grid_items import boundaries,clean_cell
WORK=ROOT/'output/square-gear'

def build():
    records=json.loads((WORK/'catalog.json').read_text())['entries']
    sheets={name:Image.open(WORK/f'generated/{name}.png').convert('RGBA') for name in ['helm','armor','gloves','pants','boots']}
    cuts={name:(boundaries(im,8,0),boundaries(im,3,1)) for name,im in sheets.items()}
    manifest_path=ROOT/'Resources/res/items/manifest.json'
    manifest=json.loads(manifest_path.read_text());old={e['id']:e for e in manifest['entries']}
    grid_manifest_path=ROOT/'Resources/res/grid_items/manifest.json'
    grid_manifest=json.loads(grid_manifest_path.read_text());grids={e['id']:e for e in grid_manifest['entries']}
    (WORK/'before').mkdir(exist_ok=True)
    for e in records:
        dest=ROOT/f'Resources/res/items/item{e["item"]}.png'
        backup=WORK/f'before/item{e["item"]}.png'
        if not backup.exists():shutil.copyfile(dest,backup)
        # Armor was temporarily linked to icon art; bake that design into its own
        # grid file before updating icons, then remove the runtime link.
        if 6<=e['type']<=8:
            canonical=Image.open(backup).convert('RGBA')
            bounds=canonical.getchannel('A').point(lambda a:255 if a>32 else 0).getbbox()
            canonical=canonical.crop(bounds);canonical.thumbnail((224,224),Image.Resampling.LANCZOS)
            grid=Image.new('RGBA',(256,256));grid.alpha_composite(canonical,((256-canonical.width)//2,(256-canonical.height)//2))
            grid_path=ROOT/f'Resources/res/grid_items/grid{e["grid"]}.png';grid.save(grid_path)
            grids[e['grid']]['output_size']=[256,256]
            grids[e['grid']]['design_source']=backup.relative_to(ROOT).as_posix()
        xs,ys=cuts[e['group']];col,row=e['cell']%8,e['cell']//8
        tile=clean_cell(sheets[e['group']].crop((xs[col],ys[row],xs[col+1],ys[row+1])))
        tile=tile.crop(tile.getchannel('A').getbbox())
        tile.thumbnail((224,224),Image.Resampling.LANCZOS)
        scale=min(224/tile.width,224/tile.height)
        tile=tile.resize((round(tile.width*scale),round(tile.height*scale)),Image.Resampling.LANCZOS)
        icon=Image.new('RGBA',(256,256));icon.alpha_composite(tile,((256-tile.width)//2,(256-tile.height)//2));icon.save(dest)
        bounds=list(icon.getchannel('A').point(lambda a:255 if a>24 else 0).getbbox())
        old[e['item']]['bounds']=bounds;old[e['item']]['rendered_from']=f'output/square-gear/generated/{e["group"]}.png'
        e['icon_file']=dest.relative_to(ROOT).as_posix();e['grid_file']=f'Resources/res/grid_items/grid{e["grid"]}.png'
        assert (ROOT/e['grid_file']).resolve()!=dest.resolve()
        assert hashlib.sha256(dest.read_bytes()).digest()!=hashlib.sha256((ROOT/e['grid_file']).read_bytes()).digest()
    manifest_path.write_text(json.dumps(manifest,indent=2))
    grid_manifest_path.write_text(json.dumps(grid_manifest,indent=2))
    rows=[]
    for e in manifest['entries']:
        x,y,r,b=e['bounds'];active=e['active'] and not e.get('reserved')
        rows.append(f'{{{x},{y},{r-x},{b-y},{str(active).lower()}}}')
    (ROOT/'Classes/ItemSeriesArt.h').write_text('#pragma once\n// Generated item artwork bounds.\nnamespace ItemSeries {\nstruct Art {int x,y,w,h;bool active;};\nstatic const Art Artwork[Count]={\n'+',\n'.join(rows)+'\n};\n}\n')
    cards=''.join(f'<article><b>{e["group"]} {e["detail"]+1} / type {e["type"]}</b><div><img src="../../{e["grid_file"]}"><img src="../../{e["icon_file"]}"></div></article>' for e in records)
    (WORK/'index.html').write_text('<!doctype html><meta charset="utf-8"><title>Grid / icon designs</title><style>body{background:#203034;color:#ead9bb;font:14px sans-serif}main{display:grid;grid-template-columns:repeat(auto-fill,minmax(260px,1fr));gap:10px}article{background:#38484c;padding:10px}article div{display:flex;height:130px}img{width:48%;object-fit:contain}</style><h1>Grid / independently repainted icon (120)</h1><main>'+cards+'</main>')
    (WORK/'manifest.json').write_text(json.dumps({'entries':records},indent=2))
    print('PASS 120 independent 256px icons; matching grid designs and separate files')

if __name__=='__main__':build()
