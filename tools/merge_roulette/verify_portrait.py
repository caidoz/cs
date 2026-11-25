"""Isolated native captures and actual button input at compact/tall ratios."""
import os
from pathlib import Path
import subprocess
import time
import argparse
import json

ROOT=Path(__file__).resolve().parents[2]
parser=argparse.ArgumentParser()
parser.add_argument('--height',type=int,default=850)
parser.add_argument('--stage',type=int,default=9)
parser.add_argument('--lobby',action='store_true')
parser.add_argument('--entry',action='store_true')
parser.add_argument('--overlap',action='store_true')
parser.add_argument('--enemy-attack',action='store_true')
parser.add_argument('--catapult',action='store_true')
parser.add_argument('--sample-assets',type=Path)
parser.add_argument('--sample-foot-x',type=float,default=65)
parser.add_argument('--sample-assembled',action='store_true')
parser.add_argument('--sample-ground',action='store_true')
parser.add_argument('--sample-rail-y',type=float)
args=parser.parse_args()
name=('lobby' if args.stage==0 else f'lobby-stage-{args.stage+1:02d}') if args.lobby else f'stage-{args.stage+1:02d}'
if args.entry:name='entry-'+name
if args.overlap:name='overlap-'+name
if args.enemy_attack:name='enemy-attack-'+name
if args.catapult:name='catapult-'+name
dest=ROOT/'output/portrait-redesign'/str(args.height)/name
if args.sample_assets:
    assert args.stage==0,'Artwork samples currently support the first stage only'
    dest=args.sample_assets.resolve().parent/f'{"lobby" if args.lobby else "battle"}-{args.height}'
dest.mkdir(parents=True,exist_ok=True)
trace=dest/'checks.log';trace.unlink(missing_ok=True)
env=os.environ.copy()
env.update(CS_MERGE_REVIEW='1',CS_PORTRAIT_REVIEW='1',CS_PORTRAIT_STAGE=str(args.stage),
           CS_MERGE_REVIEW_HEIGHT=str(args.height),CS_MERGE_REVIEW_PATH=dest.as_posix()+'/')
for audit_name in ('asset-load.log','asset-draw.log'):(dest/audit_name).unlink(missing_ok=True)
env.update(CS_ASSET_AUDIT=str(dest/'asset-load.log'),CS_ASSET_DRAW_AUDIT=str(dest/'asset-draw.log'))
if args.sample_assets:
    env.update(CS_PORTRAIT_SAMPLE_ASSETS=args.sample_assets.resolve().as_posix()+'/',
               CS_PORTRAIT_SAMPLE_FOOT_X=str(args.sample_foot_x))
if args.sample_assembled:
    assert args.sample_assets,'An assembled sample requires an external asset root'
    env['CS_PORTRAIT_SAMPLE_ASSEMBLED']='1'
if args.sample_ground:
    assert args.sample_assembled,'The road preview requires the assembled artwork sample'
    env['CS_PORTRAIT_SAMPLE_GROUND']='1'
if args.sample_rail_y is not None:
    assert args.sample_ground,'The rail baseline requires the ground preview'
    env['CS_PORTRAIT_SAMPLE_RAIL_Y']=str(args.sample_rail_y)
if args.lobby:env['CS_PORTRAIT_LOBBY']='1'
if args.entry:env['CS_PORTRAIT_ENTRY']='1'
if args.enemy_attack:env['CS_PORTRAIT_ENEMY_ATTACK']='1'
if args.catapult:env['CS_PORTRAIT_CATAPULT']='1'
if args.overlap:
    env['CS_PORTRAIT_OVERLAP']='1'
    (dest/'merge-diag.txt').write_text('previous-session-marker\n',encoding='utf-8')
startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
with (dest/'stdout.log').open('w',encoding='utf-8') as log:
    exe=ROOT/'proj.win32/Debug.win32/cs_portrait_redesign.exe'
    if args.sample_assets:exe=exe.with_name('cs_castle_tone_sample.exe')
    p=subprocess.Popen([str(exe)],cwd=ROOT/'Resources',env=env,stdout=log,stderr=log,startupinfo=startup)
    try:
        deadline=time.monotonic()+70
        while time.monotonic()<deadline:
            result=trace.read_text(encoding='utf-8') if trace.exists() else ''
            if 'FAIL' in result:raise RuntimeError(result)
            if 'DONE portrait review' in result:
                assert (dest/('catapult-release.png' if args.catapult else 'lobby.png' if args.lobby else 'battle.png')).is_file()
                loads=(dest/'asset-load.log').read_text(encoding='utf-8')
                if args.enemy_attack:
                    draws=(dest/'asset-draw.log').read_text(encoding='utf-8')
                    assert 'res/monster_parts-atlas-' not in draws,draws
                    assert 'PASS native monster attack never overlays the player grid' in result,result
                    print('PASS monster attack draws no part atlas over the player inventory',flush=True)
                assert 'MISSING' not in loads,loads
                retired=json.loads((ROOT/'tools/merge_roulette/retired_portrait_runtime_assets.json').read_text())
                assert all(a['target'] not in loads for a in retired['assets']),loads
                if args.overlap:
                    diagnostic=(dest/'merge-diag.txt').read_text(encoding='utf-8')
                    assert 'result=overlap' in diagnostic and 'result=rejected' in diagnostic,diagnostic
                    assert 'source_stars=' in diagnostic and 'shape=5x4' in diagnostic,diagnostic
                    assert diagnostic.count('[placement-v2 ')==3,diagnostic
                    assert 'result=rejected reason=spot action=rotate' in diagnostic,diagnostic
                    assert diagnostic.startswith('previous-session-marker\n') and 'pointer_cell=-2,0' in diagnostic,diagnostic
                    print('PASS UTF-8 placement log appends overlap and rejection snapshots',flush=True)
                print(result,flush=True);break
            if p.poll() is not None:raise RuntimeError(f'Runtime exited {p.returncode}: {result}')
            time.sleep(.2)
        else:raise RuntimeError(f'Timed out: {result}')
    finally:
        if p.poll() is None:p.terminate()
        p.wait(timeout=10)
