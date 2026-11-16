"""Extract original monster pixels and build a reviewable inventory catalogue."""
import csv
import io
import json
import re
import struct
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'output/monster-parts-all'
OUT.mkdir(parents=True, exist_ok=True)

def pack_arrays():
    data = (ROOT / 'Resources/data/content.pack').read_bytes()
    magic, _, count, _ = struct.unpack_from('<4I', data)
    assert magic == 0x314B5049
    start = 16 + count * 48
    result = {}
    for i in range(count):
        e = 16 + i * 48
        name = data[e:e+32].split(b'\0')[0].decode()
        size, kind = data[e+32:e+34]
        cells, offset = struct.unpack_from('<II', data, e+36)
        if name.startswith('cmf'):
            fmt = {1:'B', 2:'H', 4:'I'}[size]
            if 'MotionImgBlob' in name:
                fmt = 'h'
            result[name] = struct.unpack_from('<' + str(cells) + fmt, data, start+offset)
    return result

def enum_values():
    text = (ROOT/'Classes/Def/CmfDef.h').read_text(encoding='utf-8-sig')
    text = re.sub(r'//[^\n]*', '', text)
    text = text.split('{',1)[1].split('}',1)[0]
    result, value = {}, 0
    for item in text.split(','):
        m = re.fullmatch(r'\s*(\w+)\s*(?:=\s*(\d+))?\s*', item)
        if not m:
            continue
        if m[2]: value=int(m[2])
        result[m[1]]=value
        value+=1
    return result

def font(n):
    return ImageFont.truetype('C:/Windows/Fonts/malgun.ttf',n)

def fit(im, size):
    scale = min(size[0]/im.width, size[1]/im.height)
    if scale >= 1: scale = max(1,int(scale))
    return im.resize((max(1,int(im.width*scale)),max(1,int(im.height*scale))),Image.Resampling.NEAREST)

def main():
    arrays, enums = pack_arrays(), enum_values()
    lines = [l for l in (ROOT/'content/enemy.tsv').read_text(encoding='utf-8-sig').splitlines() if l and not l.startswith('#')]
    enemies = [r for r in csv.DictReader(lines,delimiter='\t') if r['enum_name'].startswith('ENEMY_')]
    bases = [r for r in enemies if int(r['id']) < 54]
    assert len(enemies)==357 and len(bases)==51
    atlas = Image.new('RGBA',(1440, ((len(bases)+5)//6)*200),(22,26,36))
    draw = ImageDraw.Draw(atlas)
    records=[]
    for bi,row in enumerate(bases):
        cmf=enums[row['cmf']]
        sheet=Image.open(ROOT/f'Resources/res/c{cmf}.png').convert('RGBA')
        thumb=fit(sheet,(226,150))
        x=(bi%6)*240;y=(bi//6)*200
        atlas.alpha_composite(thumb,(x+(240-thumb.width)//2,y+32))
        draw.text((x+6,y+5),f"c{cmf} {row['label']}",font=font(16),fill='white')
    atlas.convert('RGB').save(OUT/'all-base-sheets.jpg',quality=95)
    for row in enemies:
        cmf=enums[row['cmf']]
        base=next(enums[b['cmf']] for b in bases if arrays['cmfOffSlot'][enums[b['cmf']]]==arrays['cmfOffSlot'][cmf])
        sheet_path=ROOT/f'Resources/res/c{cmf}.png'
        if not sheet_path.exists(): raise RuntimeError(f'Missing sheet {cmf}')
        sheet=Image.open(sheet_path).convert('RGBA')
        total=int(re.search(r'TOTALC\d+OFF\s*=\s*(\d+)',(ROOT/f'Classes/Cmf/c{base}.h').read_text(encoding='utf-8-sig'))[1])
        first=arrays['cmfImgOff'][cmf*5]
        end=min(total,arrays['cmfImgOff'][cmf*5+1])
        parts=[]
        folder=OUT/f'c{cmf}';folder.mkdir(exist_ok=True)
        contact=Image.new('RGBA',(900,((end-first+5)//6)*120),(25,30,40))
        cd=ImageDraw.Draw(contact)
        for i in range(first,end):
            pos=arrays['cmfOffSlot'][cmf]+i*4
            sx,sy,w,h=arrays['cmfOffBlob'][pos:pos+4]
            assert w>0 and h>0,(cmf,i)
            clipped = sx+w>sheet.width or sy+h>sheet.height
            part=sheet.crop((sx,sy,sx+w,sy+h))
            part.save(folder/f'part-{i:02}.png')
            px=((i-first)%6)*150;py=((i-first)//6)*120
            thumb=fit(part,(142,90))
            contact.alpha_composite(thumb,(px+(150-thumb.width)//2,py+(92-thumb.height)//2))
            cd.text((px+5,py+94),f'#{i} {w}x{h}',font=font(13),fill='white')
            parts.append(dict(index=i,rect=[sx,sy,w,h],asset=f'c{cmf}/part-{i:02}.png',clipped=clipped))
        contact.save(folder/'source-parts.png')
        start=arrays['cmfMotionImgCntSlot'][cmf]
        first_motion,count=arrays['cmfMotionImgCntBlob'][start:start+2]
        mi=arrays['cmfMotionImgSlot'][cmf]+first_motion*4
        idle=list(dict.fromkeys(arrays['cmfMotionImgBlob'][mi+j*4] for j in range(count)))
        records.append(dict(id=int(row['id']),name=row['label'],enum=row['enum_name'],cmf=cmf,base=base,idle_parts=idle,parts=parts))
    (OUT/'sources.json').write_text(json.dumps(records,ensure_ascii=False,indent=2),encoding='utf-8')
    originals=[r for r in records if r['id']<54]
    for page in range(6):
        subset=originals[page*9:(page+1)*9]
        review=Image.new('RGBA',(1440,max(1,len(subset))*150),(22,26,36));rd=ImageDraw.Draw(review)
        for row,r in enumerate(subset):
            rd.text((5,row*150+5),f"c{r['cmf']} {r['name']}",font=font(16),fill='white')
            available={p['index']:p for p in r['parts']}
            for col,i in enumerate([i for i in r['idle_parts'] if i in available][:10]):
                im=Image.open(OUT/available[i]['asset']).convert('RGBA');im=fit(im,(132,100))
                review.alpha_composite(im,(col*144+(144-im.width)//2,row*150+30))
                rd.text((col*144+4,row*150+131),f'#{i}',font=font(13),fill='white')
        review.convert('RGB').save(OUT/f'idle-review-{page+1}.jpg',quality=95)
    print(f'Extracted {len(records)} monsters / {sum(len(r["parts"]) for r in records)} source rectangles; {len(bases)} base species.')

if __name__=='__main__': main()
