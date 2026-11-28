"""Fit approved original castle exteriors vertically; expressly requested 2026-11-28."""
from pathlib import Path
import argparse, hashlib, json, shutil
from PIL import Image
ROOT=Path(__file__).resolve().parents[2]
SOURCE=ROOT/'asset_library/work/castle-exterior-silhouette-20261128/previous-production'
WORK=ROOT/'asset_library/work/castle-exterior-original-height-fit-20261128'
def main():
 parser=argparse.ArgumentParser();parser.add_argument('--apply',action='store_true');args=parser.parse_args()
 WORK.mkdir(exist_ok=True);out=WORK/'selected-finals';out.mkdir(exist_ok=True)
 entries={a['target']:a for a in json.loads((ROOT/'content/runtime-assets.json').read_text(encoding='utf-8'))['assets']}
 report=[]
 for n in range(1,20):
  name=f'portrait-castle-{n:02d}.png';src=SOURCE/name
  interior='portrait-starter-interior.png' if n==1 else f'portrait-castle-interior-{n:02d}.png'
  refentry=entries['res/'+interior];ref=ROOT/refentry.get('original_source',refentry['source'])
  original=Image.open(src).convert('RGBA');target=Image.open(ref)
  assert original.width==target.width,(n,original.size,target.size)
  # Explicit user exception: preserve X and adjust only Y. No regeneration,
  # reference-alpha replacement, rim compositing or floor-by-floor facade paint.
  final=original.resize(target.size,Image.Resampling.LANCZOS) if original.size!=target.size else original.copy()
  dest=out/name;final.save(dest)
  item=dict(stage=n,source=src.relative_to(ROOT).as_posix(),source_sha256=hashlib.sha256(src.read_bytes()).hexdigest(),interior=ref.relative_to(ROOT).as_posix(),source_size=original.size,final_size=final.size,x_scale=1.0,y_scale=final.height/original.height,canvas_identical=True,alpha_identical_not_required=True,selected=dest.relative_to(ROOT).as_posix())
  if args.apply:
   entry=entries['res/'+name];master=ROOT/entry.get('original_source',entry['source']);shutil.copy2(dest,master);item['master']=master.relative_to(ROOT).as_posix()
  report.append(item)
 (WORK/'height-fit-report.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
 print('PASS all19 original exteriors retained; width unchanged; height fitted to corresponding interior canvas')
if __name__=='__main__':main()
