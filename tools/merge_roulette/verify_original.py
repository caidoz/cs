"""Compare live original-pixel components against the same native reference transform."""
import os,time,subprocess,json,argparse
from pathlib import Path
from PIL import Image,ImageChops,ImageStat
root=Path(__file__).resolve().parents[2]
dest=root/'output/merge-roulette/original';dest.mkdir(parents=True,exist_ok=True)
trace=dest/'checks.log';trace.unlink(missing_ok=True)
env=os.environ.copy();env.update(CS_MERGE_REVIEW='1',CS_MERGE_ORIGINAL_REVIEW='1',CS_MERGE_REVIEW_HEIGHT='850',CS_MERGE_REVIEW_PATH=dest.as_posix()+'/')
startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
parser=argparse.ArgumentParser();parser.add_argument('--exe',default='proj.win32/Debug.win32/cs.exe');args=parser.parse_args()
exe=(root/args.exe).resolve()
with (dest/'stdout.log').open('w') as log:
 p=subprocess.Popen([str(exe)],cwd=exe.parent,env=env,stdout=log,stderr=subprocess.STDOUT,startupinfo=startup)
 try:
  deadline=time.monotonic()+60
  while time.monotonic()<deadline:
   txt=trace.read_text() if trace.exists() else ''
   if 'PASS capture '+(dest/'original-live-lobby.png').as_posix() in txt:break
   if p.poll() is not None:raise RuntimeError('preview exited')
   time.sleep(.1)
  else:raise RuntimeError('capture timeout')
 finally:p.terminate();p.wait(timeout=5)
a=Image.open(dest/'original-uniform-reference.png').convert('RGB');b=Image.open(dest/'original-live-lobby.png').convert('RGB')
regions={'start':(190,642,450,683),'continue':(258,712,390,728),'manage':(255,600,383,611),'tower':(139,67,154,80),'beam':(180,303,490,309)}
result={}
for name,q in regions.items():
 q=(q[0],q[1]-40,q[2],q[3]-40)
 d=ImageChops.difference(a.crop(q),b.crop(q));stat=ImageStat.Stat(d)
 result[name]={'maxDifference':max(v[1] for v in d.getextrema()),'meanDifference':max(stat.mean)}
 assert result[name]['maxDifference']<=(4 if name=='beam' else 2) and result[name]['meanDifference']<.05,(name,result[name])
print('PASS original tower, beam and three buttons use matching native source pixels',flush=True)
(dest/'verification.json').write_text(json.dumps(result,indent=2))
