import os,subprocess,time,argparse
from pathlib import Path
parser=argparse.ArgumentParser();parser.add_argument('--height',type=int,default=850);args=parser.parse_args()
root=Path(__file__).resolve().parents[2];out=root/f'output/portrait-redesign/navigation-{args.height}';out.mkdir(parents=True,exist_ok=True)
trace=out/'phases.log';trace.write_text('')
env=dict(os.environ,CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',CS_CENTERED_LOBBY_NAV_REVIEW='1',CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(args.height))
startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
with (out/'stdout.log').open('w') as log:
 p=subprocess.Popen([str(root/'proj.win32/Debug.win32/cs_portrait_redesign.exe')],cwd=root/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
 try:
  end=time.monotonic()+55
  while time.monotonic()<end:
   result=trace.read_text(encoding='utf-8')
   if 'FAIL' in result:raise RuntimeError(result)
   if 'DONE centered lobby navigation review' in result:
    assert result.count('PASS section owns full height with no dock targets; lobby restores five actions')==5,result
    assert 'PASS nested modal owns input above section and resource bar' in result,result
    assert 'PASS closing all pages restores exactly five live lobby actions' in result,result
    print(result);break
   if p.poll() is not None:raise RuntimeError(str(p.returncode)+result)
   time.sleep(.2)
  else:raise RuntimeError('Timed out '+result)
 finally:
  if p.poll() is None:p.terminate()
  p.wait(timeout=10)
