"""Verify native costume slots, upgrade cues, and grid-landing timing."""
import os
from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).resolve().parents[2]
EXE = ROOT / 'proj.win32/Debug.win32/cs_bars.exe'
for height in (850, 1408):
    dest = ROOT / 'output/merge-costume-review' / str(height)
    dest.mkdir(parents=True, exist_ok=True)
    trace = dest / 'checks.log'
    trace.unlink(missing_ok=True)
    env = os.environ.copy()
    env.update(CS_MERGE_REVIEW='1', CS_MERGE_COSTUME_REVIEW='1',
               CS_MERGE_REVIEW_HEIGHT=str(height), CS_MERGE_REVIEW_PATH=dest.as_posix() + '/')
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest / 'stdout.log').open('w') as log:
        process = subprocess.Popen([str(EXE)], cwd=ROOT / 'Resources', env=env,
                                   stdout=log, stderr=log, startupinfo=startup)
        try:
            deadline = time.monotonic() + 90
            while time.monotonic() < deadline:
                text = trace.read_text() if trace.exists() else ''
                if 'FAIL' in text:
                    raise RuntimeError(text)
                if 'DONE costume review' in text and 'PASS capture ' in text and (dest / 'costume-weapon-level-up.png').exists():
                    for check in ('downgrade does not trigger level up',
                                  'higher grade weapon triggers level up',
                                  'weaker roulette weapon does not trigger level up',
                                  'equal roulette weapon does not trigger level up',
                                  'each sword attacks in its own costume and best weapon returns before enemy turn without level up'):
                        assert 'PASS ' + check in text, text
                    print(f'PASS 640x{height}: upgrades only, landing gate, per-sword attack costume and best weapon restoration', flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError(f'Game exited: {process.returncode}')
                time.sleep(.1)
            else:
                raise TimeoutError(text)
        finally:
            process.terminate()
            process.wait(timeout=10)
