"""Exercise real debug close/reopen and normal departure-selection guards."""
import argparse
import os
from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser()
parser.add_argument('--height', type=int, default=850)
args = parser.parse_args()
out = ROOT / f'output/portrait-redesign/debug-selection-{args.height}'
out.mkdir(parents=True, exist_ok=True)
trace = out / 'phases.log'
trace.write_text('', encoding='utf-8')
env = dict(os.environ, CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',
           CS_CASTLE_DEBUG_SELECTION_REVIEW='1', CS_BATTLE_MENU_REVIEW='1',
           CS_BATTLE_MENU_HEIGHT=str(args.height))
startup = subprocess.STARTUPINFO()
startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
startup.wShowWindow = 0
with (out / 'stdout.log').open('w') as log:
    process = subprocess.Popen([str(ROOT / 'proj.win32/Debug.win32/cs_portrait_redesign.exe')],
                               cwd=ROOT / 'Resources', env=env, startupinfo=startup,
                               stdout=log, stderr=log)
    try:
        deadline = time.monotonic()+55
        while time.monotonic() < deadline:
            result = trace.read_text(encoding='utf-8')
            if 'FAIL' in result:
                raise RuntimeError(result)
            if 'DONE debug selection review' in result:
                assert 'PASS first castle after debug close capture' in result, result
                print(result)
                break
            if process.poll() is not None:
                raise RuntimeError(f'Exited {process.returncode}: {result}')
            time.sleep(.2)
        else:
            raise RuntimeError(f'Timed out: {result}')
    finally:
        if process.poll() is None:
            process.terminate()
        process.wait(timeout=10)
