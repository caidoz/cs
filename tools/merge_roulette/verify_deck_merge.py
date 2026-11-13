"""Exercise actual crew drags and the material-to-result transition on the deck."""
import argparse
import os
from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser()
parser.add_argument('--exe', default='proj.win32/Debug.win32/cs_bars.exe')
args = parser.parse_args()
for height in (850, 1408):
    dest = ROOT / 'output/merge-deck-fusion-review' / str(height)
    dest.mkdir(parents=True, exist_ok=True)
    trace = dest / 'checks.log'
    trace.unlink(missing_ok=True)
    env = os.environ.copy()
    env.update(CS_MERGE_REVIEW='1', CS_MERGE_DECK_MERGE_REVIEW='1',
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
                if 'DONE deck merge review' in text:
                    for check in ('deck merge triggered by actual grid drag',
                                  'two deck materials converge before result appears',
                                  'attacks wait for deck merge presentation',
                                  'material pair becomes the actual merged crew with native warp',
                                  'deck merge finishes with one result and no stale materials'):
                        assert text.count('PASS ' + check) == 2, text
                    for case in ('different', 'identical'):
                        for phase in ('01-before', '02-gather', '03-warp'):
                            assert (dest / f'deck-merge-{case}-{phase}.png').exists()
                    print(f'PASS 640x{height}: distinct and identical crew converge, warp, and leave the actual result', flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError(f'Preview exited: {text}')
                time.sleep(.2)
            else:
                raise RuntimeError('Deck merge review timed out: ' + text)
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=5)
