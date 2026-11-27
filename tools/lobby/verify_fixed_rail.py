"""Verify fixed rails against all19 castle renderers, including a scrolled viewport."""
from pathlib import Path
import argparse,importlib.util,json,re,shutil
root=Path(__file__).resolve().parents[2]
p=argparse.ArgumentParser();p.add_argument('--exe',default='cs_fixed_rail.exe');args=p.parse_args()
spec=importlib.util.spec_from_file_location('runtime_review',root/'tools/items/verify_runtime.py')
review=importlib.util.module_from_spec(spec);spec.loader.exec_module(review)
review.EXE=root/'proj.win32/Debug.win32'/args.exe
results=[]
for height in (850,1408):
 baseline=None
 for scroll in (False,True):
  folder=f'fixed-rail-{height}'+('-scrolled' if scroll else '')
  flags={'CS_PORTRAIT_REVIEW':'1','CS_PORTRAIT_LOBBY':'1','CS_MOTIF_SERIES_REVIEW':'1'}
  if scroll:flags['CS_FIXED_RAIL_SCROLL_REVIEW']='1'
  review.run(height,flags,folder,'DONE motif series review',38)
  path=root/'output/item-series/runtime'/folder
  text=(path/'checks.log').read_text(encoding='utf8')
  rows=[tuple(map(int,m)) for m in re.findall(r'RAIL lobby stage=(\d+) height=(\d+) ground=(\d+) lowerUiGap=(\d+) camera=(-?\d+)',text)]
  assert len(rows)==19 and [r[0] for r in rows]==list(range(1,20))
  assert len({r[2] for r in rows})==len({r[3] for r in rows})==1
  assert rows[0][3]==(21 if height==850 else 141)
  if baseline is None:baseline=rows[0][2:4]
  else:assert rows[0][2:4]==baseline and rows[0][4]<0
  results.append({'height':height,'scrolled':scroll,'ground':rows[0][2],'rail_to_region_panel_gap':rows[0][3],'stages':19,'captures':38})
  dest=root/'docs/design/fixed-rail-v1'
  shutil.copy2(path/'checks.log',dest/(folder+'.log'))
  if not scroll:
   for stage in (1,19):
    for scene in ('lobby','battle'):
     shutil.copy2(path/f'motif-{scene}-{stage:02}.png',dest/f'{scene}-{stage:02}-{height}.png')
(root/'docs/design/fixed-rail-v1/validation.json').write_text(json.dumps(results,indent=2),encoding='utf8')
print('PASS fixed rail position and scale for nineteen stages, both ratios and vertical scroll; 152 live captures')
