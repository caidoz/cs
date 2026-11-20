"""Review existing-art backgrounds, clipping and full-screen castle upgrades."""
import os
import argparse
from pathlib import Path
import subprocess
import time
from PIL import Image

root=Path(__file__).resolve().parents[2]
parser=argparse.ArgumentParser()
parser.add_argument('--exe',default='cs.menu-scenes.exe')
args=parser.parse_args()
fingerprints=[]
for c in range(1,11):
    with Image.open(root/f'Resources/res/castle_four_rooms_v5-rooms-{c:02d}.png') as im:
        fingerprints.append(im.crop((im.width//2,0,im.width*3//4,im.height//6)).tobytes())
assert len(set(fingerprints))==10
print('PASS ten distinct native pixel backgrounds without newly generated artwork',flush=True)
for height in (850,1408):
    out=root/f'output/menu-scenes-{height}'
    out.mkdir(parents=True,exist_ok=True)
    trace=out/'phases.log'
    trace.write_text('')
    env=dict(os.environ,CS_MENU_SCENES_REVIEW='1',CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',
             CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(height))
    startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
    with (out/'stdout.log').open('w') as log:
        process=subprocess.Popen([str(root/'proj.win32/Debug.win32'/args.exe)],cwd=root/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
        try:
            deadline=time.monotonic()+60
            while time.monotonic()<deadline:
                result=trace.read_text()
                if 'FAIL' in result:raise RuntimeError(result)
                if 'DONE menu scenes review' in result:
                    assert result.count('PASS menu scene capture')==10,result
                    assert 'PASS full-screen castle has no dock touch targets' in result,result
                    print(f'PASS {height}: ten native menu captures and no castle dock',flush=True)
                    break
                if process.poll() is not None:raise RuntimeError(f'Exited {process.returncode}')
                time.sleep(.1)
            else:raise RuntimeError('Scene review timed out')
        finally:
            if process.poll() is None:process.terminate()
            process.wait(timeout=5)
