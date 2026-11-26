"""Native nineteen-stage castle menu, scrolling and upgrade transaction review."""
import os,subprocess,time
from pathlib import Path
root=Path(__file__).resolve().parents[2];w=root/'output/castle-growth';w.mkdir(parents=True,exist_ok=True)
for height in (850,1408):
 out=w/str(height);out.mkdir(exist_ok=True);trace=out/'phases.log';trace.write_text('')
 env=dict(os.environ,CS_CASTLE_GROWTH_REVIEW='1',CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(height))
 si=subprocess.STARTUPINFO();si.dwFlags|=subprocess.STARTF_USESHOWWINDOW;si.wShowWindow=0
 with (out/'stdout.log').open('w') as log:
  p=subprocess.Popen([str(root/'proj.win32/Debug.win32/cs_castle_growth.exe')],cwd=root/'Resources',env=env,startupinfo=si,stdout=log,stderr=log)
  try:
   end=time.monotonic()+55
   while time.monotonic()<end:
    s=trace.read_text()
    if 'FAIL' in s:raise RuntimeError(s)
    if 'DONE castle growth review' in s:print(height,s,flush=True);break
    if p.poll() is not None:raise RuntimeError('Exited '+str(p.returncode))
    time.sleep(.1)
   else:raise RuntimeError('Timeout '+trace.read_text())
  finally:
   if p.poll() is None:p.terminate()
   p.wait(timeout=5)
