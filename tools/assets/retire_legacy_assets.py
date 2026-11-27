"""Retire superseded art from the production allowlist; retain every source.

The archived catalog records the renderer evidence for each removal. No artwork
is deleted here. Run runtime_assets.py stage to update generated runtime copies.
"""
import argparse
import fnmatch
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
RULES = [
    ('res/diorama*.png', 'Every former diorama draw now calls the shared basic castle preview; no separate castle thumbnails are loaded.'),
    ('res/shop_banner_*.png', 'ShopIapDrawTabbed is uncalled; the current ShopSpec draws pixel panels and current product art.'),
    ('res/lobby_landscape.png', 'Current LobbyDraw returns from MergeRouletteLobbySceneDraw before the predecessor sky renderer.'),
    ('res/lobby_cloud.png', 'Current LobbyDraw returns from MergeRouletteLobbySceneDraw before the predecessor sky renderer.'),
    ('res/lobby_foothills.png', 'Current LobbyDraw returns from MergeRouletteLobbySceneDraw before the predecessor sky renderer.'),
    ('res/login_*.png', 'Unregistered files: absent from Text image names and all current drawing callers; TitleLogin uses generated pixel controls.'),
    ('res/t.png', 'GetResourceName overrides TITLE_IMG with hybrid_sd3d-title-scene.png; the old title slot is never selected.'),
    ('res/castle_room_integrated_v4-*', 'User removed the obsolete two-castle duel. Current MergeSiege uses MistCastle hulls and castle_four_rooms_v5 facilities.'),
    ('res/castle_soft_sectors_v1-*', 'User removed the obsolete two-castle duel, its facade/wheel/cannon renderer. Current siege shares the basic MistCastle renderer.'),
    ('res/castle_map_icons-*', 'Obsolete two-castle universe/VS entrance removed; no current drawing callers remain.'),
    ('res/inventory_cannon-atlas.png', 'Only used below the successful DrawIndividualCastle return in the archived modular renderer; current inventory uses CANNON_UPGRADE_ATLAS_IMG.'),
    ('res/castle_room_integrated_v4-castle-10.png', 'FacilityImage selects CASTLE_FINAL_ROOM_FIRST_IMG+level for castle 10; this predecessor slot is never selected.'),
    ('res/merge_castle_rebuild-ui-navigation.png', 'MergeCastleArt::Navigation has no drawing callers; current navigation is generated pixel UI.'),
    ('res/castle_exterior/*', 'CastleModularDebug.h: DrawCastle returns from DrawIndividualCastle before modular exterior; CS_LEGACY_CASTLE_ART comparison only.'),
    ('res/castle_sd*legacy/*', 'CastleModularDebug.h: DrawSdCastle is superseded by DrawIndividualCastle in the default renderer.'),
    ('res/stage_sd3d_v2/*', 'StageBackground.h: Img selects STAGE_MIST for all three terrain layers; Boss returns before loading old landmarks.'),
    ('res/bg[0-9]*_far.png', 'Superseded STAGEBG terrain; StageBackground::Img selects STAGE_MIST instead.'),
    ('res/bg[0-9]*_mid.png', 'Superseded STAGEBG terrain; StageBackground::Img selects STAGE_MIST instead.'),
    ('res/bg[0-9]*_rail.png', 'Superseded STAGEBG terrain; StageBackground::Img selects STAGE_MIST instead.'),
    ('res/bg[0-9]*_boss*.png', 'StageBackground::Boss returns before any legacy landmark load for the current STAGE_MIST terrain.'),
    ('res/hybrid_sd3d/fleet-*', 'HybridStarterCastle.inc: historical fleet renderer, superseded by DrawIndividualCastle.'),
    ('res/hybrid_sd3d/castles-*-v2.png', 'HybridStarterCastle.inc: historical starter renderer, superseded by DrawIndividualCastle.'),
    ('res/hybrid_sd3d/parts.png', 'Historical HybridStarterCastle renderer is superseded by DrawIndividualCastle.'),
    ('res/hybrid_sd3d/wheels.png', 'Historical HybridStarterCastle renderer is superseded by DrawIndividualCastle.'),
    ('res/hybrid_sd3d/ui.png', 'Func_Graphics.cpp: DrawRenewalPanel uses generated pixel geometry; old bitmap is CS_METAL_UI_REVIEW only.'),
    ('res/hybrid_sd3d/far.png', 'StageBackground::Img selects STAGE_MIST; no current draw requests HYBRID_FAR_IMG.'),
    ('res/hybrid_sd3d/mid-v2.png', 'StageBackground::Img selects STAGE_MIST; no current draw requests HYBRID_MID_IMG.'),
    ('res/hybrid_sd3d/rail.png', 'StageBackground::Img selects STAGE_MIST; no current draw requests HYBRID_RAIL_IMG.'),
    ('res/merge_castle_rebuild/chassis-*', 'MergeCastleMenuArt.inc: RebuildPreview returns from MergeRouletteOriginalPreview for all valid castles.'),
    ('res/merge_castle_rebuild/parts-*', 'CastleFourFacilityMenu.inc: current facilities use MistCastle previews and registered cannon art; old RebuildPreview fallback is inactive.'),
    ('res/merge_castle_rebuild/front-cover-*', 'MergeCastleLobbyRebuild.inc: drawBattleCover uses MistCastle::image(c,8); MergeCastleFronts::Image has no callers.'),
    ('res/merge_castle_rooms/*', 'MERGE_ROOM_FIRST_IMG and MERGE_CASTLE_STRUCTURE_IMG have no drawing callers; current rooms are castle_four_rooms_v5.'),
    ('res/castle_pixel_01_v1/*', 'MergeCastleOriginal.inc: pixelHull/pixelPart are uncalled predecessor helpers; current world uses MistCastle.'),
    ('res/castle_interiors_v3/*', 'CastleModularDebug.h: rectangular-room branch is behind !SoftCastle::Enabled(); default uses integrated facility art.'),
    ('res/castle_functional_sectors_v2/*', 'CASTLE_FUNCTIONAL_FIRST_IMG has no drawing callers; current facility art is castle_room_integrated_v4.'),
    ('res/castle_upgrades_v1/*', 'DrawIndividualUpgradeWheel is used only when SoftCastle::Enabled() is false; default wheels use CASTLE_SOFT_WHEELS_IMG.'),
    ('res/castle_mobility/*', 'Old modular chassis/engines are below the successful DrawIndividualCastle return in DrawCastle.'),
    # 2026-11-26 full audit (image index -> file map + live call sites after dead-function removal).
    ('res/item_boots_*.png', 'DrawBootsInBox/Rot return from DrawGridItemInBox first; GridItems::FromItem covers every boots type/detail 0-7 and all 225 grid_items exist, so the ITEM_BOOTS_* fallback is never reached.'),
    ('res/item_pants_*.png', 'DrawPantsInBox returns from DrawGridItemInBox first; the ITEM_PANTS_* fallback is never reached.'),
    ('res/item_glove_*.png', 'DrawGloveInBox returns from DrawGridItemInBox first; the ITEM_GLOVE_* fallback is never reached.'),
    ('res/item_armor_*.png', 'DrawArmorInBox returns from DrawGridItemInBox first; the ITEM_ARMOR_* fallback is never reached.'),
    ('res/item_vest_*.png', 'DrawArmorInBox returns from DrawGridItemInBox first; the ITEM_VEST_* fallback is never reached.'),
    ('res/item_coat_*.png', 'DrawArmorInBox returns from DrawGridItemInBox first; the ITEM_COAT_* fallback is never reached.'),
    ('res/inventory_helm-*.png', 'GridTest item draw returns from DrawGridItemInBox for ITEM_SWORD..ITEM_BOOTS before the INVENTORY_HELM_* branch.'),
    ('res/inventory_gun-*.png', 'GridTest item draw returns from DrawGridItemInBox before the INVENTORY_GUN_* branch; the two *_art files have no image index or filename reference at all.'),
    ('res/inventory_boomerang-*.png', 'GridTest item draw returns from DrawGridItemInBox before the INVENTORY_BOOMERANG_* branch.'),
    ('res/button.png', 'BUTTON_IMG has no reference outside ImgDef.h.'),
    ('res/cloud.png', 'CLOUD_IMG has no reference outside ImgDef.h.'),
    ('res/gacha.png', 'GACHA_IMG has no reference outside ImgDef.h.'),
    ('res/shop_cash_coin.png', 'SHOP_CASH_COIN_IMG is only inside the boot preload range; nothing draws it.'),
    ('res/num.png', 'NUM_IMG was only loaded; every number draw uses NUM2_IMG (num2.png).'),
]


