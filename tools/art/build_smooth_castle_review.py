"""Register redrawn architectures on an incremental, native-pixel chassis.

Architecture is uniformly sampled. Foundation courses repeat newly authored
material pixels instead of stretching the castle's doors, windows or walls.
This is an external review library, never a runtime import.
"""
from pathlib import Path
from PIL import Image
import json
import shutil
from build_portrait_assets import source,isolated,WORK

OUT=WORK/'smooth-review-v2'
ART=OUT/'art'
ART.mkdir(parents=True,exist_ok=True)
SHEETS=['exec-c363332f-b3cc-4718-aac0-f41fd6ca7903.png',
        'exec-f3cebc78-701b-4c1b-9377-575d6490f989.png',
        'exec-9e1979b1-75a2-4862-9b61-d98eab4ee562.png',
        'exec-44420875-f3aa-47b7-a91d-7e296f406a5f.png']

def foundation(art,width,height):
    """Build load-bearing courses from the same new hull's masonry texture."""
    a=art.convert('RGBA');w,h=a.size
    tilew=max(12,min(36,w//8));tileh=12
    best=None
    for y in range(max(0,h-h//5),h-tileh,4):
        for x in (max(0,w//10),max(0,w-w//10-tilew)):
            tile=a.crop((x,y,x+tilew,y+tileh))
            alpha=list(tile.getchannel('A').getdata())
            score=sum(v>220 for v in alpha)
            if best is None or score>best[0]:best=(score,tile)
    tile=best[1]
    # Opaque backing is sampled from the same material, never from old art.
    pixels=[p for p in tile.getdata() if p[3]>220]
    color=tuple(sum(p[c] for p in pixels)//max(1,len(pixels)) for c in range(3))+(255,)
    result=Image.new('RGBA',(width,height),color)
    for y in range(0,height,tileh):
        offset=-(tilew//2) if (y//tileh)%2 else 0
        for x in range(offset,width,tilew):result.alpha_composite(tile,(x,y))
    # Carry the actual authored chassis cap as the final ground-facing course.
    cap=a.crop((0,max(0,h-7),w,h))
    result.alpha_composite(cap,((width-w)//2,height-cap.height))
    return result

records=[]
for group,name in enumerate(SHEETS):
    sheet=source(name);cols=4 if group==3 else 5
    for col in range(cols):
        index=group*5+col
        raw=isolated(sheet.crop((round(col*sheet.width/cols),0,round((col+1)*sheet.width/cols),sheet.height)))
        width=round(256*(1+.2*index/18));height=round(300+480*index/18)
        z=min(width/raw.width,(height-12)/raw.height)
        body=isolated(raw.resize((round(raw.width*z),round(raw.height*z)),Image.Resampling.NEAREST))
        baseheight=height-body.height
        master=Image.new('RGBA',(width,height))
        master.alpha_composite(body,((width-body.width)//2,0))
        master.alpha_composite(foundation(body,width,baseheight),(0,body.height))
        path=ART/f'portrait-castle-{index+1:02d}.png';master.save(path,optimize=True)
        # Export attachments at their native assembly dimensions, then the
        # entire castle is displayed with ONE common scale in the review.
        wheel=round(78*(1+.2*index/18));gunw=round(100*(1+.2*index/18))
        for kind,native in [('wheel',wheel),('turret',gunw)]:
            p=Image.open(WORK/'final'/f'portrait-{kind}-{index+1:02d}.png').convert('RGBA')
            if kind=='wheel':k=native/max(p.size)
            else:k=native/p.width
            p=p.resize((round(p.width*k),round(p.height*k)),Image.Resampling.NEAREST)
            p.save(ART/f'portrait-{kind}-{index+1:02d}.png',optimize=True)
        alpha=master.getchannel('A').point(lambda a:255 if a>100 else 0)
        bounds=alpha.getbbox()
        records.append({'stage':index+1,'width':width,'height':height,'area':width*height,
                        'visible_bounds':bounds,'body_uniform_scale':z,'foundation_height':baseheight,
                        'wheel_size':wheel,'turret_width':gunw,'source':name})

for previous,current in zip(records,records[1:]):
    assert current['width']>previous['width']
    assert current['height']>previous['height']
    assert current['area']>previous['area']
    assert current['visible_bounds'][2]-current['visible_bounds'][0]==current['width']
    assert current['visible_bounds'][3]-current['visible_bounds'][1]==current['height']
report={'stages':records,'width_ratio':records[-1]['width']/records[0]['width'],
        'height_ratio':records[-1]['height']/records[0]['height'],
        'area_ratio':records[-1]['area']/records[0]['area'],
        'all_dimensions_monotonic':True,'anisotropic_scaling':False}
(OUT/'dimensions.json').write_text(json.dumps(report,indent=2)+'\n')
print(f"PASS 19 stages: 256x300 -> 307x780; width {report['width_ratio']:.3f}, height {report['height_ratio']:.3f}, area {report['area_ratio']:.3f}")
