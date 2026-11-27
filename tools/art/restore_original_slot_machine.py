"""Restore the original slot/gear PNG masters byte-for-byte under flat runtime IDs."""
from pathlib import Path
import hashlib
import json
import shutil

root=Path(__file__).resolve().parents[2]
work=root/'asset_library/work/original-slot-machine-restore'
final=work/'final'
final.mkdir(parents=True,exist_ok=True)
assets=json.loads((root/'content/runtime-assets.json').read_text(encoding='utf-8'))['assets']
report=[]
for original,name in [('ui-slot.png','portrait-ui-05.png'),('ui-gear.png','portrait-roulette-gear.png')]:
    source=root/'asset_library/reference/Resources/res/merge_castle_rebuild'/original
    selected=final/name
    shutil.copy2(source,selected)
    record=next(a for a in assets if a['target']=='res/'+name)
    master=root/record.get('original_source',record['source'])
    shutil.copy2(selected,master)
    assert source.read_bytes()==selected.read_bytes()==master.read_bytes()
    report.append({'original':source.relative_to(root).as_posix(),'selected':selected.relative_to(root).as_posix(),
                   'runtime':record['target'],'sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
                   'restoration':'Original PNG bytes; no recoloring, redrawing, cropping or resampling'})
(work/'restoration.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print('Restored original housing and golden gear masters exactly')
