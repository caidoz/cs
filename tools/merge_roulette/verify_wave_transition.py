"""Exercise real kills, actor layering, castle travel, and incoming enemies."""
import importlib.util
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location('runtime', ROOT / 'tools/items/verify_runtime.py')
runtime = importlib.util.module_from_spec(spec)
spec.loader.exec_module(runtime)
runtime.EXE = ROOT / 'proj.win32/Debug.win32/cs_wave_transition.exe'

for height in (850, 1408):
    folder = f'wave-transition-{height}'
    runtime.run(height, {'CS_WAVE_TRANSITION_REVIEW': '1'}, folder, 'DONE wave transition review', 13)
    checks = (ROOT / 'output/item-series/runtime' / folder / 'checks.log').read_text()
    assert 'PASS monster then allied character and sword then impact effect' in checks
    assert checks.count('PASS defeat travel incoming settle input lock and preserved board') == 3
    print(f'PASS 640x{height}: normal wave, boss arrival, and next castle; actor/effect order and input lock', flush=True)
