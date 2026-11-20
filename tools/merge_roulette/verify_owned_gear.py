"""Exercise owned-equipment reel drops using the actual native renderer."""
import argparse
from pathlib import Path
import sys
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'items'))
import verify_runtime as runtime
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--exe',default='cs.exe')
args=parser.parse_args()
runtime.EXE=runtime.ROOT/'proj.win32/Debug.win32'/args.exe
for height in (850,1408):
    runtime.run(height,{'CS_OWNED_GEAR_REVIEW':'1'},f'owned-gear-{height}',
                'DONE owned gear review',1)
