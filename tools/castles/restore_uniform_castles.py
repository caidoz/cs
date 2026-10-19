"""Re-register existing castle artwork with one uniform scale; never repaint it.

The previous registrars stretched strips to a fixed rig. Their mappings are read
only to recover semantic partition boundaries and actor anchors, not to draw art.
"""
import json
import math
import re
import subprocess
from pathlib import Path

import numpy as np
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'output/uniform-castles'
OUT.mkdir(parents=True, exist_ok=True)
FAMILIES = ['sixth', 'seventh', 'eighth', 'ninth', 'tenth']


def rigs(family):
    if family == 'sixth':
        left, right = [125,128,130,136,150,128], [322,335,340,373,405,337]
        cy, radius = [949,952,953,960,952,953], [50,55,53,59,60,54]
        extent = [462,507,569,560,592,556]
        result = []
        for s in [0,1,5,3,2,4]:
            result.append(dict(sx=[20,left[s],right[s],extent[s]+10], dx=[20,125,322,470],
                               sy=[0,884,cy[s],1024], dy=[0,884,949,1024],
                               cx=[left[s],right[s]], cy=cy[s], radius=radius[s]))
        return result
    script = (ROOT / f'tools/castles/legacy_registration/register_{family}_sd.ps1').read_text(encoding='utf-8-sig')
    code = script[script.index('Add-Type -AssemblyName'):script.index("'@")+2]
    diagnostic = 'Console.WriteLine("MAP|"+string.Join(",",sx)+"|"+string.Join(",",dx)+"|"+string.Join(",",sy)+"|"+string.Join(",",dy)+"|"+string.Join(",",cx)+"|"+cy+"|"+radius);'
    code = code.replace('Console.WriteLine("Source wheel rig', diagnostic+'\n   Console.WriteLine("Source wheel rig')
    cls = family.title()+'SdRegister'
    code += '\nfor($stage=0;$stage -lt 6;$stage++) {\n'
    code += f'$folder="{(ROOT / ("content/castles/"+family+"_modular_sd_v1")).as_posix()}"\n'
    code += 'if($stage -gt 0){$folder+="/upgrade-$stage"}\n$src=[System.Drawing.Bitmap]::FromFile($folder+"/generated-master.png")\n'
    if family in ['ninth','tenth']:
        code += f'$layout=[{cls}]::Layout($src)\n'
    else:
        code += '$layout=$src\n'
    code += f'$dst=[{cls}]::Exterior($layout);$dst.Dispose();if($layout -ne $src){{$layout.Dispose()}};$src.Dispose()\n}}'
    temp = OUT / f'probe-{family}.ps1'
    temp.write_text(code, encoding='utf-8-sig')
    run = subprocess.run(['powershell','-NoProfile','-ExecutionPolicy','Bypass','-File',str(temp)],
                         capture_output=True, text=True, check=True)
    result = []
    for line in run.stdout.splitlines():
        if not line.startswith('MAP|'): continue
        fields = line.split('|')[1:]
        r = {k:list(map(int,v.split(','))) for k,v in zip(['sx','dx','sy','dy','cx'],fields[:5])}
        r.update(cy=int(fields[5]), radius=int(fields[6]))
        result.append(r)
    assert len(result)==6, run.stdout+run.stderr
    return result


def read_header(path):
    text = path.read_text(encoding='utf-8-sig')
    constants = {k:float(v) for k,v in re.findall(r'(\w+)=(-?[0-9.]+)f?', text)}
    constants['Room'] = list(map(int,re.search(r'Room=\{([^}]+)',text)[1].split(',')))[:4]
    return constants


