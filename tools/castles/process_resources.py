"""Remove connected navy backdrops and scale existing artwork without regeneration."""
from pathlib import Path
import json, shutil
import numpy as np
from PIL import Image, ImageDraw, ImageFilter

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'output/castles/pixel-preserved'
BACKUP = OUT / 'originals'
HEIGHTS = [139, 212, 254, 293, 317, 350, 423, 431, 460, 528]

def process(n):
    path = ROOT / f'Resources/res/castle{n}.png'
    backup = BACKUP / path.name
    if not backup.exists(): shutil.copy2(path, backup)
    im = Image.open(backup).convert('RGBA')
    a = np.asarray(im).astype(np.float32)
    rgb = a[:,:,:3]
    edge = np.concatenate([rgb[:4].reshape(-1,3), rgb[-4:].reshape(-1,3),
                           rgb[:,:4].reshape(-1,3), rgb[:,-4:].reshape(-1,3)])
    # Background is a textured navy gradient. Model its channel relationships,
    # then remove only matching regions connected to the canvas boundary.
    blue = rgb[:,:,2]
    residual = np.zeros(blue.shape)
    for c in (0,1):
        slope, offset = np.polyfit(edge[:,2], edge[:,c], 1)
        residual = np.maximum(residual, abs(rgb[:,:,c] - (slope*blue+offset)))
    residual = np.maximum(residual, np.maximum(0,blue-edge[:,2].max()))
    candidate = residual < 7
    mask = Image.fromarray(np.pad(candidate.astype('uint8')*255,1,constant_values=255)).copy()
    ImageDraw.floodfill(mask,(0,0),128)
    bg = np.asarray(mask)[1:-1,1:-1] == 128
    alpha = np.where(bg,0,255).astype('uint8')
    # Retain anti-alias coverage on the immediate silhouette boundary.
    adjacent = np.asarray(Image.fromarray(bg.astype('uint8')*255).filter(ImageFilter.MaxFilter(3)))>0
    soft = adjacent & ~bg
    alpha[soft] = np.clip((residual[soft]-5)/9*255,0,255).astype('uint8')
    # Remove the navy matte from soft torch/crystal glow fringes as well.
    belt = bg.copy()
    for axis in (0,1):
        padded = np.pad(belt,((30,30),(0,0)) if axis==0 else ((0,0),(30,30)))
        belt = np.logical_or.reduce([padded[k:k+im.height,:] if axis==0 else padded[:,k:k+im.width] for k in range(61)])
    bg_color = np.median(edge,axis=0)
    upper = np.indices(bg.shape)[0] < im.height*.85
    fringe = belt & ~bg & upper & (rgb.max(axis=2)<155)
    coverage = np.clip(np.maximum(rgb-bg_color,0).max(axis=2)/120,0,1)
    alpha[fringe] = (coverage[fringe]*255).astype('uint8')
    af = np.maximum(alpha.astype(np.float32)/255,.01)
    corrected = (rgb-bg_color[None,None,:]*(1-af[:,:,None]))/af[:,:,None]
    a[fringe,:3] = np.clip(corrected[fringe],0,255)
    alpha[alpha<8] = 0
    a[:,:,3] = np.minimum(a[:,:,3],alpha)
    cut = Image.fromarray(a.astype('uint8'))
    bbox = cut.getbbox()
    cut = cut.crop(bbox)
    h = round(1700*HEIGHTS[n]/HEIGHTS[-1])
    w = round(cut.width*h/cut.height)
    result = cut.resize((w,h),Image.Resampling.LANCZOS)
    result = result.crop(result.getbbox())
    result.save(OUT/path.name)
    return {'file':path.name,'original':im.size,'crop':bbox,'size':result.size,'referenceHeight':HEIGHTS[n]}

def main():
    BACKUP.mkdir(parents=True,exist_ok=True)
    records = [process(n) for n in range(10)]
    (OUT/'sizes.json').write_text(json.dumps(records,indent=2)+'\n')
    preview = Image.new('RGB',(2500,700),(110,110,110))
    draw = ImageDraw.Draw(preview)
    x = 10
    for r in records:
        im = Image.open(OUT/r['file'])
        im.thumbnail((180,640))
        # Common scale, not common cell size.
        src = Image.open(OUT/r['file'])
        im = src.resize((round(src.width*.35),round(src.height*.35)),Image.Resampling.LANCZOS)
        preview.paste(im,(x,660-im.height),im)
        draw.text((x,674),r['file'],fill='white')
        x += im.width+14
    preview.crop((0,0,min(x,2500),700)).save(OUT/'scale-review.png')
    print(json.dumps(records))

if __name__ == '__main__': main()
