"""Verify equipment stats, scrolling, exact-instance equip and duplicate status."""
import argparse
import os
from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--exe', default='cs.exe')
args = parser.parse_args()
for height in (850, 1408):
    dest = ROOT / f'output/equipment-stats/{height}'
    dest.mkdir(parents=True, exist_ok=True)
    trace = dest / 'phases.log'
    trace.write_text('')
    env = dict(os.environ, CS_EQUIP_STATS_REVIEW='1',
               CS_CASTLE_REVIEW_PATH=dest.as_posix()+'/',
               CS_BATTLE_MENU_REVIEW='1', CS_BATTLE_MENU_HEIGHT=str(height))
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest / 'run.log').open('w') as log:
        process = subprocess.Popen([str(ROOT/'proj.win32/Debug.win32'/args.exe)],
                                   cwd=ROOT/'Resources', env=env, startupinfo=startup,
                                   stdout=log, stderr=log)
        try:
            deadline = time.monotonic()+60
            while time.monotonic()<deadline:
                checks = trace.read_text()
                if 'FAIL' in checks:
                    raise RuntimeError(checks)
                if 'DONE equipment stats review' in checks:
                    assert checks.count('PASS equipment stats instance and input')==4, checks
                    assert checks.count('PASS equipment stats capture')==4, checks
                    print(f'PASS {height}: stats, scroll, exact instance, equipped state and duplicates', flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError(f'Game exited: {process.returncode}')
                time.sleep(.2)
            else:
                raise TimeoutError(checks)
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=10)
