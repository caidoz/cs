"""Promote only the final portrait assets referenced by the native renderer."""
from pathlib import Path
import json
import shutil
import subprocess
import sys

ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'asset_library/work/portrait-redesign-implementation'
generated=Path('C:/Users/polyp/.codex/generated_images/01a207f5-96b6-74a1-b712-379018a739b4')
icons=WORK/'final/portrait-icons.png'
shutil.copy2(generated/'exec-a9593bd4-df21-4f1e-abf5-bed21b89ba59.png',WORK/'source/exec-a9593bd4-df21-4f1e-abf5-bed21b89ba59.png')
shutil.copy2(WORK/'source/exec-a9593bd4-df21-4f1e-abf5-bed21b89ba59.png',icons)
files=sorted((WORK/'final').glob('portrait-ui-*.png'))+[WORK/'final/portrait-night.png',icons]
files+=sorted((WORK/'smooth-review-v2/art').glob('*.png'))
known={a['target']:a for a in json.loads((ROOT/'content/runtime-assets.json').read_text())['assets']}
for p in files:
    # Selected integrated hulls supersede the legacy tiled-foundation reviews.
    integrated=ROOT/'asset_library/work/castle-integrated-chassis/final'/p.name
    if integrated.is_file():p=integrated
    starter=ROOT/'asset_library/work/castle-front-cannon-tone-sync/starter-production-final'/p.name
    if p.name in {'portrait-castle-01.png','portrait-wheel-01.png','portrait-turret-01.png'} and starter.is_file():p=starter
    all_castles=ROOT/'asset_library/work/all-castles-matte-20261125/selected-final'/p.name
    if all_castles.is_file():p=all_castles
    target='res/'+p.name
    if target in known:
        master=ROOT/known[target].get('original_source',known[target]['source'])
        if p.read_bytes()!=master.read_bytes():shutil.copy2(p,master)
        continue
    subprocess.run([sys.executable,str(ROOT/'tools/assets/runtime_assets.py'),'add',str(p),'--name',p.name],check=True)
print(f'Promoted {len(files)} directly referenced final assets',flush=True)
