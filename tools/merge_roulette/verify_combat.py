"""Exercise actual merged crew, native bullet/hero presentation, and inset bars."""
import argparse
import os
from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).resolve().parents[2]


def verify(exe, height, turn=False, arrival=False):
    dest = ROOT / ('output/merge-arrival-review' if arrival else 'output/merge-turn-review' if turn else 'output/merge-combat-review') / str(height)
    dest.mkdir(parents=True, exist_ok=True)
    trace = dest / 'checks.log'
    trace.unlink(missing_ok=True)
    env = os.environ.copy()
    env.update(CS_MERGE_REVIEW='1', CS_MERGE_COMBAT_REVIEW='1',
               CS_MERGE_REVIEW_HEIGHT=str(height), CS_MERGE_REVIEW_PATH=dest.as_posix() + '/')
    if turn:
        env['CS_MERGE_TURN_REVIEW'] = '1'
    if arrival:
        env['CS_MERGE_ARRIVAL_REVIEW'] = '1'
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (dest / 'stdout.log').open('w') as log:
        process = subprocess.Popen([str(exe)], cwd=ROOT / 'Resources', env=env,
                                   stdout=log, stderr=log, startupinfo=startup)
        try:
            deadline = time.monotonic() + 120
            while time.monotonic() < deadline:
                text = trace.read_text() if trace.exists() else ''
                if 'FAIL' in text:
                    raise RuntimeError(text)
                if arrival and 'DONE merge arrival review' in text and 'arrival-07-spin-ready.png' in text:
                    for check in ('stopped reels do not reveal pending crew on deck',
                                  'grid landing precedes rotating deck arrival',
                                  'normal spin also lands before rotating crew onto deck'):
                        assert 'PASS ' + check in text, check
                    for name in ('arrival-01-stopped-reels', 'arrival-02-grid-landed',
                                 'arrival-03-deck-spin', 'arrival-04-opening-ready',
                                 'arrival-05-spin-grid-landed', 'arrival-06-spin-deck-rotation',
                                 'arrival-07-spin-ready'):
                        assert (dest / (name + '.png')).is_file(), name
                    print(f'PASS 640x{height}: both opening and normal draws stop, land on grid, then rotate onto deck', flush=True)
                    return
                if turn and 'DONE merge turn review' in text and 'turn-06-wave15-final-boss.png' in text:
                    for check in ('hero crew and enemy neutral motions loop',
                                  'enemy hits only after all allied actions complete',
                                  'turn end follows enemy recovery',
                                  'enemy counterattack then turn end unlocks controls',
                                  'real bosses at waves 5 10 15 with increasing health'):
                        assert 'PASS ' + check in text, check
                    for name in ('turn-01-idle-progress', 'turn-02-enemy-counterattack',
                                 'turn-03-turn-end', 'turn-04-wave5-boss',
                                 'turn-05-wave10-boss', 'turn-06-wave15-final-boss'):
                        assert (dest / (name + '.png')).is_file(), name
                    print(f'PASS 640x{height}: neutral loops, allied/enemy/end sequence, single counter hit and 15-wave boss header', flush=True)
                    return
                if not turn and not arrival and 'DONE merge combat review' in text and 'combat-04-complete.png' in text:
                    for check in ('every deployed crew including merged crew is drawn',
                                  'projectile forms above caster head before launch',
                                  'visible formation phase precedes projectile flight',
                                  'actual impact damage floats above target',
                                  'defense gain floats while guard bar animates',
                                  'companion generates native roulette projectile',
                                  'companion requests full native hero skill motion',
                                  'all merged crew remain after combat', 'exactly one impact per actor'):
                        assert 'PASS ' + check in text, check
                    for name in ('combat-01-formation-bars', 'combat-02a-bullet-formation', 'combat-02-native-bullet',
                                 'combat-03-requested-hero-skill', 'combat-04-complete',
                                 'combat-05-guard-charge', 'combat-06-damage-number'):
                        assert (dest / (name + '.png')).is_file(), name
                    print(f'PASS 640x{height}: merge/deck identities, motion completion, bullet impact, hero request and bar captures', flush=True)
                    return
                if process.poll() is not None:
                    raise RuntimeError(f'Preview exited {process.returncode}: {text}')
                time.sleep(.2)
            raise RuntimeError('Combat review timed out: ' + text)
        finally:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=5)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--exe', default='proj.win32/Debug.win32/cs_review.exe')
    parser.add_argument('--turn', action='store_true')
    parser.add_argument('--arrival', action='store_true')
    args = parser.parse_args()
    for height in (850, 1408):
        verify((ROOT / args.exe).resolve(), height, args.turn, args.arrival)