def run(family, level):
    folder = ROOT / f'content/castles/{family}_modular_sd_v1'
    dirs = [folder]+[folder/f'upgrade-{s}' for s in range(1,6)]
    # Preserve the exact previous metadata and assembled image for comparison.
    for s,d in enumerate(dirs):
        backup = d/'before-uniform-registration'
        backup.mkdir(exist_ok=True)
        for name in ['assembled-master.png','parts.json']:
            dst=backup/name
            if not dst.exists(): dst.write_bytes((d/name).read_bytes())
        header=ROOT/f'Classes/Data/{family.title()}SdParts{("Stage"+str(s)) if s else ""}.h'
        if not (backup/'metadata.h').exists(): (backup/'metadata.h').write_bytes(header.read_bytes())
    mapping=rigs(family)
    (folder/'uniform-source-rigs.json').write_text(json.dumps(mapping,indent=2))
    images=[]; bounds=[]
    for d in dirs:
        im=Image.open(d/'generated-master.png').convert('RGBA')
        # Same uniform layout normalization used by the old 9/10 registrar.
        if im.height!=1024:
            im=im.resize((round(im.width*1024/im.height),1024),Image.Resampling.LANCZOS)
        images.append(im)
        a=np.array(im)[:,:,3]
        bounds.append(Image.fromarray(np.uint8(a>=192)*255).getbbox())
    old=read_header(dirs[0]/'before-uniform-registration/metadata.h')
    width=int(old['Width'])
    # Fit each complete source with one scalar, never independent strip scales.
    scales=[(width-16)/(b[2]-b[0]) for b in bounds]
    height=math.ceil(max((b[3]-b[1])*s for b,s in zip(bounds,scales)))+24
    ground=height-12
    transforms=[]
    for im,b,scale in zip(images,bounds,scales):
        transforms.append((8-b[0]*scale,ground-b[3]*scale))
    def mapped(stage,x,y):
        r=mapping[stage];tx,ty=transforms[stage];scale=scales[stage]
        # Old registered x coordinates include a 20px crop offset.
        return (float(np.interp(x+20,r['dx'],r['sx']))*scale+tx,
                float(np.interp(y,r['dy'],r['sy']))*scale+ty)
    apertures=[]
    for stage in range(6):
        base=mapped(stage,old['Room'][0],old['Room'][1])
        end=mapped(stage,old['Room'][0]+old['Room'][2],old['Room'][1]+old['Room'][3])
        apertures.append((*base,*end))
    left=max(a[0] for a in apertures);top=max(a[1] for a in apertures)
    right=min(a[2] for a in apertures);bottom=min(a[3] for a in apertures)
    aperture=[math.ceil(left),math.ceil(top),math.floor(right)-math.ceil(left),math.floor(bottom)-math.ceil(top)]
    assert min(aperture[2:])>0,(family,apertures)
    ax,ay,aw,ah=aperture
    # The same aperture for all room upgrades keeps mixed part sets aligned.
    reports=[]
    for stage,(d,im,r,(tx,ty),scale) in enumerate(zip(dirs,images,mapping,transforms,scales)):
        master=im.transform((width,height),Image.Transform.AFFINE,
                            (1/scale,0,-tx/scale,0,1/scale,-ty/scale),Image.Resampling.BICUBIC)
        raw=np.array(master)
        yy,xx=np.indices((height,width))
        source_x=(xx-tx)/scale;source_y=(yy-ty)/scale
        ox=np.interp(source_x,r['sx'],r['dx'])-20
        oy=np.interp(source_y,r['sy'],r['dy'])
        # Recover the original semantic masks without using their distorted pixels.
        if level==6:
            group=np.where(oy<150,0,np.where(oy<884,2,np.where(oy<925,5,6)))
            group[(ox>=295)&(oy>=704)&(oy<882)]=4
            group[(ox>=295)&(oy>=580)&(oy<704)]=3
        elif level==7:
            group=np.where(oy<228,0,np.where(oy<900,2,np.where(oy<930,5,6)))
            group[(ox>=260)&(oy>=744)&(oy<900)]=4
            group[(ox>=260)&(oy>=540)&(oy<744)&((ox>=285)|(oy>=620))]=3
        else:
            roof={8:196,9:180,10:160}[level];edge={8:220,9:205,10:190}[level]
            group=np.where(oy<roof,0,np.where(oy<900,2,np.where(oy<935,5,6)))
            group[(ox>=edge)&(oy>=740)&(oy<900)]=4
            group[(ox>=edge)&(oy>=(540 if level==8 else 360))&(oy<740)]=3
        group[ay:ay+ah,ax:ax+aw]=1
        for i,cx in enumerate(r['cx']):
            # Square crop around a circular wheel, with one common scale on both axes.
            wx=cx*scale+tx;wy=r['cy']*scale+ty;radius=r['radius']*scale
            wheel=(xx-wx)**2+(yy-wy)**2<=(radius+1)**2
            group[wheel]=7+i
        parts=json.loads((d/'before-uniform-registration/parts.json').read_text())['parts']
        pieces=[];crops=[]
        for i in range(9):
            a=raw.copy();a[group!=i]=0
            if i==1:
                box=(ax,ay,ax+aw,ay+ah)
            elif i>=7:
                cx=r['cx'][i-7]*scale+tx;cy=r['cy']*scale+ty
                radius=math.ceil(r['radius']*scale+1)
                box=(round(cx)-radius,round(cy)-radius,round(cx)+radius+1,round(cy)+radius+1)
            else:
                box=Image.fromarray(a).getbbox()
            assert box, (family,stage,i)
            x,y,x2,y2=box
            crop=Image.fromarray(a).crop(box)
            pieces.append(dict(name=parts[i]['name'],x=x,y=y,w=x2-x,h=y2-y,sx=0))
            crops.append(crop)
        wheel=Image.new('RGBA',(crops[7].width+crops[8].width,max(crops[7].height,crops[8].height)))
        wheel.paste(crops[7],(0,0));wheel.paste(crops[8],(crops[7].width,0))
        pieces[8]['sx']=crops[7].width
        for i in range(7): crops[i].save(ROOT/'Resources/res'/pieces[i]['name'])
        wheel.save(ROOT/'Resources/res'/pieces[7]['name'])
        roomname=f'castle_room_{level:02d}_{stage}.png'
        room_backup=d/'before-uniform-registration'/roomname
        if not room_backup.exists(): room_backup.write_bytes((ROOT/'Resources/res'/roomname).read_bytes())
        room=Image.open(room_backup).convert('RGBA').resize((aw,ah),Image.Resampling.LANCZOS)
        room_a=np.array(room);room_a[:,:,3]=np.minimum(room_a[:,:,3],raw[ay:ay+ah,ax:ax+aw,3])
        Image.fromarray(room_a).save(ROOT/'Resources/res'/roomname)
        # Verify disk files reconstruct every RGBA pixel exactly.
        rebuilt=Image.new('RGBA',(width,height))
        for p in pieces:
            saved=Image.open(ROOT/'Resources/res'/p['name']).convert('RGBA')
            saved=saved.crop((p['sx'],0,p['sx']+p['w'],p['h']))
            rebuilt.alpha_composite(saved,(p['x'],p['y']))
        visible=raw[:,:,3]>0
        assert np.array_equal(np.array(rebuilt)[visible],raw[visible]), (family,stage,'partition mismatch')
        master.save(d/'assembled-master.png');rebuilt.save(d/'reassembled-closed.png');rebuilt.save(d/'reassembled-game-closed.png')
        opened=rebuilt.copy();opened.paste(Image.fromarray(room_a),(ax,ay));opened.save(d/'reassembled-open.png');opened.save(d/'reassembled-game-open.png')
        oldstage=read_header(d/'before-uniform-registration/metadata.h')
        anchor={}
        for xkey,ykey in [('HeroX','HeroY'),('StoneX','StoneY')]:
            x,y=mapped(stage,oldstage[xkey],oldstage[ykey]);anchor[xkey]=round(x);anchor[ykey]=round(y)
        dx,dy=mapped(stage,oldstage['DeckX'],oldstage['DeckY'])
        dr,_=mapped(stage,oldstage['DeckX']+oldstage['DeckW'],oldstage['DeckY'])
        anchor.update(DeckX=round(dx),DeckY=round(dy),DeckW=round(dr-dx),FloorY=ay+ah-4,
                      GroundY=ground,WheelRadius=round(r['radius']*scale),TopVisibleY=master.getbbox()[1])
        namespace=family.title()+'SdParts'+(f'Stage{stage}' if stage else '')
        header=f'#pragma once\nnamespace {namespace} {{\nusing Piece=StarterSdParts::Piece;\nstatic const int Width={width},Height={height};\nstatic const Piece Pieces[9]={{\n'
        header+=''.join(' {'+','.join(str(p[k]) for k in ['x','y','w','h','sx'])+',0},\n' for p in pieces)
        header+='};\nstatic const Piece Room={'+','.join(map(str,aperture))+',0,0};\n'
        header+='static const int '+','.join(f'{k}={v}' for k,v in anchor.items())+';\n'
        header+=f'static const float RoomFloorGap={ah/level:.6f}f;\n}}\n'
        (ROOT/f'Classes/Data/{namespace}.h').write_text(header)
        report=dict(masterWidth=width,masterHeight=height,visiblePixelMismatches=0,parts=pieces,
                    registration='uniform-source',scaleX=scale,scaleY=scale,source=str((d/'generated-master.png').relative_to(ROOT)),anchors=anchor)
        (d/'parts.json').write_text(json.dumps(report,indent=2))
        (d/'partition-check.txt').write_text('PASS uniform source scaleX == scaleY; disk PNG reconstruction: zero RGBA mismatches.\n')
        reports.append(dict(stage=stage,width=width,height=height,scaleX=scale,scaleY=scale,roomCount=level))
    (folder/'uniform-registration.json').write_text(json.dumps(reports,indent=2))
    print(f'PASS {family}: six stages, {width}x{height}, uniform scale {scale:.6f}, disk reconstruction exact',flush=True)


