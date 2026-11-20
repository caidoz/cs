"""Capture native fixed-size rewards, 1/3/12/30 entries and six star tiers."""
import importlib.util
import argparse
from pathlib import Path

root=Path(__file__).resolve().parents[2]
spec=importlib.util.spec_from_file_location('runtime',root/'tools/items/verify_runtime.py')
runtime=importlib.util.module_from_spec(spec)
spec.loader.exec_module(runtime)
parser=argparse.ArgumentParser()
parser.add_argument('--exe',default='cs.reward-reveal.exe')
args=parser.parse_args()
runtime.EXE=root/'proj.win32/Debug.win32'/args.exe
for height in (850,1408):
    folder=f'reward-reveal-{height}'
    runtime.run(height,{'CS_REWARD_REVEAL_REVIEW':'1'},folder,'DONE reward reveal review',13 if height==850 else 12)
    log=(root/'output/item-series/runtime'/folder/'checks.log').read_text()
    assert log.count('PASS fixed card size independent of count')==4,log
    assert log.count('PASS confirm closes revealed rewards')==4,log
    assert 'PASS sample mixes all six native star tiers' in log,log
    assert 'PASS height-dependent scrolling' in log,log
    assert 'PASS skip reveals without dismissing rewards' in log,log
    if height==850:assert 'PASS drag returns to first row' in log,log
    print(f'PASS {height}: fixed native cards, responsive rows, mixed tiers, drag and confirmation',flush=True)