def retire(apply=False):
    catalog_path = ROOT / 'content/runtime-assets.json'
    archive_path = ROOT / 'content/archived-runtime-assets.json'
    catalog = json.loads(catalog_path.read_text(encoding='utf-8'))
    archived = json.loads(archive_path.read_text(encoding='utf-8')) if archive_path.exists() else {
        'version': 1, 'policy': 'Authoring/reference only. Excluded from every production build.', 'assets': []}
    kept, removed = [], []
    for asset in catalog['assets']:
        reason = next((reason for pattern, reason in RULES if fnmatch.fnmatchcase(asset['target'], pattern)), None)
        if reason:
            source = (ROOT / asset['source']).resolve()
            if not source.is_relative_to((ROOT / 'asset_library').resolve()) or not source.is_file():
                raise ValueError(f'Cannot retire asset without a preserved external master: {asset}')
            removed.append(dict(asset, reason=reason, bytes=source.stat().st_size))
        else:
            kept.append(asset)
    if apply:
        catalog['assets'] = kept
        archived['assets'].extend(removed)
        archived['assets'].sort(key=lambda a: a['target'])
        archive_path.write_text(json.dumps(archived, indent=2) + '\n', encoding='utf-8')
        catalog_path.write_text(json.dumps(catalog, indent=2) + '\n', encoding='utf-8')
    print(f"{'RETIRED' if apply else 'CANDIDATES'} {len(removed)} files, {sum(a['bytes'] for a in removed)/2**20:.1f} MiB; preserved masters in asset_library")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--apply', action='store_true')
    retire(parser.parse_args().apply)
