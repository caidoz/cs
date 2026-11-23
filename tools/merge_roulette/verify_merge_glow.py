"""Capture real merges at tiers 2 through 6 and check single mode hides enemy grids."""
import argparse
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'items'))
import verify_runtime as runtime

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--exe', default='cs.exe')
args = parser.parse_args()
runtime.EXE = runtime.ROOT / 'proj.win32/Debug.win32' / args.exe
for height in (850, 1408):
    folder = f'merge-glow-{height}'
    runtime.run(height, {'CS_MERGE_GLOW_REVIEW': '1'}, folder,
                'DONE merge glow review', 5)
    checks = (runtime.ROOT / 'output/item-series/runtime' / folder / 'checks.log').read_text()
    assert checks.count('PASS merge tier increases border glow strength and duration') == 5
    assert 'PASS single mode has no enemy grid panel' in checks
