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
                    for check in ('PASS spin results automatically fly into inventory', 'PASS landing locks input without extra heart cost',
                                  'PASS all three reel symbols land separately without automatic merge',
                                  'PASS dragging clubs merges on full board into one 64px tile without heart cost',
                                  'PASS slot gears rotate during spin', 'PASS slot gears decelerate and stop with reels',
                                  'PASS slot gears stay still during attack',
                                  'PASS nine-column castle retains exact 64px cells',
                                  'PASS large result waits safely then flies automatically when space is freed',
                                  'PASS pending results resume with identical landing and no duplicate reward'):
                        assert check in trace,check
                    print(f'PASS {640}x{height}: automatic result flight, counter-rotating gears, 64px cells, hearts, retained actions, three-cell guard and resume', flush=True)
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
    for name in ('01-families', '02-inventory', '05-castle10','10-castle5-nine-columns'):
        if name not in traces[850] or traces[850].get(name) != traces[1408].get(name):
            raise RuntimeError('UI rectangle coordinates differ between ratios: ' + name)
        short = Image.open(ROOT / 'output/merge-roulette/850' / (name + '.png')).convert('RGB')
        tall = Image.open(ROOT / 'output/merge-roulette/1408' / (name + '.png')).convert('RGB')
        short = short.crop((0, short.height - 592, 640, short.height))
        tall = tall.crop((0, tall.height - 592, 640, tall.height))
        diff = ImageChops.difference(short, tall)
        # CMF/atlas sprite edges can round differently in the two GL viewports.
        # Procedural widgets match exactly. Generated textures use linear GL
        # filtering; different viewport heights can vary their samples slightly.
        # Compare opaque faces, excluding transparent flourishes over scenery.
        values=list(map(int,traces[850][name]));hx,hy,hw,hh=values[12:16]
        for rect in ((hx+10,592-hy+9,hx+hw-10,592-hy+hh-9),(311,545,329,560)):
            if diff.crop(rect).getbbox():
                raise RuntimeError('bottom-aligned UI differs between ratios: ' + name + ' ' + str(rect))
        from PIL import ImageStat
        for rect in ((92,540,270,565),(365,540,546,565)):
            area=diff.crop(rect);stat=ImageStat.Stat(area)
            if max(stat.mean)>2 or max(top for low,top in area.getextrema())>16:
                raise RuntimeError('button face shifted between ratios: '+name+' '+str(rect))
    print('PASS identical bottom UI geometry at both ratios and castles 1/10; exact heart/OR pixels, button faces within GL filtering tolerance', flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--exe', default='proj.win32/Debug.win32/cs.exe')
    args = parser.parse_args()
    for height in (850, 1408):
        verify((ROOT / args.exe).resolve(), height)
    compare_bottom()
