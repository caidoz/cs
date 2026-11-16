"""Exercise actual render routes and capture the new textures in the game."""
from pathlib import Path
import argparse
import os
import subprocess
import time
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
EXE = ROOT / 'proj.win32/Debug.win32/cs_items.exe'


def run(height, flags, folder, done, captures):
    dest = ROOT / 'output/item-series/runtime' / folder
    dest.mkdir(parents=True, exist_ok=True)
    trace = dest / 'checks.log'
    trace.unlink(missing_ok=True)
    env = os.environ.copy()
    for key in list(env):
        if key.startswith('CS_') and ('REVIEW' in key or key.endswith('_TRACE')):
            env.pop(key)
    env.update(CS_MERGE_REVIEW='1', CS_MERGE_REVIEW_HEIGHT=str(height),
               CS_MERGE_REVIEW_PATH=dest.as_posix() + '/', **flags)
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest / 'stdout.log').open('w') as log:
        process = subprocess.Popen([str(EXE)], cwd=ROOT / 'Resources', env=env,
                                   startupinfo=startup, stdout=log, stderr=log)
        try:
            deadline = time.monotonic() + 180
            while time.monotonic() < deadline:
                text = trace.read_text(encoding='utf-8') if trace.exists() else ''
                if 'FAIL' in text:
                    raise RuntimeError(text)
                if done in text and text.count('PASS capture ') == captures:
                    for line in text.splitlines():
                        if line.startswith('PASS capture '):
                            with Image.open(line.removeprefix('PASS capture ')) as image:
                                assert image.size == (640, height)
                                image.verify()
                    print(f'PASS {folder}: {captures} live captures', flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError(f'{folder}: preview exited; see {dest}')
                time.sleep(.2)
            else:
                raise RuntimeError(f'{folder}: preview timed out')
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=5)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--catalog-only', action='store_true')
    options = parser.parse_args()
    run(850, {'CS_ITEM_SERIES_REVIEW': '1'}, 'catalog', 'DONE item series review', 10)
    if not options.catalog_only:
        for height in (850, 1408):
            run(height, {'CS_MIST_RESOURCE_REVIEW': '1'}, str(height), 'DONE mist resource review', 35)
