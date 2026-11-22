"""Capture settings/languages and exercise shared button touch registration."""
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
    out = ROOT / f'output/ui-type/{height}'
    out.mkdir(parents=True, exist_ok=True)
    trace = out / 'phases.log'
    trace.write_text('')
    env = dict(os.environ, CS_UI_TYPE_REVIEW='1', CS_BATTLE_MENU_REVIEW='1',
               CS_BATTLE_MENU_HEIGHT=str(height), CS_CASTLE_REVIEW_PATH=out.as_posix() + '/')
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (out / 'run.log').open('w') as log:
        process = subprocess.Popen([str(ROOT / 'proj.win32/Debug.win32' / args.exe)],
                                   cwd=ROOT / 'Resources', env=env, startupinfo=startup,
                                   stdout=log, stderr=log)
        try:
            deadline = time.monotonic() + 60
            while time.monotonic() < deadline:
                checks = trace.read_text()
                if 'FAIL' in checks:
                    raise RuntimeError(checks)
                if 'DONE UI type review' in checks:
                    assert checks.count('PASS UI type capture') == 2, checks
                    print(f'PASS {height}: settings, languages, all language targets and selection', flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError(f'Preview exited: {process.returncode}')
                time.sleep(.2)
            else:
                raise TimeoutError(checks)
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=5)
