"""Capture the ten live castle skins and all fifteen regional backgrounds."""
from pathlib import Path
import os
import subprocess
import time
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
for stage in range(1,11):
    folder = ROOT / f'Resources/res/castle_mist_v2/{stage:02}'
    for path in folder.glob('*.png'):
        with Image.open(path) as image:
            image.verify()
    assert len(list(folder.glob('*.png'))) == (11 if stage==1 else 10)
    with Image.open(folder/'cover.png') as image:
        assert image.size == (1000,610)
        assert image.convert('RGBA').getchannel('A').getextrema() == (255,255)
print('PASS 101 assets and ten fully opaque wall panels', flush=True)
for height in (850,1408):
    dest = ROOT / 'output/mist-live-review' / str(height)
    dest.mkdir(parents=True,exist_ok=True)
    trace = dest/'checks.log'
    trace.unlink(missing_ok=True)
    env = os.environ.copy()
    env.update(CS_MERGE_REVIEW='1',CS_MIST_RESOURCE_REVIEW='1',
        CS_MERGE_REVIEW_HEIGHT=str(height),CS_MERGE_REVIEW_PATH=dest.as_posix()+'/')
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest/'stdout.log').open('w') as log:
        process = subprocess.Popen([str(ROOT/'proj.win32/Debug.win32/cs_bars.exe')],
            cwd=ROOT/'Resources',env=env,startupinfo=startup,stdout=log,stderr=log)
        try:
            end = time.monotonic()+180
            while time.monotonic()<end:
                text = trace.read_text() if trace.exists() else ''
                if 'FAIL' in text:
                    raise RuntimeError(text)
                if 'DONE mist resource review' in text and text.count('PASS capture ')==35:
                    assert text.count('PASS mist resource parts')==35
                    paths = [dest/f'castle-{c:02}-{mode}.png' for c in range(1,11)
                             for mode in ('interior','battle')]
                    paths += [dest/f'background-{r:02}.png' for r in range(1,16)]
                    for path in paths:
                        with Image.open(path) as image:
                            assert image.size == (640,height)
                            image.verify()
                    print(f'PASS 640x{height}: 20 castle states and 15 backgrounds',flush=True)
                    break
                if process.poll() is not None:
                    raise RuntimeError('Preview exited')
                time.sleep(.2)
            else:
                raise RuntimeError('Review timeout')
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=5)
gallery = ROOT/'output/mist-live-review/index.html'
gallery.write_text('<!doctype html><meta charset="utf-8"><title>Live castle resources</title>'
    '<style>body{background:#20282b;color:#e7dcc7;font:18px sans-serif}section{display:flex;gap:12px;flex-wrap:wrap}img{width:310px;max-width:46vw}h2{margin-top:40px}</style>'
    + ''.join(f'<h2>성 {c}</h2><section><img src="1408/castle-{c:02}-interior.png"><img src="1408/castle-{c:02}-battle.png"></section>' for c in range(1,11))
    + '<h2>지역별 배경</h2><section>'
    + ''.join(f'<img loading="lazy" src="1408/background-{r:02}.png">' for r in range(1,16))+'</section>',encoding='utf-8')
