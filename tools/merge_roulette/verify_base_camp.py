"""Native regression: compact PvE/PvP HUD and recall/close/travel handoff."""
from pathlib import Path
import argparse,os,subprocess,sys
ROOT=Path(__file__).resolve().parents[2]
p=argparse.ArgumentParser();p.add_argument('--height',type=int,nargs='*',default=[850,1408]);p.add_argument('--record',action='store_true');args=p.parse_args()
for height in args.height:
 for flag,lobby in [('CS_BASE_HUD_REVIEW',False),('CS_BASE_CAMP_REVIEW',True)]:
  env=os.environ.copy()
  for key in ('CS_BASE_HUD_REVIEW','CS_BASE_CAMP_REVIEW','CS_BASE_CAPTURE_FRAMES'):env.pop(key,None)
  env[flag]='1'
  if args.record and lobby and height==850:env['CS_BASE_CAPTURE_FRAMES']='1'
  command=[sys.executable,str(ROOT/'tools/merge_roulette/verify_portrait.py'),'--height',str(height),'--stage','0']
  if lobby:command.append('--lobby')
  subprocess.run(command,env=env,cwd=ROOT,check=True)
  log=(ROOT/f'output/portrait-redesign/{height}'/('lobby' if lobby else 'stage-01')/'checks.log').read_text(encoding='utf8')
  expected=['owned residents populate interior','all exterior actors enter before facade','castle accelerates and scales uniformly','departure commits one paid battle','battle arrives with compact friendly trio'] if lobby else ['left-half allied trio','mirrors HP defense attack','physical HUD ownership stays fixed']
  for text in expected:assert text in log,text
print('PASS native HUD ownership, recall sequence, closed facade, camera handoff and single entry charge')
