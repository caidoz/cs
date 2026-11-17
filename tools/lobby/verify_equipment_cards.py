"""Check native six-column cards, equipped slots and existing equipment actions."""
import os
import argparse
from pathlib import Path
import subprocess
import time

root=Path(__file__).resolve().parents[2]
parser=argparse.ArgumentParser()
parser.add_argument('--exe',default='cs.equipment-cards.exe')
args=parser.parse_args()
for height in (850,1408):
    out=root/f'output/equipment-cards-{height}'
    out.mkdir(parents=True,exist_ok=True)
    trace=out/'phases.log'
    trace.write_text('')
    env=dict(os.environ,CS_PIXEL_EQUIP_REVIEW='1',CS_EQUIPMENT_CARDS_REVIEW='1',
             CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(height))
    startup=subprocess.STARTUPINFO()
    startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow=0
    with (out/'stdout.log').open('w') as log:
        process=subprocess.Popen([str(root/'proj.win32/Debug.win32'/args.exe)],
                                 cwd=root/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
        try:
            deadline=time.monotonic()+60
            while time.monotonic()<deadline:
                result=trace.read_text()
                if 'FAIL' in result:raise RuntimeError(result)
                if 'PASS pixel equipment review complete' in result:
                    for check in ('six separate equipment cards and native backgrounds',
                                  'equipment V2 scrolling and layout','equipment all hero equip and power',
                                  'detail lock touch','detail unlock touch','detail closes to equipment'):
                        assert 'PASS '+check in result,result
                    print(f'PASS {height}: six cards, native background, scrolling, hero equip, lock and detail return',flush=True)
                    break
                if process.poll() is not None:raise RuntimeError(f'Exited {process.returncode}')
                time.sleep(.1)
            else:raise RuntimeError('Equipment review timed out')
        finally:
            if process.poll() is None:process.terminate()
            process.wait(timeout=5)
