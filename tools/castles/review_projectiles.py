from pathlib import Path
from PIL import Image, ImageDraw
ROOT = Path(__file__).resolve().parents[2]
im = Image.open(ROOT/'Resources/res/crewBullet.png').convert('RGBA')
out = Image.new('RGBA', (1024, 1344), (24,30,40,255))
draw = ImageDraw.Draw(out)
for n in range(256):
    x, y = n%16*64, n//16*84
    out.alpha_composite(im.crop((n%16*64,n//16*64,(n%16+1)*64,(n//16+1)*64)), (x,y+17))
    draw.text((x+4,y+1),str(n),fill='white')
out.save(ROOT/'output/crew-bullet-index.png')
