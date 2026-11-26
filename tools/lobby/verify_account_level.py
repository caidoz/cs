"""Check account EXP boundaries, real boss-only settlement and page ownership."""
import os,subprocess,time
from pathlib import Path
root=Path(__file__).resolve().parents[2]
for height in (850,1408):
 out=root/f'output/account-level/{height}';out.mkdir(parents=True,exist_ok=True)
 trace=out/'phases.log';trace.write_text('')
 env=dict(os.environ,CS_ACCOUNT_LEVEL_REVIEW='1',CS_FINAL_BOSS_REWARD_REVIEW='1',CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(height))
 startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
 with (out/'run.log').open('w') as log:
  p=subprocess.Popen([str(root/'proj.win32/Debug.win32/cs_account_level.exe')],cwd=root/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
  try:
   deadline=time.monotonic()+75
   while time.monotonic()<deadline:
    text=trace.read_text()
    if 'FAIL' in text:raise RuntimeError(text)
    if 'DONE account level review' in text:
     assert text.count('PASS account capture')==5,text
     print(height,text,flush=True);break
    if p.poll() is not None:raise RuntimeError(f'Exited {p.returncode}: {text}')
    time.sleep(.2)
   else:raise RuntimeError('Timeout: '+trace.read_text())
  finally:
   if p.poll() is None:p.terminate()
   p.wait(timeout=5)
