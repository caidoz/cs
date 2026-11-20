import json
from pathlib import Path
import tempfile
import unittest
import runtime_assets as assets
import retire_legacy_assets as retire
from unittest.mock import patch


class StagingTest(unittest.TestCase):
    def setUp(self):
        self.original = assets.ROOT, assets.CATALOG, assets.LIBRARY
        self.temp = tempfile.TemporaryDirectory()
        assets.ROOT = Path(self.temp.name)
        assets.CATALOG = assets.ROOT / 'content/runtime-assets.json'
        assets.LIBRARY = assets.ROOT / 'asset_library/reference/Resources'
        assets.CATALOG.parent.mkdir()
        assets.LIBRARY.mkdir(parents=True)
        (assets.LIBRARY / 'chosen.png').write_bytes(b'final')
        (assets.LIBRARY / 'draft.png').write_bytes(b'not bundled')
        assets.save({'version': 1, 'assets': [{'source': 'asset_library/reference/Resources/chosen.png', 'target': 'res/chosen.png'}]})

    def tearDown(self):
        assets.ROOT, assets.CATALOG, assets.LIBRARY = self.original
        self.temp.cleanup()

    def test_only_approved_asset_and_stale_build_pruning(self):
        out = assets.ROOT / 'build/approved'
        assets.stage(out)
        self.assertEqual((out / 'res/chosen.png').read_bytes(), b'final')
        self.assertFalse((out / 'res/draft.png').exists())
        (out / 'stale.png').write_bytes(b'old build')
        assets.stage(out, prune=True)
        self.assertFalse((out / 'stale.png').exists())
        self.assertTrue((assets.LIBRARY / 'draft.png').exists())

    def test_missing_source_fails(self):
        (assets.LIBRARY / 'chosen.png').unlink()
        with self.assertRaises(FileNotFoundError): assets.load()

    def test_nested_new_runtime_name_rejected(self):
        with self.assertRaises(ValueError): assets.add(assets.LIBRARY / 'chosen.png', 'new/final.png')

    def test_legacy_nested_catalog_target_rejected(self):
        assets.save({'assets': [{'source': 'asset_library/reference/Resources/chosen.png',
                                'target': 'res/legacy/chosen.png'}]})
        with self.assertRaisesRegex(ValueError, 'must be flat'): assets.load()

    def test_image_budget_rejects_future_growth(self):
        data = assets.load()
        data['max_image_bytes'] = 1
        assets.save(data)
        with self.assertRaisesRegex(ValueError, 'budget exceeded'): assets.load()

    def test_old_owned_directory_is_removed_and_header_matches_catalog(self):
        out = assets.ROOT / 'build/flat'
        old = out / 'res/legacy/chosen.png'
        old.parent.mkdir(parents=True)
        old.write_bytes(b'old')
        out.with_name(out.name + '.runtime-assets-state.json').write_text(json.dumps(['res/legacy/chosen.png']))
        assets.stage(out)
        self.assertFalse(old.parent.exists())
        header = (assets.ROOT / 'Classes/ApprovedRuntimeImages.h').read_text()
        self.assertIn('res/chosen.png', header)
        self.assertNotIn('legacy/', header)

    def test_check_rejects_changed_copy_and_unapproved_file(self):
        out = assets.ROOT / 'build/checked'
        assets.stage(out)
        (out / 'manifest.tsv').write_text('')
        assets.check(out)
        (out / 'res/chosen.png').write_bytes(b'corrupt')
        with self.assertRaisesRegex(ValueError, 'altered runtime copy'): assets.check(out)
        assets.stage(out)
        (out / 'res/draft.png').write_bytes(b'draft')
        with self.assertRaisesRegex(ValueError, 'differs from catalog'): assets.check(out)

    def test_promote_final_to_flat_runtime_name(self):
        assets.add(assets.LIBRARY / 'draft.png', 'approved-final.png')
        out = assets.ROOT / 'build/promoted'
        assets.stage(out)
        self.assertEqual((out / 'res/approved-final.png').read_bytes(), b'not bundled')
        self.assertTrue((assets.ROOT / 'asset_library/production/approved-final.png').is_file())
        self.assertTrue((assets.LIBRARY / 'draft.png').exists())

    def test_escape_rejected(self):
        assets.save({'assets': [{'source': '../outside.png', 'target': 'res/outside.png'}]})
        with self.assertRaises(ValueError): assets.load()

    def test_retirement_preserves_master_and_removes_only_owned_runtime_copy(self):
        data = assets.load()
        data['assets'].append({'source': 'asset_library/reference/Resources/draft.png',
                               'target': 'res/bg1_far.png'})
        assets.save(data)
        out = assets.ROOT / 'build/retired'
        assets.stage(out)
        with patch.object(retire, 'ROOT', assets.ROOT):
            retire.retire(apply=True)
            retire.retire(apply=True)  # Repeating must not duplicate archived entries.
        assets.stage(out)
        self.assertFalse((out / 'res/bg1_far.png').exists())
        self.assertEqual((out / 'res/chosen.png').read_bytes(), b'final')
        self.assertEqual((assets.LIBRARY / 'draft.png').read_bytes(), b'not bundled')
        archive = json.loads((assets.ROOT / 'content/archived-runtime-assets.json').read_text())
        self.assertEqual(len(archive['assets']), 1)

    def test_retirement_rejects_asset_without_external_master(self):
        (assets.ROOT / 'Resources').mkdir()
        (assets.ROOT / 'Resources/old.png').write_bytes(b'only copy')
        assets.save({'assets': [{'source': 'Resources/old.png',
                                'target': 'res/bg1_far.png'}]})
        with patch.object(retire, 'ROOT', assets.ROOT):
            with self.assertRaises(ValueError): retire.retire(apply=True)
        self.assertEqual(len(json.loads(assets.CATALOG.read_text())['assets']), 1)


if __name__ == '__main__': unittest.main()
