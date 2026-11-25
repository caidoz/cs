"""Exercise artillery themes using real rendering and damage timelines."""
import os
import argparse
from pathlib import Path
import subprocess
import time
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
parser=argparse.ArgumentParser()
parser.add_argument('--exe',default='cs_bars.exe')
parser.add_argument('--level',type=int,choices=range(6))
parser.add_argument('--count',type=int,choices=range(1,20),default=10)
options=parser.parse_args()
for height in (850, 1408):
    dest = ROOT / ('output/turret-attack-review' if options.level is None else f'output/turret-upgrade-fx/lv-{options.level}') / str(height)
    dest.mkdir(parents=True, exist_ok=True)
    trace = dest / 'checks.log'
    trace.unlink(missing_ok=True)
    env = os.environ.copy()
    env.update(CS_MERGE_REVIEW='1', CS_MERGE_TURRET_REVIEW='1',
               CS_MERGE_REVIEW_HEIGHT=str(height), CS_MERGE_REVIEW_PATH=dest.as_posix() + '/')
    if options.level is not None:env['CS_TURRET_REVIEW_LEVEL']=str(options.level)
    env['CS_TURRET_REVIEW_COUNT']=str(options.count)
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest / 'stdout.log').open('w') as log:
        process = subprocess.Popen([str(ROOT / 'proj.win32/Debug.win32'/options.exe)],
                                   cwd=ROOT / 'Resources', env=env, startupinfo=startup,
                                   stdout=log, stderr=log)
        try:
            deadline = time.monotonic() + 150
            while time.monotonic() < deadline:
                text = trace.read_text() if trace.exists() else ''
                if 'FAIL' in text:
                    raise RuntimeError(text)
                if 'DONE turret attack review' in text:
                    assert text.count('PASS turret native type muzzle and burst') == options.count
                    assert text.count('PASS turret damage commits exactly once') == options.count
                    assert text.count('PASS capture ') == options.count*4
                    for castle in range(1, options.count+1):
                        for phase in ('prepare', 'launch', 'flight', 'impact'):
                            with Image.open(dest / f'turret-{castle:02}-{phase}.png') as image:
                                image.verify()
                    print(f'PASS 640x{height}: {options.count} turret types, burst timing, damage, and {options.count*4} captures', flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError('preview exited')
                time.sleep(.2)
            else:
                raise RuntimeError('turret review timeout')
        finally:
            if process.poll() is None:
                process.terminate()
            try:process.wait(timeout=5)
            except subprocess.TimeoutExpired:
                process.kill();process.wait(timeout=10)
