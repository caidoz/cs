"""Capture every castle and assert equal hull width and uniform art transforms."""
import argparse
import sys
from pathlib import Path

root = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(root / 'tools/items'))
import verify_runtime as runtime

parser = argparse.ArgumentParser()
parser.add_argument('--exe', default='cs.castle-proportions.exe')
args = parser.parse_args()
runtime.EXE = root / 'proj.win32/Debug.win32' / args.exe
for height in (850, 1408):
    runtime.run(height, {'CS_CASTLE_PROPORTIONS_REVIEW': '1'},
                f'castle-proportions-{height}', 'DONE castle proportions review', 10)
