"""Register new illustrated background layers; no repainting or color filter.

Only canvas sizing and bridge deck registration for the existing parallax engine.
"""
from pathlib import Path
import json
import numpy as np
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
DEST=ROOT/'Resources/res/stage_mist_v3'
manifest=[]
for region in range(1,16):
    for layer in ('far','mid','rail'):
        name=f'region-{region:02}-{layer}.png'
        source=Image.open(DEST/'source'/name).convert('RGBA')
        size=(1088,438) if layer=='rail' else (1088,1445)
        image=source.resize(size,Image.Resampling.NEAREST)
        offset=0
        if layer=='far':
            # Authored sky is already opaque and graded; do not alter its colors.
            image=image.convert('RGB')
        elif layer=='rail':
            # Topmost continuous rail is the native engine's deck at y=28.
            alpha=np.asarray(image)[:,:,3]
            rows=np.flatnonzero((alpha>192).mean(axis=1)>.88)
            assert len(rows),f'No continuous bridge deck: {name}'
            offset=28-int(rows[0])
            registered=Image.new('RGBA',size)
            registered.alpha_composite(image,(0,offset))
            image=registered
        else:
            alpha=np.asarray(image)[:,:,3]
            assert (alpha==0).mean()>.3,f'Middle layer blocks sky: {name}'
        image.save(DEST/name)
        manifest.append(dict(region=region,layer=layer,size=size,
            source=f'source/{name}',deckShift=offset))
(DEST/'manifest.json').write_text(json.dumps(manifest,indent=2))
(ROOT/'Classes/StageMistNames.inc').write_text(''.join(
    f'\t"stage_mist_v3/region-{r:02}-{l}",\n' for r in range(1,16) for l in ('far','mid','rail')))
print('PASS 45 new background PNGs: far/middle 1088x1445, bridge 1088x438, deck y=28')
