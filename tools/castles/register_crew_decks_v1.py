"""Register generated deck sprites unchanged and record their opaque crop."""
from pathlib import Path
from PIL import Image
import json
import shutil

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / 'content/castles/crew_decks_v1'
GAME = ROOT / 'Resources/res/castle_crew_decks'

def main():
    GAME.mkdir(parents=True, exist_ok=True)
    pieces, entries = [], []
    for castle in range(1, 11):
        name = f'deck-{castle:02}.png'
        src = SOURCE / 'originals' / name
        im = Image.open(src).convert('RGBA')
        alpha = im.getchannel('A')
        assert alpha.getextrema()[0] == 0, src
        x, y, right, low = alpha.point(lambda a: 255 if a >= 128 else 0).getbbox()
        w, h = right-x, low-y
        assert 6 < w/h < 18, (castle, w, h)
        foot = round(h*.36)
        pieces.append(f' {{{x},{y},{w},{h},{foot}}},')
        shutil.copy2(src, GAME/name)
        entries.append(dict(castle=castle, file=name, crop=[x,y,w,h], foot=foot))
    (ROOT/'Classes/Data/CastleCrewDeckLayout.h').write_text(
        '#pragma once\nnamespace CastleCrewDeckLayout {\n'
        'struct Piece {int x,y,w,h,foot;};\nstatic const Piece Pieces[10]={\n'
        +'\n'.join(pieces)+'\n};\n}\n', encoding='utf-8')
    (SOURCE/'manifest.json').write_text(json.dumps(entries, indent=2), encoding='utf-8')
    print('PASS ten transparent continuous battle decks registered without repainting')

if __name__ == '__main__':
    main()
