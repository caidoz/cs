import json, unittest
from pathlib import Path
from PIL import Image
ROOT=Path(__file__).resolve().parents[2]
class ArtilleryAssets(unittest.TestCase):
    def test_all_animation_frames_have_visible_art_and_stay_in_atlas(self):
        path=ROOT/'Resources/res/castle_artillery'
        data=json.loads((path/'manifest.json').read_text(encoding='utf-8'))
        atlas=Image.open(path/'attacks.png').convert('RGBA')
        self.assertEqual(len(data['rects']),248)
        for x,y,w,h in data['rects']:
            self.assertTrue(0<w<=96 and 0<h<=96)
            self.assertLessEqual(x+w,atlas.width)
            self.assertLessEqual(y+h,atlas.height)
            self.assertIsNotNone(atlas.crop((x,y,x+w,y+h)).getchannel('A').getbbox())
    def test_grade_progression_and_native_resource_reuse(self):
        profiles=json.loads((ROOT/'content/castles/artillery.json').read_text(encoding='utf-8'))
        self.assertEqual([p['grade'] for p in profiles],list(range(1,11)))
        for grade in (3,5,8): self.assertTrue(profiles[grade-1]['asset'].startswith('diana:'))
        self.assertEqual(len({p['kind'] for p in profiles}),10)
        dps=[p['damagePercent']*p['hits']/(p['cooldown']+12+p['hits']*p['interval']) for p in profiles]
        self.assertEqual(dps,sorted(dps))
if __name__=='__main__': unittest.main()
