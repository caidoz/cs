"""Verify glove stats/turns and capture the dedicated lever and full-length held sword."""
import os
from pathlib import Path
import subprocess
import time
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
for height in (850, 1408):
    dest = ROOT / 'output/passive-glove-lever-review' / str(height)
    dest.mkdir(parents=True, exist_ok=True)
    trace = dest / 'checks.log'
    trace.unlink(missing_ok=True)
    env = os.environ.copy()
    env.update(CS_MERGE_REVIEW='1', CS_MERGE_ATTACK_STAT_REVIEW='1',
               CS_MERGE_REVIEW_HEIGHT=str(height), CS_MERGE_REVIEW_PATH=dest.as_posix() + '/')
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest / 'stdout.log').open('w') as log:
        process = subprocess.Popen([str(ROOT / 'proj.win32/Debug.win32/cs_bars.exe')],
                                   cwd=ROOT / 'Resources', env=env, startupinfo=startup,
                                   stdout=log, stderr=log)
        try:
            deadline = time.monotonic() + 90
            while time.monotonic() < deadline:
                text = trace.read_text() if trace.exists() else ''
                if 'FAIL' in text:
                    raise RuntimeError(text)
                if 'DONE attack stat review' in text and text.count('PASS capture ') >= 2:
                    assert 'PASS gloves are passive and sword uses the actual increased attack stat' in text
                    assert 'PASS dedicated plump lever icon loaded' in text
                    with Image.open(dest / 'glove-passive-sword-lever-ready.png') as image:
                        image.verify()
                    print(f'PASS 640x{height}: glove attack gain, no glove turns, native sword power, lever asset and captures', flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError('preview exited')
                time.sleep(.2)
            else:
                raise RuntimeError('passive glove review timeout')
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=5)
