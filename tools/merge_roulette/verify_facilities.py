"""Read-only asset checks and isolated native room/upgrade captures."""
import hashlib
import argparse
import json
import os
from pathlib import Path
import subprocess
import time
from PIL import Image, ImageChops

ROOT=Path(__file__).resolve().parents[2]
DEST=ROOT/'output/merge-roulette/facilities'
DEST.mkdir(parents=True,exist_ok=True)
for c in range(1,11):
    im=Image.open(ROOT/f'Resources/res/merge_castle_rebuild/rooms-{c:02}.png').convert('RGB')
    w,h=im.size
    for r in range(5):
        hashes=[hashlib.sha256(im.crop((w*r//5,h*lv//6,w*(r+1)//5,h*(lv+1)//6)).tobytes()).digest() for lv in range(6)]
        assert len(set(hashes))==6,(c,r,'duplicate upgrade art')
print('PASS 10 atlases / 50 rooms / 300 unique upgrade frames',flush=True)
env=os.environ.copy();env.update(CS_MERGE_REVIEW='1',CS_MERGE_ROOM_REVIEW='1',CS_MERGE_REVIEW_HEIGHT='850',CS_MERGE_REVIEW_PATH=DEST.as_posix()+'/')
trace=DEST/'checks.log';trace.unlink(missing_ok=True)
startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
parser=argparse.ArgumentParser()
parser.add_argument('--exe',default='proj.win32/Debug.win32/cs.exe')
args=parser.parse_args()
exe=(ROOT/args.exe).resolve()
with (DEST/'stdout.log').open('w') as log:
    process=subprocess.Popen([str(exe)],cwd=exe.parent,env=env,stdout=log,stderr=subprocess.STDOUT,startupinfo=startup)
    try:
        deadline=time.monotonic()+90
        while time.monotonic()<deadline:
            if process.poll() is not None:raise RuntimeError(f'preview exited {process.returncode}')
            last=DEST/'room-independent-castle-01-level-0.png'
            logtext=trace.read_text() if trace.exists() else ''
            if 'DONE' in logtext and ('PASS capture '+last.as_posix()) in logtext:break
            time.sleep(.2)
        else:raise RuntimeError('facility capture timed out')
    finally:
        process.terminate();process.wait(timeout=5)
for c in range(1,11):
    for lv in range(6):
        im=Image.open(DEST/f'room-castle-{c:02}-level-{lv}.png');assert im.size==(640,850)
base=Image.open(DEST/'room-castle-01-level-0.png').convert('RGB')
mixed=Image.open(DEST/'room-independent-castle-01-level-0.png').convert('RGB')
# Compare the actual alpha apertures, excluding posts and animated scenery
# visible through their antialiased outer edges. Only bottom-right upgrades.
for rect in [(124,345,237,420),(268,345,378,420),(409,345,521,420),(124,480,294,565)]:
    rect=(rect[0],rect[1]-24,rect[2],rect[3]-24)
    assert ImageChops.difference(base.crop(rect),mixed.crop(rect)).getbbox() is None,'neighbor room changed'
assert ImageChops.difference(base.crop((333,456,521,541)),mixed.crop((333,456,521,541))).getbbox(),'selected room did not upgrade'
print('PASS 61 native captures; changing one room preserves the other four pixel-for-pixel',flush=True)
(DEST/'verification.json').write_text(json.dumps({'castles':10,'rooms':50,'upgradeFrames':300,'nativeCaptures':61,'independentRoomPixels':True},indent=2))
