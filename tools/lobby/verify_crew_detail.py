"""Capture the native turn-based companion detail at both supported review sizes."""
from pathlib import Path
import os
import argparse
import subprocess
import time

root=Path(__file__).resolve().parents[2]
parser=argparse.ArgumentParser();parser.add_argument('--exe',default='cs.crew-detail.exe');args=parser.parse_args()
for height in (850,1408):
    out=root/f'output/crew-detail/{height}'
    out.mkdir(parents=True,exist_ok=True)
    trace=out/'phases.log'
    trace.write_text('')
    env=dict(os.environ,CS_CREW_DETAIL_REVIEW='1',CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(height))
    startup=subprocess.STARTUPINFO()
    startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow=0
    with (out/'run.log').open('w') as log:
        process=subprocess.Popen([str(root/'proj.win32/Debug.win32'/args.exe)],cwd=root/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
        try:
            deadline=time.monotonic()+40
            while time.monotonic()<deadline:
                result=trace.read_text()
                if 'FAIL' in result:raise RuntimeError(result)
                if 'DONE' in result:print(f'PASS {height}: {out / "crew-detail.png"}',flush=True);break
                if process.poll() is not None:raise RuntimeError(f'Exited {process.returncode}')
                time.sleep(.1)
            else:raise RuntimeError('Capture timed out')
        finally:
            if process.poll() is None:process.terminate()
            process.wait(timeout=10)
