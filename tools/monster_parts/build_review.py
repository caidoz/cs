"""Build all semantic icons, packed tiers and a standalone local review page."""
import html
import json
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont
from build_all import OUT, ROOT, fit, font
from catalogue import SELECTIONS, TIERS, SOURCE_OVERRIDES, MASKS

def arrange(icons, target):
    blocks=list(range(len(icons)))
    repeat=[i for i,p in enumerate(icons) if p['role']!='core']
    while len(blocks)<target:
        blocks.append(repeat[(len(blocks)-len(icons))%len(repeat)])
    blocks.sort(key=lambda i:(-icons[i]['size'][0]*icons[i]['size'][1],i))
    occupied=set(); result=[]
    for i in blocks:
        w,h=icons[i]['size']
        for y in range(5-h):
            for x in range(7-w):
                cells={(x+dx,y+dy) for dx in range(w) for dy in range(h)}
                if not cells&occupied:
                    occupied|=cells
                    result.append(dict(icon=i,x=x,y=y,w=w,h=h));break
            else:continue
            break
        else:raise RuntimeError('Board packing failed')
    return result

def board(r,tier,cell=46):
    im=Image.new('RGBA',(6*cell,4*cell),(24,26,36));d=ImageDraw.Draw(im)
    for y in range(4):
        for x in range(6):d.rectangle((x*cell,y*cell,(x+1)*cell-1,(y+1)*cell-1),outline=(65,64,75))
    for b in r['tiers'][tier]['blocks']:
        x,y,w,h=b['x']*cell,b['y']*cell,b['w']*cell,b['h']*cell
        role=r['icons'][b['icon']]['role']
        color={'core':(101,52,65),'attack':(77,37,49),'guard':(53,47,69)}[role]
        d.rectangle((x+2,y+2,x+w-3,y+h-3),fill=color,outline=(166,99,109))
        icon=Image.open(OUT/r['icons'][b['icon']]['asset']).convert('RGBA')
        thumb=fit(icon,(w-10,h-20))
        im.alpha_composite(thumb,(x+(w-thumb.width)//2,y+4+(h-20-thumb.height)//2))
        d.text((x+5,y+h-18),'★'*r['tiers'][tier]['stars'],font=font(10),fill=(241,200,100))
    return im

def main():
    sources=json.loads((OUT/'sources.json').read_text(encoding='utf-8'))
    catalogue=[]; warnings=[]; pixels=0
    for r in sources:
        parts={p['index']:p for p in r['parts']}; icons=[]
        for entry in SELECTIONS[r['base']]:
            i,name,role,*crop=entry
            source=parts[i]
            override=SOURCE_OVERRIDES.get((r['cmf'],i))
            sx,sy,sw,sh=override or source['rect']
            sheet=Image.open(ROOT/f"Resources/res/c{r['cmf']}.png").convert('RGBA')
            if override:
                assert sx+sw<=sheet.width and sy+sh<=sheet.height
                original=sheet.crop((sx,sy,sx+sw,sy+sh))
            else:
                original=Image.open(OUT/source['asset']).convert('RGBA')
            expected=original
            local=crop[0] if crop else None
            if local:
                x,y,w,h=local
                assert x>=0 and y>=0 and x+w<=original.width and y+h<=original.height
                expected=original.crop((x,y,x+w,y+h))
            polygon=MASKS.get((r['base'],name))
            if polygon:
                mask=Image.new('L',expected.size,0)
                ImageDraw.Draw(mask).polygon(polygon,fill=255)
                masked=Image.new('RGBA',expected.size)
                masked.paste(expected,(0,0),mask)
                expected=masked
            assert expected.getbbox(),(r['cmf'],entry)
            bbox=expected.getbbox();icon=expected.crop(bbox)
            asset=f"c{r['cmf']}/icon-{len(icons)}.png"
            icon.save(OUT/asset)
            assert Image.open(OUT/asset).convert('RGBA').tobytes()==icon.tobytes()
            # Compare unmodified pixels, including transparency, to authoritative sheet.
            assert sheet.crop((sx,sy,sx+sw,sy+sh)).tobytes()==original.tobytes()
            if source['clipped'] and not override:warnings.append(dict(cmf=r['cmf'],part=i,name=r['name']))
            pixels+=icon.width*icon.height
            size=[2,2] if role=='core' else [2,1] if icon.width/icon.height>1.7 else [1,2] if icon.height/icon.width>1.7 else [1,1]
            icons.append(dict(name=name,role=role,part=i,asset=asset,crop=local,mask=polygon,source_override=override,source_rect=[sx,sy,sw,sh],trim=list(bbox),size=size,method='override' if override else 'masked-crop' if polygon else 'crop' if crop else 'direct'))
        item={k:r[k] for k in ('id','name','enum','cmf','base')};item['icons']=icons;item['tiers']={}
        for key,label,count,stars in TIERS:
            blocks=arrange(icons,max(count,len(icons)))
            cells=set()
            for b in blocks:
                for y in range(b['y'],b['y']+b['h']):
                    for x in range(b['x'],b['x']+b['w']):
                        assert 0<=x<6 and 0<=y<4 and (x,y) not in cells
                        cells.add((x,y))
            assert sum(icons[b['icon']]['role']=='core' for b in blocks)==1
            item['tiers'][key]=dict(label=label,stars=stars,blocks=blocks)
        catalogue.append(item)
    originals=[r for r in catalogue if r['id']<54]
    for page in range(6):
        subset=originals[page*9:(page+1)*9]
        im=Image.new('RGBA',(1440,80+len(subset)*230),(21,25,35));d=ImageDraw.Draw(im)
        d.text((20,10),f'CMF 원본 부위 인벤토리 / {page+1:02}   일반 → 정예 → 강적',font=font(25),fill='#ead4a6')
        d.text((20,47),'원본 픽셀 사용 · ★와 블록 수는 강화 규칙 시안 · 전투 미적용',font=font(14),fill='#b5bdcd')
        for row,r in enumerate(subset):
            y=80+row*230
            d.text((12,y+5),f"{r['name']}  c{r['cmf']}",font=font(18),fill='white')
            for idx,p in enumerate(r['icons']):
                icon=Image.open(OUT/p['asset']).convert('RGBA');thumb=fit(icon,(92,108))
                x=15+idx*105;im.alpha_composite(thumb,(x+(95-thumb.width)//2,y+42+(108-thumb.height)//2))
                d.text((x,y+157),p['name'],font=font(12),fill='#dbd5ca')
            for col,(key,label,_,_) in enumerate(TIERS):
                x=540+col*296
                im.alpha_composite(board(r,key),(x,y+28))
                count=len(r['tiers'][key]['blocks'])
                d.text((x,y+5),f'{label} · {count}블록',font=font(14),fill='#e7bca5')
            d.line((10,y+222,1420,y+222),fill='#46505e')
        im.convert('RGB').save(OUT/f'inventory-review-{page+1}.jpg',quality=96)
    comparison=next(r for r in originals if r['cmf']==13)
    sample=Image.new('RGBA',(1080,330),(21,25,35));d=ImageDraw.Draw(sample)
    d.text((18,10),'같은 멧돼지의 강화 예시 · 부위 종류 고정 / 블록 투자 증가',font=font(23),fill='#ead4a6')
    for col,(key,label,_,_) in enumerate(TIERS):
        sample.alpha_composite(board(comparison,key,52),(18+col*354,92))
        d.text((18+col*354,59),f"{label} · {len(comparison['tiers'][key]['blocks'])}블록",font=font(20),fill='white')
    sample.convert('RGB').save(OUT/'strength-comparison.jpg',quality=96)
    (OUT/'catalogue.json').write_text(json.dumps(catalogue,ensure_ascii=False,indent=2),encoding='utf-8')
    stats=dict(monsters=len(catalogue),base_species=len(originals),source_rectangles=sum(len(r['parts']) for r in sources),icons=sum(len(r['icons']) for r in catalogue),boards=len(catalogue)*3,verified_pixels=pixels,selected_source_clipping=warnings,source_override_count=sum(bool(p['source_override']) for r in catalogue for p in r['icons']),all_source_clipping=[dict(cmf=r['cmf'],part=p['index']) for r in sources for p in r['parts'] if p['clipped']])
    (OUT/'validation.json').write_text(json.dumps(stats,ensure_ascii=False,indent=2),encoding='utf-8')
    payload=json.dumps(catalogue,ensure_ascii=False).replace('</','<\\/')
    template=(Path(__file__).with_name('review-template.html')).read_text(encoding='utf-8')
    (OUT/'index.html').write_text(template.replace('__CATALOGUE__',payload),encoding='utf-8')
    print(json.dumps(stats,ensure_ascii=False))

if __name__=='__main__':main()
