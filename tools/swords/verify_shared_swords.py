"""Compare inventory and held swords captured through the actual game renderer."""
import importlib.util
from pathlib import Path
import numpy as np
from PIL import Image, ImageFilter

ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location('runtime', ROOT / 'tools/items/verify_runtime.py')
runtime = importlib.util.module_from_spec(spec)
spec.loader.exec_module(runtime)
runtime.EXE = ROOT / 'proj.win32/Debug.win32/cs_shared_swords.exe'

for height in (850, 1408):
    folder = f'shared-swords-{height}'
    runtime.run(height, {'CS_SHARED_SWORD_REVIEW': '1'}, folder, 'DONE shared sword review', 7)
    for page in range(7):
        image = Image.open(ROOT / 'output/item-series/runtime' / folder / f'shared-sword-{page+1:02d}.png').convert('RGB')
        # The hand anchor can lie between pixels; suppress only that subpixel
        # sampling difference before comparing the silhouette and colour layout.
        image = image.filter(ImageFilter.GaussianBlur(1))
        for row in range(5):
            detail = page * 5 + row
            blade_height = 32 * (2 if detail < 10 else 3 if detail < 25 else 4)
            top = 70 + row * 145
            inventory = np.array(image.crop((98, top-2, 134, top+blade_height+2)), dtype=float)
            # Attachment coordinates round to integer screen pixels. Allow that
            # translation, but require the rendered artwork and proportions to match.
            errors = []
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    held = np.array(image.crop((278+dx, top-2+dy, 314+dx, top+blade_height+2+dy)), dtype=float)
                    errors.append(np.abs(inventory-held).mean())
            assert min(errors) < 6, (height, detail+1, min(errors))
    print(f'PASS 640x{height}: all 35 inventory/held sword silhouettes and colours match', flush=True)
