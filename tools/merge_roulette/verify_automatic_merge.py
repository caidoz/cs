"""Review automatic equipment/companion chains and their direct flights from the landing cell."""
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
    folder = f'auto-merge-{height}'
    runtime.run(height, {'CS_AUTO_MERGE_REVIEW': '1'}, folder,
                'DONE automatic merge review', 8)
    checks = (runtime.ROOT / 'output/item-series/runtime' / folder / 'checks.log').read_text()
    assert 'PASS equipment chain merges directly from its landing cell' in checks
    assert 'PASS companion chain merges directly from its landing cell' in checks
    assert checks.count('PASS automatic merges consume no lightning and lock input') == 2
