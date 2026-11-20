"""Verify that an AAB contains exactly the approved runtime asset files."""
import argparse
import json
import zipfile
from collections import defaultdict
from pathlib import Path

root = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser()
parser.add_argument('aab', type=Path)
args = parser.parse_args()
catalog = json.loads((root / 'content/runtime-assets.json').read_text())
expected = {a['target'] for a in catalog['assets']} | {'manifest.tsv'}
with zipfile.ZipFile(args.aab) as archive:
    prefix = 'assets_base/assets/'
    actual = {i.filename[len(prefix):] for i in archive.infolist()
              if i.filename.startswith(prefix) and not i.is_dir()}
    assert actual == expected, {'missing': sorted(expected-actual)[:20], 'extra': sorted(actual-expected)[:20]}
    manifest = archive.read(prefix + 'manifest.tsv').decode('utf-8').splitlines()
    assert manifest == (root/'Resources/manifest.tsv').read_text(encoding='utf-8').splitlines(), 'Bundled updater manifest differs from staged resources'
    manifest_entries = 0
    for line in manifest:
        if not line or line.startswith(('#', 'version\t')): continue
        name, size, digest = line.split('\t')
        assert name in expected, f'Unapproved updater manifest entry: {name}'
        assert archive.getinfo(prefix + name).file_size == int(size), f'Stale updater manifest size: {name}'
        manifest_entries += 1
    retired_path = root / 'content/archived-runtime-assets.json'
    if retired_path.exists():
        retired = {a['target'] for a in json.loads(retired_path.read_text())['assets']}
        assert not actual & retired, {'archived_assets_in_bundle': sorted(actual & retired)}
    groups = defaultdict(lambda: {'files': 0, 'bytes': 0, 'compressed_bytes': 0})
    for item in archive.infolist():
        if not item.filename.startswith(prefix) or item.is_dir(): continue
        path = item.filename[len(prefix):].split('/')
        key = '/'.join(path[:2]) if len(path) > 2 else path[0] + ' (root files)'
        groups[key]['files'] += 1
        groups[key]['bytes'] += item.file_size
        groups[key]['compressed_bytes'] += item.compress_size
    info = {'aab_bytes': args.aab.stat().st_size, 'asset_files': len(actual),
            'asset_bytes': sum(i.file_size for i in archive.infolist() if i.filename.startswith(prefix)),
            'compressed_asset_bytes': sum(i.compress_size for i in archive.infolist() if i.filename.startswith(prefix)),
            'validated_manifest_entries': manifest_entries}
print(json.dumps(info, indent=2))
(root / 'reports/runtime-assets/aab-after.json').write_text(json.dumps(info, indent=2))
(root / 'reports/runtime-assets/aab-groups.json').write_text(json.dumps(dict(
    sorted(groups.items(), key=lambda row: -row[1]['compressed_bytes'])), indent=2))
