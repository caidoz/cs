"""Validate every grid sprite and exercise live board, rotation and icon routes."""
from pathlib import Path
import hashlib
import importlib.util
import json
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]

def validate():
    entries=json.loads((ROOT/'Resources/res/grid_items-manifest.json').read_text())['entries']
    assert len(entries)==225
    for e in entries:
        assert hashlib.sha256((ROOT/e['source']).read_bytes()).hexdigest()==e['source_sha256'], e['source']
        with Image.open(ROOT/e['file']) as image:
            assert image.mode=='RGBA' and image.size==tuple(e['output_size'])
            if e.get('design_source'):assert image.size==(256,256)
            else:assert image.width*e['size'][1]==image.height*e['size'][0]
            alpha=image.getchannel('A')
            low,high=alpha.getextrema()
            assert low==0 and high>=240
            bbox=alpha.getbbox()
            assert bbox and 0<=bbox[0]<bbox[2]<=image.width and 0<=bbox[1]<bbox[3]<=image.height, e['file']
            assert alpha.getpixel((0,0))==0 and alpha.getpixel((image.width-1,image.height-1))==0, e['file']
    print('PASS all 225 grid files: alpha, canvas ratio, gutters and unchanged actor sources',flush=True)

if __name__=='__main__':
    validate()
    spec=importlib.util.spec_from_file_location('runtime',ROOT/'tools/items/verify_runtime.py')
    runtime=importlib.util.module_from_spec(spec);spec.loader.exec_module(runtime)
    runtime.EXE=ROOT/'proj.win32/Debug.win32/cs_grid_items.exe'
    runtime.run(850,{'CS_GRID_ITEM_REVIEW':'1'},'grid-catalog','DONE grid item review',8)
    runtime.run(850,{'CS_ITEM_SERIES_REVIEW':'1'},'grid-icon-regression','DONE item series review',10)
    for height in (850,1408):
        runtime.run(height,{'CS_MIST_RESOURCE_REVIEW':'1'},f'grid-scene-{height}','DONE mist resource review',35)
