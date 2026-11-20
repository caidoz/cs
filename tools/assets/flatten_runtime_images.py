"""Retire reviewed predecessors and migrate existing image IDs to flat res names.

No artwork is edited or deleted from the external library. The draw audit is a
veto against retirement, not an automatic unused-file detector.
"""
from pathlib import Path
import argparse
import fnmatch
import json
import re

ROOT = Path(__file__).resolve().parents[2]
RULES = [
    ('res/castle_individual_v4/*', 'CastleModularDebug.h: predecessor textures load only when !SoftCastle::Enabled(); production uses integrated art, including PVP.'),
    ('res/castle_cannon_v2/unarmed-*', 'DrawIndividualCastle: baseImg is loaded/drawn only when !soft; production uses FacilityImage.'),
    ('res/castle_room_*.png', 'CastleModularDebug.h: legacy rectangular rooms are below successful integrated DrawIndividualCastle; current menus use MergeRouletteOriginalPreview.'),
    ('res/castle_crew_decks/*', 'CASTLE_CREW_DECK_FIRST_IMG has no drawing callers; crew positions use rig coordinates.'),
    ('res/castle_mist_v2/*/room-*.png', 'MergeCastleMist.inc: facility() uses MERGE_REBUILD_ROOMS_IMG + castle, not image(castle,1..5).'),
    ('res/merge_castle_original/deck-repair.png', 'MERGE_ORIGINAL_REPAIR_IMG has no drawing callers.'),
    ('res/merge_castle_original/wheel.png', 'OriginalCastle::wheels is uncalled; production calls MistCastle::wheels with individual wheel assets.'),
    ('res/inventory_cannon/castle_*', 'DrawInventoryCannonIcon and thumbnails use CANNON_UPGRADE_ATLAS_IMG; individual exports have no callers.'),
    ('res/turret_attack_v1/*', 'TURRET_LASER_IMG and TURRET_MISSILE_IMG have no drawing callers; production uses turret_attack frame sets.'),
    ('res/battle_ui_v1/*', 'BATTLE_PLUMP_LEVER_IMG has no drawing callers.'),
    ('res/merge_castle_rebuild/ui-attack.png', 'MergeCastleArt::Attack has no drawing callers.'),
    ('res/merge_castle_rebuild/ui-board.png', 'uiArt(Board) branch has no callers; the board uses generated geometry.'),
    ('res/merge_castle_rebuild/ui-continue.png', 'MergeCastleArt::Continue has no drawing callers.'),
    ('res/merge_castle_rebuild/ui-lever.png', 'drawLever is an uncalled predecessor helper.'),
    ('res/merge_castle_rebuild/ui-manage.png', 'MergeCastleArt::Manage has no drawing callers.'),
    ('res/merge_castle_rebuild/ui-nav.png', 'MergeCastleArt::Navigation has no drawing callers.'),
    ('res/merge_castle_rebuild/ui-start.png', 'MergeCastleArt::Start has no drawing callers.'),
    ('res/merge_castle_rebuild/ui-spin.png', 'MergeCastleArt::Spin has no drawing callers.'),
    ('res/shop_card_box.png', 'SHOP_CARD_BOX_IMG has no drawing callers.'),
    ('res/shop_cash_icon.png', 'SHOP_CASH_ICON_IMG has no drawing callers.'),
    ('res/lobby_nav_*.png', 'Navigation is generated pixel UI; these images are referenced only by boot preload and filter ranges.'),
    ('res/lobby_day.png', 'LOBBY_DAY_IMG has no drawing callers.'),
    ('res/lobby_night.png', 'LOBBY_NIGHT_IMG has no drawing callers.'),
    ('res/crewBullet_old.png', 'Historical backup, not registered in Text.h or a drawing path.'),
]