def write_anchors():
    keys=['HeroX','HeroY','DeckX','DeckY','DeckW','StoneX','StoneY']
    text='#pragma once\n// Generated by restore_uniform_castles.py. All coordinates share one uniform source transform.\nnamespace UniformCastleAnchors {\nstruct Anchor { float heroX,heroY,deckX,deckY,deckW,muzzleX,muzzleY,roofY,hullX,gunX; };\nstatic const Anchor Stages[5][6]={\n'
    for index,family in enumerate(FAMILIES):
        text+=' {\n'
        folder=ROOT/f'content/castles/{family}_modular_sd_v1'
        mapping=json.loads((folder/'uniform-source-rigs.json').read_text())
        for stage in range(6):
            data=read_header(ROOT/f'Classes/Data/{family.title()}SdParts{("Stage"+str(stage)) if stage else ""}.h')
            d=folder/(f'upgrade-{stage}' if stage else '')
            im=Image.open(d/'generated-master.png').convert('RGBA')
            if im.height!=1024: im=im.resize((round(im.width*1024/im.height),1024),Image.Resampling.LANCZOS)
            b=Image.fromarray(np.uint8(np.array(im)[:,:,3]>=192)*255).getbbox()
            scale=json.loads((d/'parts.json').read_text())['scaleX'];tx=8-b[0]*scale;ty=data['GroundY']-b[3]*scale
            r=mapping[stage]
            roof=float(np.interp([150,228,196,180,160][index],r['dy'],r['sy']))*scale+ty
            hull=float(np.mean(r['cx']))*scale+tx
            gun=float(np.interp([295,260,220,205,190][index]+20,r['dx'],r['sx']))*scale+tx
            text+='  {'+','.join(str(int(data[k])) for k in keys)+f',{roof:.5f}f,{hull:.5f}f,{gun:.5f}f'+'},\n'
        text+=' },\n'
    text+='};\n}\n'
    (ROOT/'Classes/Data/UniformCastleAnchors.h').write_text(text)


def write_wrappers():
    for family in FAMILIES:
        for operation in ['register','split']:
            wrapper='''param([ValidateRange(0,5)][int]$Stage=0)
$ErrorActionPreference='Stop'
# Rebuild all six stages together: one common canvas and room aperture are required.
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$python=Join-Path $env:LOCALAPPDATA 'Python/bin/python.exe'
if(!(Test-Path $python)){$python='python'}
& $python (Join-Path $root 'tools/castles/restore_uniform_castles.py') --family FAMILY
if($LASTEXITCODE -ne 0){throw 'Uniform source registration failed'}
'''.replace('FAMILY',family)
            (ROOT/f'tools/castles/{operation}_{family}_sd.ps1').write_text(wrapper,encoding='utf-8-sig')


if __name__=='__main__':
    import argparse
    parser=argparse.ArgumentParser();parser.add_argument('--family',choices=FAMILIES)
    args=parser.parse_args()
    for n,family in enumerate(FAMILIES,6):
        if args.family is None or family==args.family: run(family,n)
    write_anchors()
    write_wrappers()
