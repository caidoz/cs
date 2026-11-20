"""Explicit runtime asset staging. Authoring files never live in Resources/res.

bootstrap: one-time conservative inventory from C++ names and dynamic families.
stage: copy ONLY approved files; never discover assets from directory wildcards.
add: promote a finished file to the flat runtime res namespace.
"""
from pathlib import Path
import argparse
import fnmatch
import hashlib
import json
import re
import shutil

ROOT = Path(__file__).resolve().parents[2]
CATALOG = ROOT / 'content/runtime-assets.json'
LIBRARY = ROOT / 'asset_library/reference/Resources'
EXTENSIONS = {'.png', '.webp', '.jpg', '.jpeg', '.plist', '.pvr', '.ccz', '.ttf', '.otf', '.mp3', '.wav', '.ogg', '.pack'}
DYNAMIC = ['res/inventory_helm/*.png', 'res/inventory_boomerang/*.png',
           'res/inventory_cannon/*.png', 'res/inventory_gun/*.png',
           'res/items/item*.png', 'res/grid_items/grid*.png',
           'res/monster_parts/atlas-*.png']


def inside(path, parent):
    path = path.resolve()
    if not path.is_relative_to(parent.resolve()):
        raise ValueError(f'Path escapes intended root: {path}')
    return path


def load():
    data = json.loads(CATALOG.read_text(encoding='utf-8'))
    targets = [a['target'] for a in data['assets']]
    if len(targets) != len(set(targets)):
        raise ValueError('Duplicate runtime target')
    for a in data['assets']:
        target = a['target']
        if target.startswith('res/') and ('/' in target[4:] or '\\' in target):
            raise ValueError(f'Runtime images must be flat: {target}')
        if target.startswith('res/'):
            inside(ROOT / a['source'], ROOT / 'asset_library')
        inside(ROOT / a['source'], ROOT)
        inside(ROOT / 'Resources' / a['target'], ROOT / 'Resources')
        if not (ROOT / a['source']).is_file():
            raise FileNotFoundError(a['source'])
        if a.get('encoding') == 'webp-lossless':
            original = inside(ROOT / a['original_source'], ROOT)
            if not original.is_file(): raise FileNotFoundError(original)
            if hashlib.sha256(original.read_bytes()).hexdigest() != a['original_sha256']:
                raise RuntimeError(f"Master changed: {a['target']}; run tools/assets/optimize_images.py --apply before staging")
            if hashlib.sha256((ROOT / a['source']).read_bytes()).hexdigest() != a['encoded_sha256']:
                raise RuntimeError(f"Encoded master changed: {a['target']}; run tools/assets/optimize_images.py --apply")
    image_bytes = sum((ROOT / a['source']).stat().st_size for a in data['assets'] if a['target'].startswith('res/'))
    if data.get('max_image_bytes') and image_bytes > data['max_image_bytes']:
        raise ValueError(f'Runtime image budget exceeded: {image_bytes} > {data["max_image_bytes"]} bytes')
    return data


