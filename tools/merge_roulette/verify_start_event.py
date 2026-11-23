"""Review the first-battle event and retained free opening reels in native rendering."""
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
    runtime.run(height, {'CS_START_EVENT_REVIEW': '1'}, f'start-event-{height}',
                'DONE start event review', 4)
runtime.run(850, {'CS_START_EVENT_REVIEW': 'skip'}, 'start-event-skip',
            'DONE start event review', 2)
