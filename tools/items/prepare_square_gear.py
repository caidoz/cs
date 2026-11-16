"""Build ordered grid-design references and independent icon identities."""
from pathlib import Path
import re,json
from PIL import Image
ROOT=Path(__file__).resolve().parents[2]
WORK=ROOT/'output/square-gear'
(WORK/'source').mkdir(parents=True,exist_ok=True)
s=(ROOT/'Classes/Data/ItemData.cpp').read_text(encoding='utf-8-sig').split('itemIconTable_builtin[] = {')[1].split('};')[0]
sections={};key=None
for line in s.splitlines():
    m=re.match(r'\s*//(ITEM_[A-Z0-9_]+)\s*$',line)
    if m:key=m[1];sections[key]=[];continue
    expr=line.split('//')[0].strip().rstrip(',')
    if key and expr and re.fullmatch(r'[0-9 +*()-]+',expr):sections[key].append(eval(expr,{'__builtins__':{}},{}))
names=['HELM','HAT','CAP','ARMOR','VEST','COAT','GUNTLET','ARMLET','GLOVE','KILT','SKIRT','PANTS','GREAVES','SHEOS','BOOTS']
entries=[];groups={}
for typ,name in enumerate(names,3):
    ids=sections['ITEM_'+name];assert len(ids)==8,(name,len(ids))
    for d,icon in enumerate(ids):
        if 9<=typ<=11:icon=584+(typ-9)*8+d
        grid=105+(typ-3)*8+d;group=['helm','armor','gloves','pants','boots'][(typ-3)//3]
        source=f'Resources/res/items/item{icon}.png' if 6<=typ<=8 else f'Resources/res/grid_items/grid{grid}.png'
        e=dict(type=typ,detail=d,item=icon,grid=grid,group=group,cell=len(groups.get(group,[])),source=source)
        entries.append(e);groups.setdefault(group,[]).append(e)
for name,items in groups.items():
    sheet=Image.new('RGBA',(2048,768))
    for e in items:
        im=Image.open(ROOT/e['source']).convert('RGBA');bbox=im.getchannel('A').point(lambda a:255 if a>32 else 0).getbbox()
        im=im.crop(bbox);im.thumbnail((208,208),Image.Resampling.LANCZOS)
        sheet.alpha_composite(im,(e['cell']%8*256+(256-im.width)//2,e['cell']//8*256+(256-im.height)//2))
    sheet.save(WORK/f'source/{name}.png')
(WORK/'catalog.json').write_text(json.dumps({'entries':entries},indent=2))
print('Prepared 120 references and independent item IDs')
