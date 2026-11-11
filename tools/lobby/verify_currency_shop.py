"""Capture the populated currency catalog and verify offline purchase guards."""
import os
import subprocess
import time
from pathlib import Path

ROOT=Path(__file__).resolve().parents[2]
for height in (850,1408):
    dest=ROOT/'output/currency-shop'/str(height)
    dest.mkdir(parents=True,exist_ok=True)
    trace=dest/'phases.log'
    trace.unlink(missing_ok=True)
    env=os.environ.copy()
    env.update(CS_CASTLE_REVIEW_PATH=dest.as_posix()+'/',CS_SHOP_CURRENCY_REVIEW='1',
               CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(height))
    startup=subprocess.STARTUPINFO()
    startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow=0
    exe=ROOT/'proj.win32/Debug.win32/cs.exe'
    with (dest/'stdout.log').open('w') as log:
        p=subprocess.Popen([str(exe)],cwd=ROOT/'Resources',env=env,stdout=log,stderr=subprocess.STDOUT,startupinfo=startup)
        try:
            until=time.monotonic()+60
            while time.monotonic()<until:
                text=trace.read_text() if trace.exists() else ''
                if 'FAIL' in text:raise RuntimeError(text)
                if 'DONE currency review' in text:
                    assert text.count('PASS currency capture')==2
                    print(f'PASS 640x{height}: twelve products, loaded art, disabled unavailable sales, top/bottom captures',flush=True)
                    break
                if p.poll() is not None:raise RuntimeError('preview exited')
                time.sleep(.2)
            else:raise RuntimeError('currency review timeout')
        finally:
            if p.poll() is None:p.terminate()
            p.wait(timeout=5)
