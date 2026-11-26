"""Check actual rendered rarity pixels for owned gear and companions."""
from pathlib import Path
import os,re,subprocess,sys
from PIL import Image
root=Path(__file__).resolve().parents[2]
for height in (850,1408):
 env=dict(os.environ,CS_GRID_RARITY_REVIEW='1')
 subprocess.run([sys.executable,str(root/'tools/merge_roulette/verify_portrait.py'),'--height',str(height),'--stage','0'],env=env,cwd=root,check=True)
 out=root/f'output/portrait-redesign/{height}/stage-01'
 log=(out/'checks.log').read_text(encoding='utf8')
 samples=re.findall(r'RIM (\d+) ([0-9A-F]+) (\d+) (\d+)',log)
 assert len(samples)==12,log
 with Image.open(out/'grid-rarity.png').convert('RGB') as image:
  for rank,color,x,y in samples:
   value=int(color,16);expected=(value>>16,(value>>8)&255,value&255)
   assert image.getpixel((int(x),int(y)))==expected,(height,rank,image.getpixel((int(x),int(y))),expected)
 print(f'PASS {height}: all six rarity colors match actual gear and companion border pixels')
