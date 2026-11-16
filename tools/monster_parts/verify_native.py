"""Run actual Win32 game captures at both supported review heights."""
import os
import subprocess
import time
from pathlib import Path

ROOT=Path(__file__).resolve().parents[2]

def verify(height):
    out=ROOT/f'output/monster-parts-native/{height}';out.mkdir(parents=True,exist_ok=True)
    trace=out/'checks.log'
    if trace.exists():trace.unlink()
    env=dict(os.environ,CS_MERGE_REVIEW='1',CS_MONSTER_PARTS_REVIEW='1',CS_MERGE_REVIEW_HEIGHT=str(height),CS_MERGE_REVIEW_PATH=out.as_posix()+'/')
    startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
    with (out/'stdout.log').open('w') as log:
        process=subprocess.Popen([str(ROOT/'proj.win32/Debug.win32/cs.monster-parts.exe')],cwd=ROOT/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
        try:
            deadline=time.monotonic()+120
            while time.monotonic()<deadline:
                text=trace.read_text(encoding='utf-8',errors='replace') if trace.exists() else ''
                if 'FAIL' in text:raise RuntimeError(text)
                if 'DONE monster parts review' in text:
                    assert len(list(out.glob('monster-parts-*.png')))==5
                    print(f'PASS 640x{height}: {text.strip()}',flush=True);return
                if process.poll() is not None:raise RuntimeError(f'Game exited {process.returncode}: {text}')
                time.sleep(.2)
            raise RuntimeError(f'Timed out: {text}')
        finally:
            if process.poll() is None:process.terminate()
            process.wait(timeout=10)

if __name__=='__main__':
    for height in (850,1408):verify(height)
