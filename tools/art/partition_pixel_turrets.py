"""Pack generated turret cells into the existing native frame/muzzle coordinates."""
from pathlib import Path
from PIL import Image
import re
root=Path(__file__).resolve().parents[2]
dest=root/'Resources/res/castle_pixel_01_v1'
source=Image.open(dest/'turret-source.png').convert('RGBA')
header=(root/'Classes/Data/MountedCannonSprites.h').read_text()
frames=re.findall(r'\{(\d+),(\d+),(\d+),(\d+),(\d+),(\d+)\}',header.split('frames[60]=')[1])[:60]
atlas=Image.new('RGBA',(2304,2560))
for i,values in enumerate(frames):
    x,y,w,h,mx,my=map(int,values)
    col,row=i%6,i//6
    cell=source.crop((round(col*source.width/6),round(row*source.height/10),
                      round((col+1)*source.width/6),round((row+1)*source.height/10)))
    alpha=cell.getchannel('A').point(lambda a:255 if a>=128 else 0)
    cell.putalpha(alpha)
    bounds=alpha.getbbox()
    assert bounds, i
    cell=cell.crop(bounds).resize((w,h),Image.Resampling.NEAREST)
    atlas.alpha_composite(cell,(x,y))
atlas.save(dest/'turret-atlas.png')
print('Packed all 60 turret upgrade parts into unchanged frame coordinates')
