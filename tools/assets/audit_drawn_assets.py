"""Audit texture dependencies that reach the actual screen, not boot preloads.

Run --capture to exercise production screens and real equipment/crew mappings.
Offscreen scratch buffers count only if another drawn texture uses them.
This report is evidence for a reviewed production allowlist, not an automatic
claim that an unobserved future variant is unused.
"""
import argparse
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed
import json
import os
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
DEST = ROOT / 'output/production-resource-audit'
CASES = {
    'castles-backgrounds': ('tools/art/verify_mist_resources.py', []),
    'menus': ('tools/lobby/verify_menu_scenes.py', []),
    'equipment': ('tools/lobby/verify_equipment_cards.py', []),
    'hero-backgrounds': ('tools/lobby/verify_hero_backgrounds.py', ['--debug']),
    'rewards': ('tools/merge_roulette/verify_reward_reveal.py', []),
    'turrets': ('tools/merge_roulette/verify_turret_attack.py', []),
    'currency-shop': ('tools/lobby/verify_currency_shop.py', []),
    'crew-detail': ('tools/lobby/verify_crew_detail.py', []),
    'box-info': ('tools/lobby/verify_box_info.py', []),
    'gear-variants': ('--native', ['CS_GRID_ITEM_REVIEW', 'DONE grid item review', '8']),
    'crew-variants': ('--native', ['CS_GRID_CREW_SCALE_REVIEW', 'DONE grid crew scale review', '4']),
    'held-weapons': ('--native', ['CS_SHARED_SWORD_REVIEW', 'DONE shared sword review', '7']),
    'monster-parts': ('--native', ['CS_MONSTER_PARTS_REVIEW', 'DONE monster parts review', '5']),
    'secondary-menus': ('--menus', []),
    'siege': ('--native', ['CS_MERGE_SIEGE_REVIEW', 'DONE PVP controls review', '1']),
}


def run_case(name, exe):
    script, extra = CASES[name]
    env = os.environ.copy()
    for key in list(env):
        if key.startswith('CS_') and ('REVIEW' in key or 'AUDIT' in key): env.pop(key)
    env['CS_ASSET_DRAW_AUDIT'] = str(DEST / (name+'.tsv'))
    env['CS_ASSET_AUDIT'] = str(DEST / (name+'-loads.tsv'))
    for path in (Path(env['CS_ASSET_DRAW_AUDIT']), Path(env['CS_ASSET_AUDIT'])): path.unlink(missing_ok=True)
    args = [sys.executable, str(Path(__file__).resolve()), '--native-case', name, '--exe', exe] if script.startswith('--') else [sys.executable, str(ROOT/script), '--exe', exe, *extra]
    with (DEST/(name+'.log')).open('w', encoding='utf-8') as log:
        result = subprocess.run(args, cwd=ROOT, env=env, stdout=log, stderr=log, timeout=300)
    if result.returncode: raise RuntimeError(f'{name} failed: {DEST/(name+".log")}')
    print('PASS actual draw audit:',name,flush=True)


def native_case(name, exe):
    if name == 'secondary-menus':
        import time
        out=DEST/name;out.mkdir(exist_ok=True)
        trace=out/'phases.log';trace.unlink(missing_ok=True)
        env=dict(os.environ,CS_RESOURCE_MENUS_REVIEW='1',CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT='850')
        startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
        with (out/'native.log').open('w') as log:
            process=subprocess.Popen([str(ROOT/'proj.win32/Debug.win32'/exe)],cwd=ROOT/'Resources',env=env,stdout=log,stderr=log,startupinfo=startup)
            try:
                deadline=time.monotonic()+100
                while time.monotonic()<deadline:
                    text=trace.read_text() if trace.exists() else ''
                    if 'FAIL' in text: raise RuntimeError(text)
                    if 'DONE resource menus review' in text:
                        assert text.count('PASS resource menu capture')==3,text
                        return
                    if process.poll() is not None: raise RuntimeError('Secondary menu process exited')
                    time.sleep(.2)
                raise TimeoutError('Secondary menus')
            finally:
                if process.poll() is None:process.terminate()
                process.wait(timeout=10)
    else:
        sys.path.insert(0,str(ROOT/'tools/items'))
        import verify_runtime as runtime
        runtime.EXE=ROOT/'proj.win32/Debug.win32'/exe
        flag, done, captures = CASES[name][1]
        flags = {flag:'1'}
        if name == 'siege': flags['CS_MERGE_PVP_CONTROLS_REVIEW'] = '1'
        runtime.run(850,flags,'resource-audit-'+name,done,int(captures))


def read_usage():
    used=defaultdict(set)
    sessions=0
    for path in sorted(DEST.glob('*.tsv')):
        if path.name.endswith('-loads.tsv'): continue
        if path.stem not in CASES: continue
        names=defaultdict(set);edges=defaultdict(set)
        def flush():
            reachable={0};todo=[0]
            while todo:
                for child in edges[todo.pop()]:
                    if child not in reachable:reachable.add(child);todo.append(child)
            for node in reachable:
                for name in names[node]:used[name].add(path.stem)
        for line in path.read_text().splitlines()+['BEGIN']:
            parts=line.split('\t')
            if parts[0]=='BEGIN':
                flush();names=defaultdict(set);edges=defaultdict(set);sessions+=1
            elif parts[0]=='NAME':names[int(parts[1])].add(parts[2])
            elif parts[0]=='EDGE':edges[int(parts[1])].add(int(parts[2]))
    return used,sessions


def report():
    used,sessions=read_usage()
    catalog=json.loads((ROOT/'content/runtime-assets.json').read_text())
    rows=[]
    for asset in catalog['assets']:
        rows.append(dict(asset, bytes=(ROOT/asset['source']).stat().st_size,
                         drawn_in=sorted(used.get(asset['target'],[]))))
    data={'sessions':sessions,'drawn_files':sum(bool(a['drawn_in']) for a in rows),
          'drawn_bytes':sum(a['bytes'] for a in rows if a['drawn_in']),
          'assets':rows}
    (ROOT/'reports/runtime-assets/actual-draw-usage.json').write_text(json.dumps(data,indent=2))
    print(f"SCREEN-REACHABLE {data['drawn_files']} files, {data['drawn_bytes']/2**20:.1f} MiB",flush=True)


if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--capture',action='store_true')
    parser.add_argument('--exe',default='cs.draw-audit.exe')
    parser.add_argument('--native-case',choices=CASES)
    args=parser.parse_args();DEST.mkdir(parents=True,exist_ok=True)
    if args.native_case:native_case(args.native_case,args.exe)
    else:
        if args.capture:
            with ThreadPoolExecutor(max_workers=2) as executor:
                tasks=[executor.submit(run_case,name,args.exe) for name in CASES]
                for task in as_completed(tasks):task.result()
        report()
