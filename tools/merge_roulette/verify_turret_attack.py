"""Exercise all ten artillery themes using real rendering and damage timelines."""
import os
from pathlib import Path
import subprocess
import time
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
for height in (850, 1408):
    dest = ROOT / 'output/turret-attack-review' / str(height)
    dest.mkdir(parents=True, exist_ok=True)
    trace = dest / 'checks.log'
    trace.unlink(missing_ok=True)
    env = os.environ.copy()
    env.update(CS_MERGE_REVIEW='1', CS_MERGE_TURRET_REVIEW='1',
               CS_MERGE_REVIEW_HEIGHT=str(height), CS_MERGE_REVIEW_PATH=dest.as_posix() + '/')
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest / 'stdout.log').open('w') as log:
        process = subprocess.Popen([str(ROOT / 'proj.win32/Debug.win32/cs_bars.exe')],
                                   cwd=ROOT / 'Resources', env=env, startupinfo=startup,
                                   stdout=log, stderr=log)
        try:
            deadline = time.monotonic() + 150
            while time.monotonic() < deadline:
                text = trace.read_text() if trace.exists() else ''
                if 'FAIL' in text:
                    raise RuntimeError(text)
                if 'DONE turret attack review' in text:
                    assert text.count('PASS turret native type muzzle and burst') == 10
                    assert text.count('PASS turret damage commits exactly once') == 10
                    assert text.count('PASS capture ') == 40
                    for castle in range(1, 11):
                        for phase in ('prepare', 'launch', 'flight', 'impact'):
                            with Image.open(dest / f'turret-{castle:02}-{phase}.png') as image:
                                image.verify()
                    print(f'PASS 640x{height}: all ten turret types, burst timing, damage, and 40 captures', flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError('preview exited')
                time.sleep(.2)
            else:
                raise RuntimeError('turret review timeout')
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=5)
