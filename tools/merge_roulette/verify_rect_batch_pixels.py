"""Compare batched widgets with CS_MERGE_SLOW_RECTS native-render captures."""
from pathlib import Path
from PIL import Image, ImageChops

ROOT = Path(__file__).resolve().parents[2]
for height in (850, 1408):
    name = 'vitals-02-native-bars-ten-hearts.png'
    fast = Image.open(ROOT / 'output/merge-native-vitals-review' / str(height) / name).convert('RGB')
    slow = Image.open(ROOT / 'output/merge-native-vitals-slow-review' / str(height) / name).convert('RGB')
    base_center = ((1445 - 83) * 640 / 1089 + 40 + 96) / 2
    lift = (height - 850) / (1408 - 850) * (704 - base_center)
    regions = {
        'header': (122, 10, 520, 85),
        'hearts': (148, int(height - 850 - lift + 700), 492, int(height - 850 - lift + 731)),
        'button': (360, height - 58, 558, height - 18),
    }
    for widget, box in regions.items():
        difference = ImageChops.difference(fast.crop(box), slow.crop(box))
        assert all(maximum == 0 for minimum, maximum in difference.getextrema()), (height, widget)
    print(f'PASS 640x{height}: batched header, hearts, and button pixels exactly match native rectangles')
