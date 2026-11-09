"""Exercise the real input path in isolated storage, at both screen ratios."""
import argparse
import os
from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).resolve().parents[2]


def verify(executable: Path, height: int):
    folder = ROOT / 'output' / 'merge-roulette' / str(height)
    folder.mkdir(parents=True, exist_ok=True)
    for name in ('checks.log', 'crash.log'):
        (folder / name).unlink(missing_ok=True)
    env = os.environ.copy()
    env.update(CS_MERGE_REVIEW='1', CS_MERGE_REVIEW_HEIGHT=str(height),
               CS_MERGE_REVIEW_PATH=folder.as_posix() + '/')
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (folder / 'stdout.log').open('w', encoding='utf-8') as log:
        process = subprocess.Popen([str(executable)], cwd=executable.parent,
                                   env=env, stdout=log, stderr=subprocess.STDOUT,
                                   startupinfo=startup)
        try:
            deadline = time.monotonic() + 75
            while time.monotonic() < deadline:
                trace = (folder / 'checks.log').read_text() if (folder / 'checks.log').exists() else ''
                if 'FAIL' in trace:
                    raise RuntimeError(trace)
                if 'DONE' in trace and '05-castle10.png' in trace:
                    for name in ('00-opening-spin', '00-opening-flight', '00-opening-land',
                                 '01-families', '02-inventory', '03-launch', '04-exchange', '05-castle10', '06-heart-spend'):
                        if not (folder / (name + '.png')).is_file():
                            raise RuntimeError('missing capture ' + name)
                    print(f'PASS {640}x{height}: 64px cells, heart blink, retained actions, three-cell guard, discard, start/continue, nine captures', flush=True)
                    return
                if process.poll() is not None:
                    crash = (folder / 'crash.log').read_text() if (folder / 'crash.log').exists() else ''
                    raise RuntimeError(f'preview exited {process.returncode}: {crash}')
                time.sleep(.2)
            raise RuntimeError('preview timed out: ' + str(folder))
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=5)


def compare_bottom():
    from PIL import Image, ImageChops
    traces = {}
    for height in (850, 1408):
        lines = (ROOT / 'output/merge-roulette' / str(height) / 'checks.log').read_text().splitlines()
        traces[height] = {line.split()[1]: line.split()[2:] for line in lines if line.startswith('LAYOUT ')}
    for name in ('01-families', '02-inventory', '05-castle10'):
        if name not in traces[850] or traces[850].get(name) != traces[1408].get(name):
            raise RuntimeError('UI rectangle coordinates differ between ratios: ' + name)
        short = Image.open(ROOT / 'output/merge-roulette/850' / (name + '.png')).convert('RGB')
        tall = Image.open(ROOT / 'output/merge-roulette/1408' / (name + '.png')).convert('RGB')
        short = short.crop((0, short.height - 592, 640, short.height))
        tall = tall.crop((0, tall.height - 592, 640, tall.height))
        diff = ImageChops.difference(short, tall)
        # CMF/atlas sprite edges can round differently in the two GL viewports.
        # The static heart bar and action buttons must still match pixel-for-pixel.
        footer = diff.crop((0, 462, 640, 592))
        if footer.getbbox():
            raise RuntimeError('bottom-aligned UI differs between ratios: ' + name)
    print('PASS bottom UI alignment at both ratios and castles 1/10; heart bar/buttons pixel-identical', flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--exe', default='proj.win32/Debug.win32/cs.exe')
    args = parser.parse_args()
    for height in (850, 1408):
        verify((ROOT / args.exe).resolve(), height)
    compare_bottom()
