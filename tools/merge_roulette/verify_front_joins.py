"""Verify closed fronts occlude the old outer frame instead of redrawing it.

Run verify_cover.py and verify_cover.py --reference before this check.
"""
from pathlib import Path
import re
from PIL import Image, ImageChops

ROOT = Path(__file__).resolve().parents[2]
pattern = re.compile(r'front-join castle=(\d+) outer=([\d,-]+) inner=([\d,-]+)')
for height in (850, 1408):
    folder = ROOT / 'output/merge-cover-review' / str(height)
    reference = ROOT / 'output/merge-cover-reference' / str(height)
    metrics = pattern.findall((folder / 'checks.log').read_text())
    assert len(metrics) == 10, metrics
    for castle, outer, inner in metrics:
        x, y, w, h = map(int, outer.split(','))
        ix, iy, iw, ih = map(int, inner.split(','))
        name = f'cover-castle-{int(castle):02}.png'
        actual = Image.open(folder / name).convert('RGB')
        original = Image.open(reference / name).convert('RGB')
        left = (x + ix) // 2
        right = (ix + iw + x + w) // 2
        top = (y + iy) // 2
        bottom = (iy - ih + y - h) // 2
        strips = (
            (left, height - iy + 4, left + 3, height - (iy - ih) - 4),
            (right, height - iy + 4, right + 3, height - (iy - ih) - 4),
            (ix + 8, height - top, ix + iw - 8, height - top + 3),
            (ix + 8, height - bottom, ix + iw - 8, height - bottom + 3),
        )
        covered_edges = 0
        for edge, box in zip(('left', 'right', 'top', 'bottom'), strips):
            diff = ImageChops.difference(actual.crop(box), original.crop(box))
            maximum = max(channel[1] for channel in diff.getextrema())
            covered_edges += maximum > 16
        assert covered_edges >= 3, (height, castle, covered_edges)
    print(f'PASS 640x{height}: all ten fronts cover the old exterior frame')
