"""Check native counterattack patterns through the real builder and renderer."""
import argparse
import os
from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).resolve().parents[2]


def verify(exe, height):
    dest = ROOT / 'output/enemy-pattern-review' / str(height)
    dest.mkdir(parents=True, exist_ok=True)
    trace = dest / 'checks.log'
    trace.unlink(missing_ok=True)
    env = dict(os.environ, CS_MERGE_REVIEW='1', CS_MERGE_ENEMY_PATTERN_REVIEW='1',
               CS_MERGE_REVIEW_HEIGHT=str(height), CS_MERGE_REVIEW_PATH=dest.as_posix() + '/')
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest / 'stdout.log').open('w') as log:
        process = subprocess.Popen([str(exe)], cwd=ROOT / 'Resources', env=env,
                                   stdout=log, stderr=log, startupinfo=startup)
        try:
            deadline = time.monotonic() + 120
            while time.monotonic() < deadline:
                result = trace.read_text() if trace.exists() else ''
                if 'FAIL' in result:
                    raise RuntimeError(result)
                if 'DONE enemy pattern review' in result:
                    assert 'stationary attacks at native range' in result
                    print(f'PASS 640x{height}: {result.strip()}', flush=True)
                    return
                if process.poll() is not None:
                    raise RuntimeError(f'Preview exited {process.returncode}: {result}')
                time.sleep(.2)
            raise RuntimeError('Enemy pattern review timed out: ' + result)
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=5)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--exe', default='proj.win32/Debug.win32/cs_enemy_patterns.exe')
    args = parser.parse_args()
    for height in (850, 1408):
        verify((ROOT / args.exe).resolve(), height)