def migrate(apply=False):
    catalog_path = ROOT / 'content/runtime-assets.json'
    data = json.loads(catalog_path.read_text(encoding='utf-8'))
    report_path = ROOT / 'reports/runtime-assets/actual-draw-usage.json'
    usage = json.loads(report_path.read_text(encoding='utf-8'))
    drawn = {a['target'] for a in usage['assets'] if a['drawn_in']}
    mapping = {a['target']: 'res/' + a['target'][4:].replace('/', '-')
               for a in data['assets'] if a['target'].startswith('res/') and a['target'].count('/') > 1}
    targets = [mapping.get(a['target'], a['target']) for a in data['assets']]
    if len(set(targets)) != len(targets):
        raise ValueError('Flat filename collision; resolve names before migration')
    removed, kept = [], []
    for asset in data['assets']:
        name = asset['target']
        reason = next((reason for pattern, reason in RULES if fnmatch.fnmatchcase(name, pattern)
                       and not (pattern == 'res/castle_room_*.png' and name.count('/') != 1)), None)
        m = re.fullmatch(r'res/items/item(\d+)\.png', name)
        if m and 449 <= int(m[1]) < 512:
            reason = 'ItemSeries::FromIcon accepts only 0..448; 449..511 cannot be selected by FromIcon or FromAtlas.'
        if reason:
            if name in drawn:
                raise ValueError(f'Retirement conflicts with actual screen usage: {name}')
            for field in ('source', 'original_source'):
                if field in asset:
                    path = (ROOT / asset[field]).resolve()
                    if not path.is_relative_to((ROOT / 'asset_library').resolve()) or not path.is_file():
                        raise ValueError(f'External master required before retiring {name}')
            removed.append(dict(asset, reason=reason))
        else:
            asset = dict(asset)
            asset['target'] = mapping.get(name, name)
            kept.append(asset)
    # Translate runtime literals and format strings, while preserving source art
    # paths, include names, bytes outside literals and the original line endings.
    prefixes = sorted({old[4:].split('/')[0] for old in mapping}, key=len, reverse=True)
    literal = re.compile(r'"[^"\r\n]*"|\x27[^\x27\r\n]*\x27')
    def translate(match):
        value = match[0]
        inner = value[1:-1]
        for base in ('Resources/res/', 'res/', ''):
            if any(inner.startswith(base + prefix + '/') for prefix in prefixes):
                return value[0] + base + inner[len(base):].replace('/', '-') + value[-1]
        return value
    changed = []
    files = [p for p in (ROOT / 'Classes').rglob('*') if p.suffix in {'.cpp', '.h', '.inc'}]
    files += list((ROOT / 'tools').rglob('verify*.py')) + list((ROOT / 'tools').rglob('verify*.ps1'))
    for path in files:
        before = path.read_bytes()
        after = literal.sub(translate, before.decode('utf-8')).encode('utf-8')
        if after != before:
            changed.append(path.relative_to(ROOT).as_posix())
            if apply:
                path.write_bytes(after)
    report = {'renamed': mapping, 'retired': removed, 'changed_code': changed,
              'retired_bytes': sum((ROOT / a['source']).stat().st_size for a in removed),
              'remaining_image_bytes': sum((ROOT / a['source']).stat().st_size for a in kept if a['target'].startswith('res/'))}
    if apply:
        archive_path = ROOT / 'content/archived-runtime-assets.json'
        archived = json.loads(archive_path.read_text(encoding='utf-8'))
        archived['assets'].extend(removed)
        archive_path.write_text(json.dumps(archived, indent=2) + '\n', encoding='utf-8')
        data['assets'] = sorted(kept, key=lambda a: a['target'])
        data['policy'] = 'Explicit approvals only. Every runtime res target must be flat; no legacy directory exceptions.'
        catalog_path.write_text(json.dumps(data, indent=2) + '\n', encoding='utf-8')
        (ROOT / 'reports/runtime-assets/flat-migration.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
        # Rename manifest IDs before staging filters it; fingerprints are
        # unchanged because the image payloads are unchanged.
        manifest = ROOT / 'Resources/manifest.tsv'
        lines = []
        for line in manifest.read_text(encoding='utf-8').splitlines():
            fields = line.split('\t')
            fields[0] = mapping.get(fields[0], fields[0])
            lines.append('\t'.join(fields))
        manifest.write_text('\n'.join(lines) + '\n', encoding='utf-8')
    print(f'{len(mapping)} flat names, {len(removed)} retired ({report["retired_bytes"]/2**20:.1f} MiB), {len(changed)} source files updated')
    print(f'Remaining images: {report["remaining_image_bytes"]/2**20:.1f} MiB')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--apply', action='store_true')
    migrate(parser.parse_args().apply)
