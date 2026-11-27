"""Capture retouched equipment through the game's real render paths."""
import argparse
import json
import os
from pathlib import Path
import subprocess
import time
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
WORK = ROOT / 'asset_library/work/equipment-retouch-20261123'


def run(exe, name, height, flags, marker, minimum_captures, merge=True):
    dest = WORK / 'runtime' / name
    dest.mkdir(parents=True, exist_ok=True)
    trace = dest / ('checks.log' if merge else 'phases.log')
    trace.write_text('')
    env = {k:v for k,v in os.environ.items() if not (k.startswith('CS_') and ('REVIEW' in k or k.endswith('_TRACE')))}
    if merge:
        env.update(CS_MERGE_REVIEW='1', CS_MERGE_REVIEW_HEIGHT=str(height), CS_MERGE_REVIEW_PATH=dest.as_posix()+'/')
    else:
        env.update(CS_BATTLE_MENU_REVIEW='1', CS_BATTLE_MENU_HEIGHT=str(height), CS_CASTLE_REVIEW_PATH=dest.as_posix()+'/')
    env.update(flags)
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest / 'stdout.log').open('w') as log:
        process = subprocess.Popen([str(exe)], cwd=ROOT/'Resources', env=env,
                                   startupinfo=startup, stdout=log, stderr=log)
        try:
            deadline = time.monotonic()+90
            while time.monotonic() < deadline:
                result = trace.read_text(encoding='utf-8', errors='replace')
                if 'FAIL' in result:
                    raise RuntimeError(result)
                captures = list(dest.glob('*.png'))
                ready = not merge or result.count('PASS capture ') >= len(captures)
                if marker in result and len(captures) >= minimum_captures and ready:
                    try:
                        for path in captures:
                            with Image.open(path) as im:
                                assert im.size == (640, height), (path, im.size)
                                im.verify()
                    except OSError:
                        time.sleep(.15)
                        continue
                    print(f'PASS {name}: {len(captures)} native captures', flush=True)
                    return dict(name=name, height=height, captures=len(captures), passed=True)
                if process.poll() is not None:
                    raise RuntimeError(f'{name}: game exited {process.returncode}; see {dest}')
                time.sleep(.15)
            raise TimeoutError(f'{name}: native review timed out; see {trace}')
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=5)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe', default='cs_equipment_tone.exe')
    args = parser.parse_args()
    exe = ROOT / 'proj.win32/Debug.win32' / args.exe
    results = []
    cases = [
        ('grid-all-225',850,{'CS_GRID_ITEM_REVIEW':'1'},'DONE grid item review',8,True),
        ('held-all-35',850,{'CS_SHARED_SWORD_REVIEW':'1'},'DONE shared sword review',7,True),
        ('costume-combat',850,{'CS_MERGE_COSTUME_REVIEW':'1'},'DONE costume review',1,True),
        ('cannons-all-60',1408,{'CS_CURRENT_CANNON_ICON_REVIEW':'1'},'PASS current cannon icon capture',1,False),
        ('equipment-850',850,{'CS_PIXEL_EQUIP_REVIEW':'1','CS_EQUIPMENT_CARDS_REVIEW':'1'},'PASS pixel equipment review complete',2,False),
        ('equipment-1408',1408,{'CS_PIXEL_EQUIP_REVIEW':'1','CS_EQUIPMENT_CARDS_REVIEW':'1'},'PASS pixel equipment review complete',2,False),
    ]
    for name, height, flags, marker, count, merge in cases:
        results.append(run(exe,name,height,flags,marker,count,merge))
        (WORK / 'runtime-validation.json').write_text(json.dumps(results,indent=2))


if __name__ == '__main__':
    main()
