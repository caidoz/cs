"""Prepare AI-edit atlases and package them without changing runtime silhouettes."""
from pathlib import Path
import argparse
import hashlib
import html
import json
import math
import shutil
from collections import deque
import numpy as np
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
WORK = ROOT / 'asset_library/work/equipment-retouch-20261123'
CATALOG = ROOT / 'content/runtime-assets.json'


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def prepare():
    assets = {a['target']: a for a in json.loads(CATALOG.read_text())['assets']}
    entries = json.loads((ROOT / 'asset_library/reference/Resources/res/grid_items/manifest.json').read_text())['entries']
    for folder in ('source', 'before', 'generated', 'final', 'review'):
        (WORK / folder).mkdir(parents=True, exist_ok=True)
    groups = {}
    records = []
    for e in entries:
        name = f'grid_items-grid{e["id"]}.png'
        a = assets['res/' + name]
        master = a.get('original_source', a['source'])
        original = ROOT / a['source']
        before = WORK / 'before' / name
        if not before.exists():
            Image.open(original).convert('RGBA').save(before)
        im = Image.open(before).convert('RGBA')
        bbox = im.getchannel('A').getbbox()
        r = dict(id=e['id'], group=e['group'], type=e['type'], detail=e['detail'],
                 target=a['target'], master=master, size=list(im.size), bbox=list(bbox),
                 before_sha256=digest(before))
        records.append(r)
        groups.setdefault(e['group'], []).append(r)
    a = assets['res/castle_cannon_v2-atlas.png']
    cannon = Image.open(ROOT / a['source']).convert('RGBA')
    backup = WORK / 'before' / 'castle_cannon_v2-atlas.png'
    if not backup.exists():
        cannon.save(backup)
    cannon = Image.open(backup).convert('RGBA')
    for n in range(60):
        rect = [n % 6 * 384, n // 6 * 256, n % 6 * 384 + 384, n // 6 * 256 + 256]
        im = cannon.crop(rect)
        name = f'cannon-frame{n:02}.png'
        before = WORK / 'before' / name
        if not before.exists():
            im.save(before)
        group = 'cannon-a' if n < 30 else 'cannon-b'
        r = dict(id=225+n, group=group, type='cannon', detail=n, target='res/'+name,
                 runtime_target=a['target'], master=a.get('original_source', a['source']),
                 source_rect=rect, size=list(im.size), bbox=list(im.getchannel('A').getbbox()),
                 before_sha256=digest(before))
        records.append(r)
        groups.setdefault(group, []).append(r)
    for name, items in groups.items():
        cols = 7 if len(items) == 35 else 6 if name.startswith('cannon') else 8
        rows = math.ceil(len(items) / cols)
        cell = 192
        sheet = Image.new('RGBA', (cols * cell, rows * cell))
        for n, r in enumerate(items):
            im = Image.open(WORK / 'before' / Path(r['target']).name).convert('RGBA')
            cropped = im.crop(r['bbox'])
            scale = min(158 / cropped.width, 158 / cropped.height)
            size = (round(cropped.width * scale), round(cropped.height * scale))
            cropped = cropped.resize(size, Image.Resampling.NEAREST)
            x, y = n % cols * cell + (cell - size[0]) // 2, n // cols * cell + (cell - size[1]) // 2
            sheet.alpha_composite(cropped, (x, y))
            r.update(cell=n, atlas_rect=[x, y, x + size[0], y + size[1]], sheet_size=list(sheet.size))
        sheet.save(WORK / 'source' / f'{name}.png')
    (WORK / 'catalog.json').write_text(json.dumps(dict(entries=records, groups={k:len(v) for k,v in groups.items()}), indent=2))
    print(f'Prepared {len(records)} assets in {len(groups)} edit atlases: { {k:len(v) for k,v in groups.items()} }')


def foreground(tile):
    """Read the painted object, excluding faint matte and detached atlas specks."""
    pixels = np.array(tile)
    active = pixels[:, :, 3] > 128
    seen = np.zeros_like(active)
    components = []
    height, width = active.shape
    for y, x in zip(*np.nonzero(active)):
        if seen[y, x]:
            continue
        stack = [(int(y), int(x))]
        seen[y, x] = True
        component = []
        while stack:
            py, px = stack.pop()
            component.append((py, px))
            for ny, nx in ((py-1, px), (py+1, px), (py, px-1), (py, px+1)):
                if 0 <= ny < height and 0 <= nx < width and active[ny, nx] and not seen[ny, nx]:
                    seen[ny, nx] = True
                    stack.append((ny, nx))
        components.append(component)
    if not components:
        raise ValueError('Empty generated sprite')
    cutoff = max(5, max(map(len, components)) * .015)
    keep = np.zeros_like(active)
    for component in components:
        if len(component) >= cutoff:
            ys, xs = zip(*component)
            keep[ys, xs] = True
    pixels[~keep] = 0
    result = Image.fromarray(pixels)
    return result.crop(result.getchannel('A').getbbox())


def restore_canvas(original, painted):
    """Uniformly fit AI paint; restore exact original canvas, alpha and cutouts.

    RGB edge bleed is a packaging operation: it supplies the nearest painted
    color where the AI outline differs, before applying the original alpha.
    No new artwork, geometry, material, pivots or occupancy data is synthesized.
    """
    bbox = original.getchannel('A').getbbox()
    width, height = bbox[2] - bbox[0], bbox[3] - bbox[1]
    scale = min(width / painted.width, height / painted.height)
    size = (max(1, round(painted.width * scale)), max(1, round(painted.height * scale)))
    painted = painted.resize(size, Image.Resampling.NEAREST)
    layer = Image.new('RGBA', original.size)
    layer.paste(painted, (bbox[0] + (width-size[0])//2, bbox[1] + (height-size[1])//2))
    p = np.array(layer)
    src = np.array(original)
    support = src[:, :, 3] > 128
    valid = p[:, :, 3] > 128
    coverage = float((valid & support).sum() / max(1, support.sum()))
    # Breadth-first nearest-neighbor bleed keeps narrow source tips covered.
    queue = deque()
    for y, x in zip(*np.nonzero(valid)):
        if ((y > 0 and not valid[y-1,x]) or (y+1 < valid.shape[0] and not valid[y+1,x]) or
            (x > 0 and not valid[y,x-1]) or (x+1 < valid.shape[1] and not valid[y,x+1])):
            queue.append((int(y), int(x)))
    while queue:
        y, x = queue.popleft()
        for ny, nx in ((y-1,x), (y+1,x), (y,x-1), (y,x+1)):
            if 0 <= ny < valid.shape[0] and 0 <= nx < valid.shape[1] and not valid[ny,nx]:
                p[ny,nx,:3] = p[y,x,:3]
                valid[ny,nx] = True
                queue.append((ny,nx))
    p[:, :, 3] = src[:, :, 3]
    p[p[:, :, 3] == 0, :3] = 0
    return Image.fromarray(p), coverage


def package():
    catalog = json.loads((WORK / 'catalog.json').read_text())
    sheets = {g: Image.open(WORK / 'generated' / f'{g}.png').convert('RGBA') for g in catalog['groups']}
    report = []
    for r in catalog['entries']:
        name = Path(r['target']).name
        original = Image.open(WORK / 'before' / name).convert('RGBA')
        sheet = sheets[r['group']]
        cols = 7 if catalog['groups'][r['group']] == 35 else 6 if r['group'].startswith('cannon') else 8
        rows = math.ceil(catalog['groups'][r['group']] / cols)
        col, row = r['cell'] % cols, r['cell'] // cols
        rect = (round(col*sheet.width/cols), round(row*sheet.height/rows),
                round((col+1)*sheet.width/cols), round((row+1)*sheet.height/rows))
        painted = foreground(sheet.crop(rect))
        final, coverage = restore_canvas(original, painted)
        assert final.size == original.size
        assert final.getchannel('A').tobytes() == original.getchannel('A').tobytes()
        if coverage < .70:
            raise ValueError(f'{name}: painted/source overlap is only {coverage:.1%}; review alignment')
        changed = int(np.any(np.array(final)[:, :, :3] != np.array(original)[:, :, :3], axis=2)[np.array(original)[:, :, 3] > 128].sum())
        final.save(WORK / 'final' / name)
        report.append(dict(id=r['id'], target=r['target'], coverage=round(coverage, 4),
                           changed_opaque_pixels=changed, size_preserved=True, alpha_exact=True))
    cannon = Image.open(WORK / 'before' / 'castle_cannon_v2-atlas.png').convert('RGBA')
    for r in catalog['entries']:
        if r['type'] == 'cannon':
            final = Image.open(WORK / 'final' / Path(r['target']).name)
            cannon.paste(final, tuple(r['source_rect'][:2]))
    cannon.save(WORK / 'final' / 'castle_cannon_v2-atlas.png')
    (WORK / 'validation.json').write_text(json.dumps(dict(count=len(report), assets=report), indent=2))
    review(catalog)
    print(f'PACKAGED {len(report)} retouches; exact original dimensions, alpha and silhouettes; minimum paint overlap {min(r["coverage"] for r in report):.1%}')


def review(catalog):
    for group in catalog['groups']:
        items = [r for r in catalog['entries'] if r['group'] == group]
        cols = 4
        sheet = Image.new('RGB', (cols*300, math.ceil(len(items)/cols)*190), '#292930')
        draw = ImageDraw.Draw(sheet)
        for n, r in enumerate(items):
            x, y = n%cols*300, n//cols*190
            name = Path(r['target']).name
            draw.text((x+8,y+5), f'{r["id"]} / {r["group"]} {r["detail"]+1}  BEFORE / AFTER', fill='white')
            for offset, folder in ((0, 'before'), (150, 'final')):
                im = Image.open(WORK / folder / name).convert('RGBA')
                im.thumbnail((142,158),Image.Resampling.NEAREST)
                sheet.paste(im, (x+offset+(150-im.width)//2,y+24+(158-im.height)//2), im)
        sheet.save(WORK / 'review' / f'{group}.png')
    cards = []
    for r in catalog['entries']:
        name = Path(r['target']).name
        label = html.escape(f'{r["group"]} {r["detail"]+1} / {r["id"]}')
        cards.append(f'<article><b>{label}</b><div><figure><img src="../before/{name}"><figcaption>BEFORE</figcaption></figure><figure><img src="../final/{name}"><figcaption>AFTER</figcaption></figure></div></article>')
    page = '<!doctype html><meta charset="utf-8"><title>Character-tone equipment retouch</title><style>body{background:#292930;color:#eee5d6;font:14px sans-serif;margin:24px}main{display:grid;grid-template-columns:repeat(auto-fill,minmax(280px,1fr));gap:12px}article{background:#33333e;padding:12px}article div{display:flex}figure{width:50%;margin:8px 0;text-align:center}img{width:130px;height:170px;object-fit:contain;image-rendering:pixelated}figcaption{font-size:12px;color:#b9b5ad}a{color:#c0d8fa}</style><h1>Equipment retouch / 285 variants</h1><p>c0-c122 character references. Original canvas, exact alpha, silhouette, footprint and pivots preserved. Built-in image generation edits; atlas prompts are in ../generated/.</p><p><a href="../validation.json">Asset validation</a> / <a href="../runtime-validation.json">Native runtime validation</a></p><main>'+''.join(cards)+'</main>'
    (WORK / 'review' / 'index.html').write_text(page, encoding='utf-8')


def apply():
    catalog = json.loads((WORK / 'catalog.json').read_text())
    validate(final=True)
    done = set()
    for r in catalog['entries']:
        target = r.get('runtime_target', r['target'])
        if target in done:
            continue
        done.add(target)
        final = WORK / 'final' / Path(target).name
        dest = ROOT / r['master']
        shutil.copy2(final, dest)
    print(f'Updated {len(done)} existing approved library masters. Run optimize_images.py --apply, then runtime_assets.py stage.')


def validate(final=False):
    catalog = json.loads((WORK / 'catalog.json').read_text())
    current = {a['target']:a for a in json.loads(CATALOG.read_text())['assets']}
    for r in catalog['entries']:
        name = Path(r['target']).name
        before = Image.open(WORK / 'before' / name).convert('RGBA')
        if final:
            image = Image.open(WORK / 'final' / name).convert('RGBA')
        else:
            target = r.get('runtime_target', r['target'])
            image = Image.open(ROOT / current[target]['source']).convert('RGBA')
            if r['type'] == 'cannon':
                image = image.crop(r['source_rect'])
        assert image.size == before.size, name
        assert image.getchannel('A').tobytes() == before.getchannel('A').tobytes(), name
        assert image.tobytes() != before.tobytes(), f'Unchanged: {name}'
    print(f'PASS {len(catalog["entries"])} changed assets: canvas dimensions and exact alpha unchanged; footprint, cutouts and aspect ratios preserved')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=['prepare', 'package', 'apply', 'validate', 'review'])
    args = parser.parse_args()
    if args.command == 'review':
        review(json.loads((WORK / 'catalog.json').read_text()))
    else:
        globals()[args.command]()
