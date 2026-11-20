"""Capture ten simple equipment-hero backgrounds at two viewport heights."""
import os
import argparse
from pathlib import Path
import subprocess
import time
from PIL import Image

root=Path(__file__).resolve().parents[2]
parser=argparse.ArgumentParser()
parser.add_argument('--exe',default='cs.hero-backgrounds.exe')
parser.add_argument('--debug',action='store_true')
args=parser.parse_args()
tiles=[]
for i in range(1,11):
    with Image.open(root/f'Resources/res/menu_renewal-dressing-v3-castle-{i:02d}.png') as im:
        assert 1.9 < im.width/im.height < 2.1
        tiles.append(im.tobytes())
assert len(set(tiles))==10
print('PASS ten distinct background paintings',flush=True)
for height in (850,1408):
    out=root/f'output/hero-backgrounds-{"debug-" if args.debug else ""}{height}'
    out.mkdir(parents=True,exist_ok=True)
    trace=out/'phases.log';trace.write_text('')
    env=dict(os.environ,CS_HERO_BACKGROUND_REVIEW='1',CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',
             CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(height))
    if args.debug:env['CS_HERO_BACKGROUND_DEBUG_REVIEW']='1'
    startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
    with (out/'stdout.log').open('w') as log:
        process=subprocess.Popen([str(root/'proj.win32/Debug.win32'/args.exe)],cwd=root/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
        try:
            deadline=time.monotonic()+60
            while time.monotonic()<deadline:
                result=trace.read_text()
                if 'FAIL' in result:raise RuntimeError(result)
                if 'DONE hero background review' in result:
                    assert result.count('PASS hero background capture')==10,result
                    assert result.count('PASS hero background follows displayed castle')==10,result
                    for i in range(1,11):
                        with Image.open(out/f'hero-castle-{i:02d}.png') as shot:assert shot.size==(640,height)
                    print(f'PASS {height}: ten actual equipment-screen captures',flush=True)
                    break
                if process.poll() is not None:raise RuntimeError(f'Exited {process.returncode}')
                time.sleep(.1)
            else:raise RuntimeError('Hero background review timed out')
        finally:
            if process.poll() is None:process.terminate()
            process.wait(timeout=5)
