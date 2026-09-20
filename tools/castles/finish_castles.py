"""Normalize restored castle sprites to the reference chart's relative heights.

Input: output/castles/generation.json with built-in imagegen output paths.
Keep full-resolution generated originals in raw/ and write ready-to-use RGBA PNGs.
"""
from pathlib import Path
import json
import shutil
import zipfile
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'output/castles'
# Approximate silhouette heights in the supplied 1983x793 progression chart.
REFERENCE_HEIGHTS = [139, 212, 254, 293, 317, 350, 423, 431, 460, 528]


def finish():
    inputs = json.loads((OUT/'generation.json').read_text(encoding='utf-8'))
    assert len(inputs) == 10
    (OUT/'raw').mkdir(exist_ok=True)
    records = []
    for item in inputs:
        n = item['id']
        source = Path(item['path'])
        shutil.copy2(source, OUT/'raw'/f'castle{n}.png')
        image = Image.open(source).convert('RGBA')
        alpha = image.getchannel('A')
        if alpha.getextrema()[0] != 0:
            raise ValueError(f'castle{n}: imagegen output has no transparent background')
        # Ignore almost invisible isolated pixels when measuring the silhouette.
        # Keep the original alpha (including soft glows) within a small guard band.
        visible = alpha.point(lambda value: 255 if value > 4 else 0).getbbox()
        if visible is None:
            raise ValueError(f'castle{n}: empty sprite')
        box = (max(0,visible[0]-4), max(0,visible[1]-4),
               min(image.width,visible[2]+4), min(image.height,visible[3]+4))
        cut = image.crop(box)
        height = round(2040 * REFERENCE_HEIGHTS[n] / REFERENCE_HEIGHTS[-1])
        width = round(cut.width * height / cut.height)
        if width > 1016:
            if n == 9:
                raise ValueError(f'castle{n}: silhouette too wide ({width}x{height}); restore a narrower portrait')
            # Keep the artwork's proportions; broad intermediate bases must also
            # fit the largest sprite's width instead of being squeezed sideways.
            height = round(height * 1016 / width)
            width = 1016
        cut = cut.resize((width,height),Image.Resampling.LANCZOS)
        size = (1024,2048) if n == 9 else (width+8,height+8)
        result = Image.new('RGBA',size)
        result.paste(cut,((size[0]-width)//2,size[1]-height-4))
        filename = f'castle{n}.png'
        result.save(OUT/filename,optimize=True)
        records.append(dict(id=n,file=filename,width=size[0],height=size[1],
                            artWidth=width,artHeight=height,relativeHeight=height/2040,
                            referenceRelativeHeight=REFERENCE_HEIGHTS[n]/528))
    (OUT/'sizes.json').write_text(json.dumps(records,indent=2)+'\n',encoding='utf-8')
    # One common scale and baseline show the actual progression, not equal-size thumbnails.
    scale=.27
    widths=[round(r['width']*scale) for r in records]
    preview=Image.new('RGB',(sum(widths)+11*16,620),'#172937')
    draw=ImageDraw.Draw(preview)
    x=16
    for r,w in zip(records,widths):
        h=round(r['height']*scale)
        im=Image.open(OUT/r['file']).resize((w,h),Image.Resampling.LANCZOS)
        preview.paste(im,(x,580-h),im)
        draw.text((x,590),r['file'],fill='white')
        x+=w+16
    preview.save(OUT/'preview.png')
    with zipfile.ZipFile(OUT/'castles-0-9.zip','w',zipfile.ZIP_DEFLATED) as archive:
        for r in records:archive.write(OUT/r['file'],r['file'])
        archive.write(OUT/'sizes.json','sizes.json')
    print(json.dumps(records,indent=2))


if __name__ == '__main__':
    finish()
