"""Register untouched rectangular room originals, never silhouette-clipped stacks."""
from pathlib import Path
import shutil
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
FAMILIES=['starter','second','third','fourth','fifth','sixth','seventh','eighth','ninth','tenth']
out=ROOT/'Resources/res/castle_rectangular_rooms'
out.mkdir(parents=True,exist_ok=True)
names=[]
for c,family in enumerate(FAMILIES,1):
    folder=ROOT/'content/castles'/f'{family}_modular_sd_v1'
    for stage in range(6):
        filename=f'castle_room_{c:02}_{stage}.png'
        source=(folder if stage==0 else folder/f'upgrade-{stage}')/'original-resources'/filename
        assert source.exists(),source
        im=Image.open(source)
        assert im.size==(512,128),(source,im.size)
        # The room's central wall must not contain the holes cut for old roofs.
        alpha=im.convert('RGBA').getchannel('A')
        assert alpha.crop((32,16,480,112)).getextrema()[0]>=240,source
        shutil.copy2(source,out/filename)
        names.append(f'\t"castle_rectangular_rooms/{filename[:-4]}",')
(ROOT/'Classes/RectangularRoomNames.inc').write_text('\n'.join(names)+'\n',encoding='utf-8')
print('PASS 60 intact 512x128 room originals and opaque inner walls')
