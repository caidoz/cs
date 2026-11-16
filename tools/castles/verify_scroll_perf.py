"""Compare native menus with/without preview/panel caches and covered-world culling."""
import os
import subprocess
import time
import re
from pathlib import Path

ROOT=Path(__file__).resolve().parents[2]
EXE=ROOT/'proj.win32/Debug.win32/cs.castle-scroll.exe'

def run(height,uncached):
    folder=ROOT/f'output/castle-scroll/{height}-{"before" if uncached else "after"}'
    folder.mkdir(parents=True,exist_ok=True)
    trace=folder/'phases.log';trace.write_text('')
    env=dict(os.environ,CS_CASTLE_REVIEW_PATH=folder.as_posix()+'/',CS_CASTLE_SCROLL_PERF_REVIEW='1',CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(height))
    if uncached:env['CS_CASTLE_PREVIEW_UNCACHED']='1'
    else:env.pop('CS_CASTLE_PREVIEW_UNCACHED',None)
    startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
    with (folder/'stdout.log').open('w') as log:
        process=subprocess.Popen([str(EXE)],cwd=ROOT/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
        try:
            deadline=time.monotonic()+120
            while time.monotonic()<deadline:
                text=trace.read_text(encoding='utf-8',errors='replace')
                if 'FAIL' in text:raise RuntimeError(text)
                if 'DONE castle scroll performance review' in text:
                    values=re.search(r'PROFILE frame_ms=([\d.]+) vertices=([\d.]+) batches=([\d.]+)',text)
                    assert values,text
                    print(f'PASS {height} {"before" if uncached else "after"}: {values.group(0)}',flush=True)
                    return tuple(map(float,values.groups()))
                if process.poll() is not None:raise RuntimeError(f'Exited: {process.returncode}: {text}')
                time.sleep(.2)
            raise RuntimeError(text)
        finally:
            if process.poll() is None:process.terminate()
            process.wait(timeout=10)

if __name__=='__main__':
    for height in (850,1408):
        before=run(height,True);after=run(height,False)
        assert after[1]<before[1]*.6,(before,after)
