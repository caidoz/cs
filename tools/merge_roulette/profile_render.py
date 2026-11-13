"""Opt-in isolated render timings; compare fresh and accumulated combat text caches."""
import argparse
import os
from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser()
parser.add_argument('--label', required=True)
parser.add_argument('--exe', default='proj.win32/Debug.win32/cs_bars.exe')
parser.add_argument('--height', type=int, default=1408)
args = parser.parse_args()
for texts in (0, 512):
    dest = ROOT / 'output/merge-performance' / f'{args.label}-{texts}'
    dest.mkdir(parents=True, exist_ok=True)
    timing = dest / 'timing.txt'
    timing.unlink(missing_ok=True)
    env = os.environ.copy()
    env.update(CS_MERGE_REVIEW='1', CS_MERGE_REVIEW_HEIGHT=str(args.height),
               CS_MERGE_REVIEW_PATH=dest.as_posix()+'/', CS_MERGE_PROFILE_PATH=str(timing),
               CS_MERGE_PROFILE_TEXTS=str(texts))
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest/'stdout.log').open('w') as log:
        proc = subprocess.Popen([str(ROOT/args.exe)],
                                cwd=ROOT/'Resources', env=env, stdout=log, stderr=log, startupinfo=startup)
        try:
            deadline = time.monotonic()+90
            while time.monotonic()<deadline:
                if timing.exists():
                    print(f'{args.label} cached_texts={texts} {timing.read_text().strip()}', flush=True)
                    break
                if proc.poll() is not None:
                    raise RuntimeError(f'Profiler exited {proc.returncode}')
                time.sleep(.2)
            else:
                raise RuntimeError('Render profiler timed out')
        finally:
            if proc.poll() is None:
                proc.terminate()
            proc.wait(timeout=5)
