"""Validate the two-state mimic asset and native discard interactions."""
import importlib.util
from pathlib import Path
from PIL import Image

root=Path(__file__).resolve().parents[2]
with Image.open(root/'Resources/res/roulette-mimic-discard-v1.png') as im:
    assert im.mode=='RGBA' and im.getchannel('A').getextrema()==(0,255)
    w,h=im.width//2,im.height
    closed=im.crop((0,0,w,h));opened=im.crop((w,0,2*w,h))
    assert closed.tobytes()!=opened.tobytes()
    assert abs(closed.getbbox()[3]-opened.getbbox()[3])<=h*.03
print('PASS transparent idle/open mimic frames and aligned baseline',flush=True)
spec=importlib.util.spec_from_file_location('runtime',root/'tools/items/verify_runtime.py')
runtime=importlib.util.module_from_spec(spec);spec.loader.exec_module(runtime)
runtime.EXE=root/'proj.win32/Debug.win32/cs.mimic-discard.exe'
for height in (850,1408):
    folder=f'mimic-discard-{height}'
    runtime.run(height,{'CS_ROULETTE_TRASH_REVIEW':'1'},folder,'DONE roulette trash review',3)
    log=(root/'output/item-series/runtime'/folder/'checks.log').read_text()
    assert log.count('PASS trash opens its mouth near dragged item')==3,log
    assert log.count('PASS drag result to trash removes exactly one with no extra charge')==3,log
    assert 'PASS resolving final result starts the normal enemy turn' in log,log
    print(f'PASS {height}: mouth proximity, exactly one discard, unchanged cost and normal turn progression',flush=True)
