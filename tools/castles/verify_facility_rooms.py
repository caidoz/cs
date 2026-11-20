"""Verify the shared four-theme/six-state atlas and its live castle rendering."""
import hashlib
import importlib.util
import argparse
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser()
parser.add_argument('--exe', default='cs.four-rooms-review.exe')
options = parser.parse_args()
for castle in range(1, 11):
    with Image.open(ROOT / f'Resources/res/castle_four_rooms_v5-rooms-{castle:02d}.png') as image:
        frames = []
        for room in range(4):
            levels = []
            for level in range(6):
                frame = image.crop((image.width*room//4, image.height*level//6,
                                    image.width*(room+1)//4, image.height*(level+1)//6))
                levels.append(hashlib.sha256(frame.tobytes()).hexdigest())
            assert len(set(levels)) == 6, (castle, room, 'duplicate upgrade artwork')
            frames.append(levels[0])
        assert len(set(frames)) == 4, (castle, 'duplicate facility themes')
print('PASS ten castles: four distinct facilities, base plus five distinct upgrade drawings each', flush=True)

spec = importlib.util.spec_from_file_location('runtime', ROOT / 'tools/items/verify_runtime.py')
runtime = importlib.util.module_from_spec(spec)
spec.loader.exec_module(runtime)
runtime.EXE = ROOT / 'proj.win32/Debug.win32' / options.exe
for height in (850, 1408):
    folder = f'facility-rooms-{height}'
    runtime.run(height, {'CS_FACILITY_ROOMS_REVIEW': '1', 'CS_FOUR_ROOM_WALKERS_REVIEW': '1'}, folder, 'DONE facility rooms review', 70)
    log = (ROOT / 'output/item-series/runtime' / folder / 'checks.log').read_text()
    assert log.count('PASS four themed rooms use independent saved levels and joined edges') == 70
    print(f'PASS 640x{height}: all ten castles, six visual stages, mixed room levels and contiguous room bounds', flush=True)
