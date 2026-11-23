"""Exercise quit/cancel through real touch handlers, including a paused attack."""
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
    folder = f'exit-confirm-{height}'
    runtime.run(height, {'CS_EXIT_PROMPT_REVIEW': '1'}, folder,
                'DONE exit confirmation review', 2)
    checks = (runtime.ROOT / 'output/item-series/runtime' / folder / 'checks.log').read_text()
    for check in ('exit opens confirmation during attack', 'confirmation pauses exact battle state',
                  'cancel returns directly to unchanged battle without cover or energy charge',
                  'abandon clears run and returns to lobby without refund'):
        assert 'PASS ' + check in checks
