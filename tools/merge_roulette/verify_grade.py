"""Capture four-star arrival and an actual five-star equipment merge."""
import os
from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).resolve().parents[2]
dest = ROOT / 'output/merge-grade-review'
dest.mkdir(parents=True, exist_ok=True)
trace = dest / 'checks.log'
trace.unlink(missing_ok=True)
env = os.environ.copy()
env.update(CS_MERGE_REVIEW='1', CS_MERGE_GRADE_REVIEW='1',
           CS_MERGE_REVIEW_PATH=dest.as_posix() + '/')
startup = subprocess.STARTUPINFO()
startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
startup.wShowWindow = 0
with (dest / 'stdout.log').open('w') as log:
    process = subprocess.Popen([str(ROOT / 'proj.win32/Debug.win32/cs_review.exe')],
                               cwd=ROOT / 'Resources', env=env, stdout=log,
                               stderr=log, startupinfo=startup)
    try:
        deadline = time.monotonic() + 60
        while time.monotonic() < deadline:
            text = trace.read_text() if trace.exists() else ''
            assert 'FAIL' not in text, text
            if ('DONE grade accent review' in text and
                    (dest / 'grade-02-five-star-merge.png').exists()):
                print('PASS four-star arrival, actual five-star merge, and accent expiration')
                break
            if process.poll() is not None:
                raise RuntimeError(f'Preview exited: {text}')
            time.sleep(.2)
        else:
            raise RuntimeError('Grade review timed out: ' + text)
    finally:
        if process.poll() is None:
            process.terminate()
        process.wait(timeout=5)
