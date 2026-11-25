"""Validate the complete replacement effect bank; --native exercises both game playback routes."""
from pathlib import Path
import argparse,array,hashlib,json,os,re,subprocess,sys,wave
ROOT=Path(__file__).resolve().parents[2]
def main():
 parser=argparse.ArgumentParser();parser.add_argument('--native',action='store_true');args=parser.parse_args()
 names=re.findall(r'"(sfx-[a-z-]+\.ogg)"',(ROOT/'Classes/GameSfx.h').read_text())
 assert len(names)==len(set(names))==49
 catalog=json.loads((ROOT/'content/runtime-assets.json').read_text(encoding='utf8'));assets={a['target']:a for a in catalog['assets']};hashes=set()
 for name in names:
  target='res/'+name;assert target in assets
  source=ROOT/assets[target]['source'];runtime=ROOT/'Resources'/target
  data=source.read_bytes();digest=hashlib.sha256(data).hexdigest();assert digest not in hashes;hashes.add(digest)
  assert runtime.read_bytes()==data
  with wave.open(str(source.with_suffix('.wav')),'rb') as w:
   assert (w.getnchannels(),w.getsampwidth(),w.getframerate())==(1,2,32000)
   assert .05<=w.getnframes()/w.getframerate()<=1.5
   samples=array.array('h',w.readframes(w.getnframes()))
  assert 1000<max(abs(x) for x in samples)<32767
  assert abs(samples[0])<500 and abs(samples[-1])<500
 for row in json.loads((ROOT/'asset_library/reference/audio-legacy-sfx-20261125/manifest.json').read_text()):
  assert row['target'] not in assets
  assert hashlib.sha256((ROOT/row['backup']).read_bytes()).hexdigest()==row['sha256']
 print('PASS 49 unique effect masters, OGG runtime cues and verified legacy backups',flush=True)
 if args.native:
  env=os.environ.copy();env['CS_SFX_REVIEW']='1'
  subprocess.run([sys.executable,str(ROOT/'tools/merge_roulette/verify_portrait.py'),'--height','850','--stage','0','--lobby'],env=env,cwd=ROOT,check=True)
  log=(ROOT/'output/portrait-redesign/850/lobby/checks.log').read_text(encoding='utf8')
  assert len(re.findall('PASS decoded native cue ',log))==49
  for required in ['both effect routes honor mute','duplicate play/effect routes coalesce once','dense effect burst is capped at twelve voices']:assert required in log
if __name__=='__main__':main()
