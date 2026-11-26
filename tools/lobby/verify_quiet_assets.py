"""Review transparent rarity surrounds and all 33 repainted chest atlases natively."""
from pathlib import Path
import argparse,os,subprocess,time
from PIL import Image
root=Path(__file__).resolve().parents[2]
p=argparse.ArgumentParser();p.add_argument('--height',type=int,nargs='*',default=[850,1408]);args=p.parse_args()
for i in range(33):
 with Image.open(root/f'Resources/res/box{i}.png') as image:
  assert image.size==(1024,512),(i,image.size)
  alpha=image.convert('RGBA').getchannel('A')
  assert alpha.getextrema()==(0,255),i
  assert all(alpha.crop((x,0,x+512,512)).getbbox() for x in (0,512)),i
print('PASS 33 original 1024x512 atlases, transparent alpha and two nonempty 512x512 poses',flush=True)
for height in args.height:
 out=root/f'output/quiet-menu-assets-{height}';out.mkdir(parents=True,exist_ok=True)
 trace=out/'phases.log';trace.write_text('')
 env=dict(os.environ,CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',CS_QUIET_CARD_REVIEW='1',CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(height),CS_ASSET_DRAW_AUDIT=str(out/'asset-draw.log'),CS_ASSET_AUDIT=str(out/'asset-load.log'))
 startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
 with (out/'stdout.log').open('w') as log:
  process=subprocess.Popen([str(root/'proj.win32/Debug.win32/cs_portrait_redesign.exe')],cwd=root/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
  try:
   end=time.monotonic()+55
   while time.monotonic()<end:
    result=trace.read_text(encoding='utf8')
    assert 'FAIL' not in result,result
    if 'DONE quiet cards and 33 chest poses review' in result:
     assert result.count('PASS quiet native capture')==6,result
     assert all((out/f'quiet-assets-{i}.png').exists() for i in range(6))
     drawn=(out/'asset-draw.log').read_text(encoding='utf8');loaded=(out/'asset-load.log').read_text(encoding='utf8')
     assert all(f'res/box{i}.png' in drawn for i in range(33)),drawn
     assert all(f'res/shop_gems_v1-tier-{i:02}.png' in drawn for i in range(1,7)),drawn
     assert 'MISSING' not in loaded,loaded
     print(f'PASS {height}: six rarity frames and all 33 closed/open chest pairs and six diamond bundles captured',flush=True);break
    if process.poll() is not None:raise RuntimeError(f'Native review exited {process.returncode}')
    time.sleep(.2)
   else:raise RuntimeError('Native quiet asset review timed out')
  finally:
   if process.poll() is None:process.terminate()
   process.wait(timeout=10)
