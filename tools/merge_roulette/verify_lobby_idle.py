"""Exercise the actual lobby render path without advancing combat simulation."""
import os
from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).resolve().parents[2]
for height in (850, 1024, 1408):
    dest = ROOT / 'output/merge-lobby-idle-review' / str(height)
    dest.mkdir(parents=True, exist_ok=True)
    trace = dest / 'checks.log'
    trace.unlink(missing_ok=True)
    env = os.environ.copy()
    env.update(CS_MERGE_REVIEW='1', CS_MERGE_LOBBY_IDLE_REVIEW='1',
               CS_MERGE_REVIEW_HEIGHT=str(height), CS_MERGE_REVIEW_PATH=dest.as_posix() + '/')
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest / 'stdout.log').open('w') as log:
        process = subprocess.Popen([str(ROOT / 'proj.win32/Debug.win32/cs_bars.exe')],
                                   cwd=ROOT / 'Resources', env=env, stdout=log,
                                   stderr=log, startupinfo=startup)
        try:
            deadline = time.monotonic() + 60
            while time.monotonic() < deadline:
                text = trace.read_text() if trace.exists() else ''
                assert 'FAIL' not in text, text
                if 'DONE lobby idle review' in text:
                    assert 'PASS responsive castle and rail lift with fixed bottom navigation' in text, text
                    assert 'PASS lifted start button matches actual lobby touch coordinates' in text, text
                    assert (dest / 'lobby-idle-01.png').exists()
                    assert (dest / 'lobby-idle-02.png').exists()
                    print(f'PASS 640x{height}: native idle, responsive castle/rail, fixed menu and actual button hit area', flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError(f'Lobby review exited: {text}')
                time.sleep(.2)
            else:
                raise RuntimeError('Lobby review timed out: ' + text)
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=5)
