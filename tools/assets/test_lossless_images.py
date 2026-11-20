import hashlib
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from PIL import Image
import optimize_images as optimizer
import runtime_assets as assets


class LosslessEncodingTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        self.master = self.root / 'asset_library/production/original.png'
        self.master.parent.mkdir(parents=True)
        image = Image.new('RGBA', (64, 32))
        image.putdata([(x*3, y*7, (x+y)*2, 0 if x<8 else (127 if x<32 else 255))
                       for y in range(32) for x in range(64)])
        image.save(self.master, compress_level=0)
        self.asset = {'source': self.master.relative_to(self.root).as_posix(), 'target': 'res/picture.png'}

    def tearDown(self):
        self.temp.cleanup()

    def test_exact_rgba_dimensions_and_preserved_original(self):
        original = self.master.read_bytes()
        with patch.object(optimizer, 'ROOT', self.root):
            encoded, proof = optimizer.encode(self.asset)
        self.assertEqual(encoded['encoding'], 'webp-lossless')
        self.assertTrue(proof['rgba_exact'])
        self.assertEqual(self.master.read_bytes(), original)
        with Image.open(self.master) as source, Image.open(self.root / encoded['source']) as runtime:
            self.assertEqual(source.size, runtime.size)
            self.assertEqual(source.convert('RGBA').tobytes(), runtime.convert('RGBA').tobytes())
            self.assertEqual(runtime.format, 'WEBP')
        # Existing runtime path stays compatible; the engine reads format magic.
        self.assertEqual(encoded['target'], 'res/picture.png')

    def test_staging_rejects_stale_original_and_corrupt_encoded_master(self):
        with patch.object(optimizer, 'ROOT', self.root):
            encoded, _ = optimizer.encode(self.asset)
        catalog = self.root / 'content/runtime-assets.json'
        catalog.parent.mkdir()
        catalog.write_text(json.dumps({'assets': [encoded]}))
        with patch.object(assets, 'ROOT', self.root), patch.object(assets, 'CATALOG', catalog):
            assets.stage(self.root / 'build/runtime')
            self.assertEqual((self.root/'build/runtime/res/picture.png').read_bytes(),
                             (self.root/encoded['source']).read_bytes())
            original = self.master.read_bytes()
            self.master.write_bytes(original + b'changed')
            with self.assertRaisesRegex(RuntimeError, 'Master changed'): assets.load()
            self.master.write_bytes(original)
            (self.root / encoded['source']).write_bytes(b'corrupt')
            with self.assertRaisesRegex(RuntimeError, 'Encoded master changed'): assets.load()

    def test_cache_corruption_is_repaired_from_preserved_master(self):
        with patch.object(optimizer, 'ROOT', self.root):
            first, _ = optimizer.encode(self.asset)
            cache = next((self.root/'asset_library/work/runtime-encoding/cache').glob('*.webp'))
            cache.write_bytes(b'broken cache')
            second, proof = optimizer.encode(first)
        self.assertTrue(proof['rgba_exact'])
        self.assertEqual(first, second)
        self.assertEqual(hashlib.sha256(cache.read_bytes()).hexdigest(), second['encoded_sha256'])

    def test_opaque_rgba_retains_alpha_channel_for_legacy_blends(self):
        Image.new('RGBA', (64,32), (30,100,190,255)).save(self.master, compress_level=0)
        with patch.object(optimizer, 'ROOT', self.root):
            encoded, proof = optimizer.encode(self.asset)
        self.assertTrue(proof['alpha_semantics_preserved'])
        with Image.open(self.root/encoded['source']) as image:
            self.assertEqual(image.mode, 'RGBA')
            self.assertEqual(image.getpixel((0,0)), (30,100,190,255))


if __name__ == '__main__': unittest.main()
