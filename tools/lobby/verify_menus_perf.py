"""Measure the same six menu fixtures through legacy and optimized render paths."""
import json
import os
from pathlib import Path
import re
import subprocess
import time

ROOT=Path(__file__).resolve().parents[2]
EXE=ROOT/'proj.win32/Debug.win32/cs.lobby-menus-review.exe'
BEFORE_EXE=ROOT/'proj.win32/Debug.win32/cs.lobby-menus-before.exe'

def run(height,before):
    out=ROOT/f'output/lobby-menus/{height}-{"before" if before else "after"}'
    out.mkdir(parents=True,exist_ok=True)
    trace=out/'phases.log';trace.write_text('')
    env=dict(os.environ,CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',CS_LOBBY_MENUS_PERF_REVIEW='1',CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(height))
    if before:env['CS_LOBBY_MENUS_UNOPTIMIZED']='1'
    else:env.pop('CS_LOBBY_MENUS_UNOPTIMIZED',None)
    startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
    with (out/'stdout.log').open('w') as log:
        process=subprocess.Popen([str(BEFORE_EXE if before else EXE)],cwd=ROOT/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
        try:
            deadline=time.monotonic()+180
            while time.monotonic()<deadline:
                text=trace.read_text(encoding='utf-8',errors='replace')
                if 'FAIL' in text:raise RuntimeError(text)
                if 'DONE lobby menus performance review' in text:
                    found=re.findall(r'PROFILE (\w+) frame_ms=([\d.]+) vertices=([\d.]+) batches=([\d.]+)',text)
                    assert len(found)==6,text
                    assert text.count('PASS settings return preserves parent page')==6,text
                    result={name:dict(zip(('frame_ms','vertices','batches'),map(float,(ms,verts,batches)))) for name,ms,verts,batches in found}
                    print(f'PASS {height} {"before" if before else "after"}: {json.dumps(result)}',flush=True)
                    return result
                if process.poll() is not None:raise RuntimeError(f'Exited {process.returncode}: {text}')
                time.sleep(.2)
            raise RuntimeError(f'Timed out: {text}')
        finally:
            if process.poll() is None:process.terminate()
            process.wait(timeout=10)

if __name__=='__main__':
    report={}
    for height in (850,1408):
        report[str(height)]={'before':run(height,True),'after':run(height,False)}
        (ROOT/'output/lobby-menus/verification.json').write_text(json.dumps(report,indent=2))
