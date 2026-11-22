"""Capture the native turn-based treasure contents at both supported review sizes."""
from pathlib import Path
import os
import argparse
import subprocess
import time

root=Path(__file__).resolve().parents[2]
parser=argparse.ArgumentParser();parser.add_argument('--exe',default='cs.box-info.exe');parser.add_argument('--purchase-flow',action='store_true');args=parser.parse_args()
for height in (850,1408):
    out=root/f'output/box-info/{height}'
    out.mkdir(parents=True,exist_ok=True)
    trace=out/'phases.log'
    trace.write_text('')
    env=dict(os.environ,CS_BOX_INFO_REVIEW='1',CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT=str(height))
    if args.purchase_flow:env['CS_SHOP_PURCHASE_FLOW_REVIEW']='1'
    startup=subprocess.STARTUPINFO()
    startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow=0
    with (out/'run.log').open('w') as log:
        process=subprocess.Popen([str(root/'proj.win32/Debug.win32'/args.exe)],cwd=root/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
        try:
            deadline=time.monotonic()+80
            while time.monotonic()<deadline:
                result=trace.read_text()
                if 'FAIL' in result:raise RuntimeError(result)
                if 'DONE' in result:
                    assert result.count('PASS box capture')==(7 if args.purchase_flow else 3),result
                    assert 'PASS sparse commands use live rectangles and reset ignores stale hits' in result,result
                    assert 'PASS six loot tiers exact odds weighted variants no energy monotonic gold' in result,result
                    assert 'PASS 750 separate equipment grow sort save and reload beyond legacy storage' in result,result
                    assert 'PASS extended inventory equipment selection for all heroes' in result,result
                    assert 'PASS product opens details without charging' in result,result
                    if args.purchase_flow:
                        assert 'PASS purchase confirms then shows granted rewards' in result,result
                        assert 'PASS common reveal closes without duplicate grants' in result,result
                        assert 'PASS original fall open cards summary flow' in result,result
                        assert 'PASS original reveal preserves all granted item instances and counts' in result,result
                        assert 'PASS real touch drag scrolls probability popup' in result,result
                        assert 'PASS probability last card visible and bottom survives parent render' in result,result
                        assert 'PASS probability close restores shop scroll' in result,result
                    assert 'PASS touch' in result,result
                    print(f'PASS {height}: top, bottom, and insufficient-currency detail access',flush=True)
                    break
                if process.poll() is not None:raise RuntimeError(f'Exited {process.returncode}')
                time.sleep(.1)
            else:raise RuntimeError('Capture timed out')
        finally:
            if process.poll() is None:process.terminate()
            try:process.wait(timeout=10)
            except subprocess.TimeoutExpired:
                process.kill()
                process.wait(timeout=10)
