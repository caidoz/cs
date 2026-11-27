"""Isolate the five existing dock icons; retain their original RGBA pixels."""
from pathlib import Path
from PIL import Image, ImageDraw
from collections import deque

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'asset_library/work/legacy-lobby-icons'
OUT.mkdir(parents=True, exist_ok=True)
source = Image.open(ROOT / 'asset_library/reference/Resources/res/merge_castle_original/reference.png').convert('RGBA').crop((76,1275,1018,1439))
outlines = [
    [(88,36),(108,30),(159,34),(173,46),(176,83),(164,99),(104,103),(84,88),(84,53)],
    [(286,34),(299,29),(313,32),(322,37),(343,35),(352,43),(345,59),(346,88),(334,102),(282,105),(267,92),(268,64),(277,43)],
    [(436,31),(447,23),(465,32),(480,45),(500,29),(512,27),(521,35),(514,45),(505,52),(512,61),(510,82),(495,101),(479,107),(464,99),(452,85),(449,63),(441,51)],
    [(601,52),(610,45),(612,35),(628,33),(637,27),(646,36),(657,25),(668,33),(680,28),(685,42),(699,44),(706,58),(701,79),(709,91),(698,102),(676,104),(663,97),(647,104),(628,100),(615,105),(600,94),(595,75)],
    [(779,39),(783,31),(790,32),(794,46),(808,43),(808,32),(820,32),(823,41),(837,40),(844,31),(851,33),(854,48),(865,49),(869,101),(778,103),(776,55)],
]
atlas = Image.new('RGBA',(640,128))
for i, points in enumerate(outlines):
    mask = Image.new('L',source.size)
    ImageDraw.Draw(mask).polygon(points,fill=255)
    icon=source.copy();icon.putalpha(mask);icon=icon.crop(mask.getbbox())
    # The original dock has a brown backdrop. Remove only backdrop-colored
    # pixels connected to the cut boundary, retaining the enclosed icon pixels.
    pixels=icon.load();seen=set();queue=deque()
    def backdrop(x,y):
        r,g,b,a=pixels[x,y]
        return a==0 or (35<r<160 and 9<g<95 and b<58 and r>g*1.6 and g>b*1.4)
    for y in range(icon.height):
        for x in range(icon.width):
            if (x in (0,icon.width-1) or y in (0,icon.height-1) or pixels[x,y][3]==0) and backdrop(x,y):
                queue.append((x,y));seen.add((x,y))
    while queue:
        x,y=queue.popleft();r,g,b,a=pixels[x,y];pixels[x,y]=(r,g,b,0)
        for nx,ny in ((x-1,y),(x+1,y),(x,y-1),(x,y+1)):
            if 0<=nx<icon.width and 0<=ny<icon.height and (nx,ny) not in seen and backdrop(nx,ny):
                seen.add((nx,ny));queue.append((nx,ny))
    visited=set()
    for y in range(icon.height):
        for x in range(icon.width):
            if (x,y) in visited or not pixels[x,y][3]:continue
            component=[];queue=deque([(x,y)]);visited.add((x,y))
            while queue:
                cx,cy=queue.popleft();component.append((cx,cy))
                for nx,ny in ((cx-1,cy),(cx+1,cy),(cx,cy-1),(cx,cy+1)):
                    if 0<=nx<icon.width and 0<=ny<icon.height and (nx,ny) not in visited and pixels[nx,ny][3]:
                        visited.add((nx,ny));queue.append((nx,ny))
            if len(component)<20:
                for cx,cy in component:
                    r,g,b,a=pixels[cx,cy];pixels[cx,cy]=(r,g,b,0)
    atlas.alpha_composite(icon,(i*128+(128-icon.width)//2,(128-icon.height)//2))
atlas.save(OUT/'legacy-lobby-icons.png')
