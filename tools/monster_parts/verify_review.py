"""Validate catalogue coverage, original pixels and all packed strength tiers."""
import csv
import json
from collections import Counter
from PIL import Image, ImageDraw
from build_all import ROOT, OUT

def main():
    catalogue=json.loads((OUT/'catalogue.json').read_text(encoding='utf-8'))
    lines=[l for l in (ROOT/'content/enemy.tsv').read_text(encoding='utf-8-sig').splitlines() if l and not l.startswith('#')]
    expected={int(r['id']) for r in csv.DictReader(lines,delimiter='\t') if r['enum_name'].startswith('ENEMY_')}
    assert {r['id'] for r in catalogue}==expected
    assert len(catalogue)==len(expected)==357
    assert len({r['base'] for r in catalogue})==51
    counts=Counter()
    for r in catalogue:
        sheet=Image.open(ROOT/f"Resources/res/c{r['cmf']}.png").convert('RGBA')
        assert sum(p['role']=='core' for p in r['icons'])==1
        for p in r['icons']:
            x,y,w,h=p['source_rect']
            assert 0<=x<x+w<=sheet.width and 0<=y<y+h<=sheet.height
            expected=sheet.crop((x,y,x+w,y+h))
            if p['crop']:
                x,y,w,h=p['crop'];expected=expected.crop((x,y,x+w,y+h))
            if p['mask']:
                mask=Image.new('L',expected.size,0);ImageDraw.Draw(mask).polygon(p['mask'],fill=255)
                masked=Image.new('RGBA',expected.size);masked.paste(expected,(0,0),mask);expected=masked
            expected=expected.crop(tuple(p['trim']))
            actual=Image.open(OUT/p['asset']).convert('RGBA')
            assert actual.size==expected.size and actual.tobytes()==expected.tobytes(),(r['cmf'],p['name'])
            counts[p['method']]+=1
        sizes=[]
        for tier in ('normal','elite','boss'):
            blocks=r['tiers'][tier]['blocks'];sizes.append(len(blocks));used=set()
            assert sum(r['icons'][b['icon']]['role']=='core' for b in blocks)==1
            assert set(b['icon'] for b in blocks)==set(range(len(r['icons'])))
            for b in blocks:
                for y in range(b['y'],b['y']+b['h']):
                    for x in range(b['x'],b['x']+b['w']):
                        assert 0<=x<6 and 0<=y<4 and (x,y) not in used
                        used.add((x,y))
        assert sizes[0]<sizes[1]<sizes[2]<=9
    result=dict(status='PASS',monsters=357,base_species=51,icons=sum(counts.values()),boards=357*3,methods=dict(counts))
    (OUT/'verification.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
    print(json.dumps(result))

if __name__=='__main__':main()
