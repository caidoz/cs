"""Capture ten simple equipment-hero backgrounds at two viewport heights."""
import os
from pathlib import Path
import subprocess
import time
from PIL import Image

root=Path(__file__).resolve().parents[2]
with Image.open(root/'Resources/res/menu_renewal/hero-castle-backgrounds-v2.png') as im:
    w,h=im.width//2,im.height//5
    tiles=[im.crop((i%2*w,i//2*h,(i%2+1)*w,(i//2+1)*h)).tobytes() for i in range(10)]
    assert len(set(tiles))==10
print('PASS ten distinct background paintings',flush=True)
for height in (850,1408):
    out=root/f'output/hero-backgrounds-{height}'
    out.mkdir(parents=True,exist_ok=True)
    trace=out/'phases.log';trace.write_text('')
    env=dict(os.environ,CS_HERO_BACKGROUND_REVIEW='1',CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',
             CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(height))
    startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
    with (out/'stdout.log').open('w') as log:
        process=subprocess.Popen([str(root/'proj.win32/Debug.win32/cs.hero-backgrounds.exe')],cwd=root/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
        try:
            deadline=time.monotonic()+60
            while time.monotonic()<deadline:
                result=trace.read_text()
                if 'FAIL' in result:raise RuntimeError(result)
                if 'DONE hero background review' in result:
                    assert result.count('PASS hero background capture')==10,result
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