def save(data):
    data['assets'].sort(key=lambda a: a['target'])
    CATALOG.write_text(json.dumps(data, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')


def bootstrap():
    if CATALOG.exists():
        raise RuntimeError('Catalog exists; use add to approve new finished assets')
    text = '\n'.join(p.read_text(encoding='utf-8', errors='replace')
                     for p in (ROOT / 'Classes').rglob('*') if p.suffix in {'.h', '.cpp', '.inc'})
    literals = set(re.findall(r'"([A-Za-z0-9_%./-]+)"', text))
    patterns = DYNAMIC + [re.sub(r'%0?\d*[ds]', '*', s) for s in literals if s.startswith('res/') and '%' in s]
    assets, excluded = [], []
    for p in sorted((ROOT / 'Resources').rglob('*')):
        if not p.is_file():
            continue
        rel = p.relative_to(ROOT / 'Resources').as_posix()
        if p.suffix.lower() not in EXTENSIONS:
            excluded.append(rel)
            continue
        stem = rel[4:].rsplit('.', 1)[0] if rel.startswith('res/') else rel
        keep = (not rel.startswith('res/') or '/' not in rel[4:]
                or stem in literals or rel in literals or rel[4:] in literals
                or any(fnmatch.fnmatchcase(rel, pat) for pat in patterns))
        if keep:
            source = 'asset_library/reference/Resources/' + rel if rel.startswith('res/') else 'Resources/' + rel
            assets.append({'source': source, 'target': rel})
        else:
            excluded.append(rel)
    save({'version': 1, 'policy': 'Explicit approvals only; new runtime res targets must be flat.', 'assets': assets})
    report = ROOT / 'reports/runtime-assets'
    report.mkdir(parents=True, exist_ok=True)
    (report / 'excluded.json').write_text(json.dumps(excluded, indent=2), encoding='utf-8')
    selected = sum((ROOT / 'Resources' / a['target']).stat().st_size for a in assets)
    total = sum(p.stat().st_size for p in (ROOT / 'Resources').rglob('*') if p.is_file())
    print(f'{len(assets)} approved files, {selected/2**20:.1f} MiB; {len(excluded)} excluded; before {total/2**20:.1f} MiB')


def stage(output, prune=False):
    data = load()
    header = ROOT / 'Classes/ApprovedRuntimeImages.h'
    names = sorted(a['target'] for a in data['assets'] if a['target'].startswith('res/'))
    code = ('// Generated from content/runtime-assets.json by runtime_assets.py stage.\n'
            '#pragma once\n#include <string>\n#include <unordered_set>\n'
            'inline bool RuntimeImageApproved(const std::string& name) {\n'
            ' static const std::unordered_set<std::string> names = {\n'
            + ''.join('  ' + json.dumps(name) + ',\n' for name in names)
            + ' };\n return names.count(name) != 0;\n}\n')
    header.parent.mkdir(parents=True, exist_ok=True)
    if not header.exists() or header.read_text(encoding='utf-8') != code:
        header.write_text(code, encoding='utf-8')
    output = inside(output, ROOT)
    if output == ROOT or output.is_relative_to(ROOT / 'asset_library'):
        raise ValueError('Output cannot be the workspace or authoring library')
    if prune:
        relative = output.relative_to(ROOT)
        permitted = {'build', 'output', 'proj.android', 'proj.win32', 'proj.linux', 'proj.ios_mac'}
        if not relative.parts or (relative.parts[0] not in permitted and not relative.parts[0].startswith('cmake-build')):
            raise ValueError('Pruning is restricted to generated build directories')
    output.mkdir(parents=True, exist_ok=True)
    targets = {a['target'] for a in data['assets']}
    # Only remove assets owned by this explicit catalog. Never recursively delete.
    state = output.with_name(output.name + '.runtime-assets-state.json')
    legacy_state = output / '.runtime-assets-state.json'
    if legacy_state.exists():
        if not state.exists(): shutil.copy2(legacy_state, state)
        legacy_state.unlink()
    previous = json.loads(state.read_text()) if state.exists() else []
    for old in set(previous) - targets:
        p = inside(output / old, output)
        if p.is_file():
            p.unlink()
    total = 0
    for a in data['assets']:
        source = ROOT / a['source']
        dest = inside(output / a['target'], output)
        total += source.stat().st_size
        if source.resolve() == dest:
            continue
        dest.parent.mkdir(parents=True, exist_ok=True)
        if not dest.exists() or (dest.stat().st_size, dest.stat().st_mtime_ns) != (source.stat().st_size, source.stat().st_mtime_ns):
            shutil.copy2(source, dest)
    # Retain only bundled entries actually approved here. This is the existing
    # updater manifest format; a full CDN fingerprint refresh stays make_manifest's job.
    bundled = ROOT / 'Resources/manifest.tsv'
    if bundled.exists():
        lines = [line for line in bundled.read_text(encoding='utf-8').splitlines()
                 if line.startswith(('#', 'version\t')) or line.split('\t')[0] in targets]
        (output / 'manifest.tsv').write_text('\n'.join(lines) + '\n', encoding='utf-8')
    state.write_text(json.dumps(sorted(targets)), encoding='utf-8')
    extras = [p.relative_to(output).as_posix() for p in output.rglob('*') if p.is_file()
              and p.relative_to(output).as_posix() not in targets | {'manifest.tsv'}]
    if extras and prune:
        if output == ROOT / 'Resources':
            raise ValueError('Do not prune development Resources; archive unexpected files instead')
        for rel in extras:
            inside(output / rel, output).unlink()
        extras = []
    if extras:
        raise RuntimeError('Unapproved files in runtime output: ' + ', '.join(extras[:12]))
    # Removing the last catalog-owned file must also remove its generated folder.
    # rmdir only succeeds for empty directories; it never deletes unowned files.
    for folder in sorted((p for p in output.rglob('*') if p.is_dir()), key=lambda p: len(p.parts), reverse=True):
        if not any(folder.iterdir()):
            try:
                folder.rmdir()
            except OSError as error:
                if output != ROOT / 'Resources' or getattr(error, 'winerror', None) != 32:
                    raise
                print(f'EMPTY DIRECTORY LOCKED by another application: {folder}', flush=True)
    print(f'STAGED {len(targets)} approved files, {total/2**20:.1f} MiB -> {output}', flush=True)


def add(source, name):
    if Path(name).name != name or '/' in name or '\\' in name or Path(name).suffix.lower() not in EXTENSIONS:
        raise ValueError('Use a flat runtime filename, e.g. hero-room-11.png')
    data = load()
    target = 'res/' + name
    if any(a['target'] == target for a in data['assets']):
        raise ValueError('Already approved; update its library source instead')
    dest = ROOT / 'asset_library/production' / name
    dest.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, dest)
    data['assets'].append({'source': dest.relative_to(ROOT).as_posix(), 'target': target})
    save(data)
    print(f'Approved {target}; run stage to publish it')


def check(output):
    data = load()
    output = inside(output, ROOT)
    expected = {a['target'] for a in data['assets']} | {'manifest.tsv'}
    actual = {p.relative_to(output).as_posix() for p in output.rglob('*') if p.is_file()}
    if actual != expected:
        raise ValueError(f'Runtime output differs from catalog: missing={sorted(expected-actual)[:10]}, extra={sorted(actual-expected)[:10]}')
    nested = [p for p in (output / 'res').rglob('*') if p.is_dir()]
    if nested:
        raise ValueError(f'Runtime res still has subdirectories: {nested[:5]}')
    for asset in data['assets']:
        source, target = ROOT / asset['source'], output / asset['target']
        if source.resolve() != target.resolve() and hashlib.sha256(source.read_bytes()).digest() != hashlib.sha256(target.read_bytes()).digest():
            raise ValueError(f'Stale or altered runtime copy: {asset["target"]}')
    size = sum((output / a['target']).stat().st_size for a in data['assets'])
    print(f'PASS {len(data["assets"])} exact approved runtime files, flat res, no extras; {size/2**20:.1f} MiB')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest='command', required=True)
    sub.add_parser('bootstrap')
    c = sub.add_parser('check'); c.add_argument('--output', type=Path, default=ROOT / 'Resources')
    s = sub.add_parser('stage'); s.add_argument('--output', type=Path, default=ROOT / 'Resources'); s.add_argument('--prune', action='store_true')
    a = sub.add_parser('add'); a.add_argument('source', type=Path); a.add_argument('--name', required=True)
    args = parser.parse_args()
    if args.command == 'bootstrap': bootstrap()
    elif args.command == 'check': check(args.output)
    elif args.command == 'stage': stage(args.output, args.prune)
    else: add(args.source, args.name)


if __name__ == '__main__':
    main()
