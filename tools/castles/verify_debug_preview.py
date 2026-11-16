"""Exercise free stage previews and direct castle touches in the native game."""
from pathlib import Path
import os
import subprocess
import time

root = Path(__file__).resolve().parents[2]
for height in (850, 1408):
    out = root / f'output/free-preview-review/{height}'
    out.mkdir(parents=True, exist_ok=True)
    trace = out / 'phases.log'
    trace.write_text('')
    env = dict(os.environ, CS_CASTLE_FREE_PREVIEW_REVIEW='1',
               CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',
               CS_BATTLE_MENU_REVIEW='1', CS_BATTLE_MENU_HEIGHT=str(height))
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (out / 'stdout.log').open('w') as log:
        process = subprocess.Popen([str(root / 'proj.win32/Debug.win32/cs.free-preview.exe')],
                                   cwd=root / 'Resources', env=env, startupinfo=startup,
                                   stdout=log, stderr=log)
        try:
            deadline = time.monotonic() + 45
            while time.monotonic() < deadline:
                result = trace.read_text()
                if 'FAIL' in result:
                    raise RuntimeError(result)
                if 'DONE' in result:
                    assert 'PASS direct room turret castle and background touches without payment' in result
                    assert 'PASS normal upgrades still require gold and debug closes' in result
                    print(f'PASS {height}: free six-stage previews, direct touches, unchanged saves and paid upgrade guards', flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError(f'Exited {process.returncode}')
                time.sleep(.1)
            else:
                raise RuntimeError('Preview review timed out')
        finally:
            if process.poll() is None:
                process.terminate()
            try:
                process.wait(timeout=5)
            except subprocess.TimeoutExpired:
                process.kill()
                process.wait(timeout=10)
