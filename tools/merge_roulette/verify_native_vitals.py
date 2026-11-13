"""Check native stats, ten hearts, companion warp and animated counter damage."""
import argparse
import os
from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser()
parser.add_argument('--exe', default='proj.win32/Debug.win32/cs_bars.exe')
parser.add_argument('--slow-rects', action='store_true')
args = parser.parse_args()
for height in (850, 1408):
    dest = ROOT / ('output/merge-native-vitals-slow-review' if args.slow_rects else 'output/merge-native-vitals-review') / str(height)
    dest.mkdir(parents=True, exist_ok=True)
    trace = dest / 'checks.log'
    trace.unlink(missing_ok=True)
    env = os.environ.copy()
    if args.slow_rects:
        env['CS_MERGE_SLOW_RECTS'] = '1'
    env.update(CS_MERGE_REVIEW='1', CS_MERGE_VITALS_REVIEW='1',
               CS_MERGE_REVIEW_HEIGHT=str(height), CS_MERGE_REVIEW_PATH=dest.as_posix() + '/')
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest / 'stdout.log').open('w') as log:
        process = subprocess.Popen([str((ROOT / args.exe).resolve())], cwd=ROOT / 'Resources',
                                   env=env, stdout=log, stderr=log, startupinfo=startup)
        try:
            deadline = time.monotonic() + 120
            while time.monotonic() < deadline:
                text = trace.read_text() if trace.exists() else ''
                assert 'FAIL' not in text, text
                if ('DONE native vitals review' in text and
                        'PASS capture ' in text and (dest / 'vitals-03-native-counter-damage.png').exists()):
                    print(f'PASS 640x{height}: native HP/armor, ten hearts, warp and animated damage', flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError(f'Preview exited: {text}')
                time.sleep(.2)
            else:
                raise RuntimeError('Native vitals review timed out: ' + text)
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=5)
