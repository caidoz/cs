"""Run native block hit tests, confirmations and actual effect bindings."""
from pathlib import Path
import argparse
import os
import subprocess
import time

root = Path(__file__).resolve().parents[2]
parser=argparse.ArgumentParser()
parser.add_argument('--exe',default='cs.castle-blocks.exe')
args=parser.parse_args()
for height in (850, 1408):
    out = root / f'output/castle-upgrade-blocks/{height}'
    out.mkdir(parents=True, exist_ok=True)
    trace = out / 'phases.log'
    trace.write_text('')
    env = dict(os.environ, CS_CASTLE_BLOCKS_REVIEW='1',
               CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',
               CS_BATTLE_MENU_REVIEW='1', CS_BATTLE_MENU_HEIGHT=str(height))
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (out / 'stdout.log').open('w') as log:
        process = subprocess.Popen([str(root / 'proj.win32/Debug.win32' / args.exe)],
                                   cwd=root / 'Resources', env=env, startupinfo=startup,
                                   stdout=log, stderr=log)
        try:
            deadline = time.monotonic()+60
            while time.monotonic() < deadline:
                result = trace.read_text()
                if 'FAIL' in result:
                    raise RuntimeError(result)
                if 'DONE' in result:
                    assert result.count('PASS full block touch') == 5, result
                    assert result.count('PASS upgrade button at least 48 high') == 5, result
                    assert result.count('PASS block cancel') == 5, result
                    assert result.count('PASS block confirmation charges once') == 5, result
                    assert result.count('PASS block confirmation capture') == 5, result
                    assert 'PASS five real effects' in result, result
                    print(f'PASS {height}: five full-block touches, cancel, single charges, scope and actual effects', flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError(f'Exited {process.returncode}')
                time.sleep(.1)
            else:
                raise RuntimeError('Block review timed out')
        finally:
            if process.poll() is None:
                process.terminate()
            try:
                process.wait(timeout=5)
            except subprocess.TimeoutExpired:
                process.kill()
                process.wait(timeout=10)
