"""Verify resume/decline through the lobby popup's actual touch handlers."""
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
    folder = f'resume-prompt-{height}'
    runtime.run(height, {'CS_RESUME_PROMPT_REVIEW': '1'}, folder,
                'DONE resume prompt review', 2)
    checks = (runtime.ROOT / 'output/item-series/runtime' / folder / 'checks.log').read_text()
    assert 'PASS explicit resume restores exact run without energy charge' in checks
    assert 'PASS decline clears run and preserves already-paid energy' in checks
