"""Extract only the original lobby controls, using their original runtime masks."""
from pathlib import Path
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'asset_library/work/legacy-lobby-controls'
OUT.mkdir(parents=True, exist_ok=True)
source = Image.open(ROOT / 'asset_library/reference/Resources/res/merge_castle_original/reference.png').convert('RGBA')
controls = {
    'legacy-lobby-start.png': [(294,1090),(315,1063),(516,1063),(514,1047),(539,1057),(548,1037),(558,1057),(583,1047),(577,1063),(779,1063),(800,1085),(800,1165),(778,1187),(316,1187),(294,1165)],
    'legacy-lobby-dock.png': [(76,1314),(101,1297),(460,1297),(483,1284),(530,1284),(531,1275),(550,1285),(574,1284),(596,1297),(984,1297),(1017,1317),(1017,1415),(993,1438),(103,1438),(76,1414)],
}
for name, polygon in controls.items():
    mask = Image.new('L', source.size)
    ImageDraw.Draw(mask).polygon(polygon, fill=255)
    result = source.copy()
    result.putalpha(mask)
    bounds = mask.getbbox()
    result.crop(bounds).save(OUT / name)
    print(name, bounds)
