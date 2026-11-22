"""Exercise local lightning through real spin, attack and cannon touch handlers."""
import argparse
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'items'))
import verify_runtime as runtime

parser = argparse.ArgumentParser()
parser.add_argument('--exe', default='cs.exe')
args = parser.parse_args()
runtime.EXE = runtime.ROOT / 'proj.win32/Debug.win32' / args.exe
for height in (850, 1408):
    folder = f'battle-lightning-{height}'
    runtime.run(height, {'CS_BATTLE_ENERGY_REVIEW': '1'}, folder,
                'DONE battle lightning review', 4)
    log = (runtime.ROOT / 'output/item-series/runtime' / folder / 'checks.log').read_text()
    for check in ('spin spends one local lightning', 'attack spends one local lightning',
                  'cannon spends one local lightning', 'rejected and empty actions',
                  'kill refills five local lightning'):
        assert 'PASS ' + check in log, log
