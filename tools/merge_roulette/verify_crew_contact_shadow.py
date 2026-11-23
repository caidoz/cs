"""Verify visible foot shadow and bottom-left body placement from native pixels."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import json
from pathlib import Path
import re
import sys
import numpy as np
from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'items'))
import verify_runtime as runtime

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--exe', default='cs.exe')
args = parser.parse_args()
runtime.EXE = runtime.ROOT / 'proj.win32/Debug.win32' / args.exe
layers = {'full': {}, 'no-shadow': {'CS_CREW_SHADOW_HIDE_REVIEW': '1'},
          'no-body': {'CS_CREW_BODY_HIDE_REVIEW': '1'},
          'tile-only': {'CS_CREW_SHADOW_HIDE_REVIEW': '1', 'CS_CREW_BODY_HIDE_REVIEW': '1'}}
def capture(case):
    height, name = case
    runtime.run(height, {'CS_GRID_CREW_ROTATION_REVIEW': '1', **layers[name]},
                f'contact-shadow-{height}-{name}', 'DONE grid crew rotation review', 2)
with ThreadPoolExecutor(max_workers=2) as pool:
    list(pool.map(capture, [(h,n) for h in (850,1408) for n in layers]))
for height in (850,1408):
    folder = runtime.ROOT / 'output/item-series/runtime' / f'contact-shadow-{height}-full'
    trace = (folder / 'checks.log').read_text()
    x, top, w, h = map(int,re.search(r'CONTACT_TILE (\d+) (\d+) (\d+) (\d+)',trace).groups())
    images = {}
    for name in layers:
        path = runtime.ROOT / 'output/item-series/runtime' / f'contact-shadow-{height}-{name}' / 'crew-horizontal.png'
        with Image.open(path) as image:
            images[name] = np.asarray(image.convert('RGB').crop((x,height-top,x+w,height-top+h))).astype(int)
    def bounds(mask):
        yy,xx=np.where(mask)
        assert len(xx)>0, 'No changed pixels found'
        return [int(xx.min()),int(yy.min()),int(xx.max())+1,int(yy.max())+1]
    visible_shadow = np.max(np.abs(images['full']-images['no-shadow']),axis=2)>5
    body = np.max(np.abs(images['no-shadow']-images['tile-only']),axis=2)>5
    shadow_bounds,body_bounds=bounds(visible_shadow),bounds(body)
    assert visible_shadow.sum()>=30, ('Shadow hidden behind body',visible_shadow.sum())
    assert shadow_bounds[0]<w*.25 and shadow_bounds[2]<w*.5, shadow_bounds
    assert shadow_bounds[3]>=h-5, ('Shadow not on tile floor',shadow_bounds,h)
    assert body_bounds[0]<=10 and h-body_bounds[3]<=8, ('Body not bottom-left',body_bounds,h)
    assert shadow_bounds[2]>body_bounds[0] and shadow_bounds[1]<=body_bounds[3]+3, 'Shadow detached from feet'
    metrics={'visible_shadow_pixels':int(visible_shadow.sum()),'shadow_bounds':shadow_bounds,'body_bounds':body_bounds,'tile_size':[w,h]}
    (folder/'contact-pixels.json').write_text(json.dumps(metrics,indent=2))
    print(f'PASS {height}: visible shadow and bottom-left foot contact {metrics}',flush=True)
