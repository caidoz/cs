"""Capture every detailed exterior in the game, with and without board contents."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'items'))
import verify_runtime as runtime

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--exe', default='cs.exe')
args = parser.parse_args()
runtime.EXE = runtime.ROOT / 'proj.win32/Debug.win32' / args.exe

def review(case):
    stage, height = case
    folder = f'detailed-cover-{stage:02}-{height}'
    runtime.run(height, {'CS_COVER_STYLE_REVIEW': '1', 'CS_COVER_STYLE_STAGE': str(stage)},
                folder, 'DONE cover style review', 2)
    checks = (runtime.ROOT / 'output/item-series/runtime' / folder / 'checks.log').read_text()
    assert 'PASS dimensional cover rendered with native grid and units' in checks

with ThreadPoolExecutor(max_workers=2) as pool:
    list(pool.map(review, [(stage,850) for stage in range(1,11)]+[(2,1408)]))
