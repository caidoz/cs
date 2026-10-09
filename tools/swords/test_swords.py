"""Validate lossless image migration and CMF sidecar integrity."""
import json
import math
import re
import unittest
from PIL import Image
from build_sword_poses import ROOT, array, decode, signature


class SwordTests(unittest.TestCase):
    def test_all_35_sprites_match_remodelled_footprints(self):
        rows=json.loads((ROOT/'content/swords/remodel/manifest.json').read_text(encoding='utf-8-sig'))
        self.assertEqual([s['id'] for s in rows],list(range(1,36)))
        for s in rows:
            with self.subTest(sword=s['id']):
                path=ROOT/f'Resources/res/w0_{s["id"]}.png'
                dst=Image.open(path).convert('RGBA')
                self.assertEqual(dst.size,(s['cols']*32,s['rows']*32))
                self.assertEqual((s['width'],s['height']),dst.size)
                self.assertGreater(sum(a>32 for a in dst.getchannel('A').getdata()),100)
                for row in range(s['rows']):
                    for col in range(s['cols']):
                        occupied=not s['cells'] or bool(s['cells'] & (1<<(row*4+col)))
                        tile=dst.crop((col*32,(s['rows']-row-1)*32,(col+1)*32,(s['rows']-row)*32))
                        count=sum(a>32 for a in tile.getchannel('A').getdata())
                        if occupied:self.assertGreater(count,0)
                        else:self.assertEqual(count,0)
                self.assertTrue(0<=s['pivotX']<dst.width and 0<=s['pivotY']<dst.height)
                self.assertGreater(s['handScale'],0)
        self.assertEqual({s['shape'] for s in rows},{'1x2','1x3','1x4','Ttree','2x2','2x3','2x4'})

    def test_track_matches_cmf_and_covers_every_sword_motion(self):
        text=(ROOT/'Classes/Data/CmfBlob.cpp').read_text(encoding='utf-8-sig')
        mi,cnt=[array(text,n) for n in ('cmfMotionImgBlob','cmfMotionImgCntBlob')]
        rows=json.loads((ROOT/'content/swords/poses.json').read_text())
        track={r['motion']:r for r in rows}
        non_quarter=0
        for m in range(842):
            parts=[mi[i:i+4] for i in range(cnt[m*2]*4,(cnt[m*2]+cnt[m*2+1])*4,4)]
            swords=[p for p in parts if p[0] in (108,109)]
            self.assertEqual(bool(swords),m in track)
            if not swords:continue
            row=track[m]
            self.assertEqual(row['signature'],signature(parts))
            self.assertTrue(all(math.isfinite(row[k]) for k in ('handX','handY','angleDegrees','scale','opacity')))
            self.assertTrue(row['scale']>0 and 0<row['opacity']<=1)
            if row['interpolated'] and row['angleDegrees']%30:non_quarter+=1
        self.assertGreater(non_quarter,50)

    def test_original_key_pose_migration_keeps_attachment(self):
        text=(ROOT/'Classes/Data/CmfBlob.cpp').read_text(encoding='utf-8-sig')
        mi,cnt=[array(text,n) for n in ('cmfMotionImgBlob','cmfMotionImgCntBlob')]
        rows=json.loads((ROOT/'content/swords/poses.json').read_text())
        for r in rows:
            if r['motion']>=245:continue
            m=r['motion'];start,count=cnt[m*2:m*2+2]
            part=next(mi[i:i+4] for i in range(start*4,(start+count)*4,4) if mi[i] in (108,109))
            expected=decode(part)
            for k in ('handX','handY','angleDegrees','scale','opacity','flipX'):
                self.assertAlmostEqual(r[k],expected[k])


if __name__=='__main__':unittest.main()
