# Shop implementation report — 2026-10-29

## Implemented

- Replaced the old long category list with **추천 / 보급품 / 패키지**, fixed below the existing currency bars. Only the body scrolls. The shop covers the bottom dock, including its touch rectangles, and retains a fixed back button.
- Recommended: first daily slot, two references to existing generic boxes, then the same four supply catalog entries used by the supply tab. Supplies: independent Robin/Diana/Max filters, four actual-data candidate lists, and six existing generic boxes. Packages: only real connected/localized-price SKUs can appear; currently an honest empty state.
- Existing castle-upgrade banners/actions, paid inventory expansion and guessed KRW fallback prices were removed from the active shop. No new material, floor, grid-slot or repair-part economy was added.
- Candidate detail panels show actual weapon/armor identities per hero, all `gTotalCrew` existing allies, shared necklaces/rings/essences, permanent ownership and existing duplicate behavior. Page controls work without replacing real allies with temporary names. Six-star swords excluded by the existing `IsBoxLockedItem` rule stay excluded.
- Gold-priced generic-box purchase uses existing prices and random reward generation. Validate sufficient gold and **12 empty persistent inventory slots** before any charge. Grant synchronously, restore the complete profile if any grant fails, and save the combined currency/inventory state once through the existing queued whole-profile protocol. No charge is saved while rewards are merely waiting for an animation. The result panel shows actual stored instances and permanent-storage guidance.
- Purchase confirmation is consumed once, concurrent actions are guarded, and rapid repeated requests are rejected. No purchase is accepted while a run equipment snapshot exists, including non-combat overlays, so a permanent grant cannot be overwritten by run teardown.
- Castle acquisition and facilities use existing **gold costs only**. Premium instant actions are blocked even if their old touch IDs are invoked. Successful castle acquisition selects that stage, updates the visual, recalculates capacity via the existing castle functions, refreshes hero stats and queues one save. Existing unlock requirements and room/part cost tables remain intact.

## Catalog and availability

| Product identifiers | Mapping / status |
|---|---|
| `SHOP_DAILY_FREE` | Daily slot; disabled until approved amount/reset configuration exists |
| `SHOP_WEAPON_ROBIN/DIANA/MAX` | Actual sword/gun/boomerang candidates; price/rates pending; viewable, not purchasable |
| `SHOP_ARMOR_ROBIN/DIANA/MAX` | Actual corresponding five armor-type pools; price/rates pending |
| `SHOP_COMPANION` | Existing 64 allies from `crewData`; shared across filters; price/rates pending |
| `SHOP_SPECIAL` | Existing neck/ring/essence data; shared; dedicated supply price/rates pending |
| `BOX_PAID0` … `BOX_PAID5` | Existing generic boxes, existing `GetBoxPrice` gold prices and `GenerateCastleBoxReward` tables |
| Existing `coin_*`, `heart_*`, `cash_*`, `starter`, `pass_*` | Retained existing IDs/journal compatibility; hidden while store/receipt verification is unavailable |
| `inven_20` | Never exposed or accepted for a new purchase; legacy enum/journal identity preserved |

`ShopCatalogModel.h` maps stable catalog IDs, availability, hero filters, reward references, sort order, source `Shop`, and ownership `Persistent`. `RunReward`/`RunTemporary` remain a separate ownership vocabulary; existing run grid/snapshot storage remains authoritative. **No fields were inserted into serialized ITEM or ROBINDATA**, so no save/schema migration is needed. Existing pending IAP journal recovery is retained; new-sale gating does not erase receipts. No server migration or deployment was performed.

## Unresolved policy / unavailable systems

1. `Config/ShopConfig.h` intentionally leaves daily amount/reset at zero and disabled. A claim path and duplicate/time-reversal/cap checks exist using the already serialized `freeRewardTimeStamp`; there is no invented daily reward or reset hour. Old `FREEITEMTIME` was an 18-hour legacy event timer, not an approved daily-shop policy.
2. Dedicated hero weapon/armor/ally/special prices and probabilities are undefined. These are clearly marked **준비 중**, with no paid button. Fixed first-candidate grants run only in an explicit self-test; they do not create live SKUs or a production mock store.
3. Mobile store adapters and production receipt verification are incomplete. `SHOP_STORE_CONNECTED` and `SHOP_RECEIPTS_VERIFIED` stay zero. Cash, ads and unconnected passes are not sold; SDK-localized prices are required before enabling a package. Existing server order deduplication and journal retry code remain unchanged. Refund/restore integration is not claimed complete.
4. Stored grades are currently normalized to zero by existing `MakeItem`, independently of intermediate box rolls. This policy is preserved and result panels reflect stored grades. It must be reconciled before approving dedicated supply grade odds.
5. With no authoritative daily-claim endpoint, eventual daily claims would use the project's existing server-adjusted client time and whole-profile save. Strong multi-device/time-tamper enforcement requires a server claim endpoint; daily claims remain disabled now.
6. Local gold-box updates are a synchronous all-or-rollback **profile transaction**, not a new server-authoritative shop endpoint. Network retries use the existing profile revision protocol; IAP continues to use its existing store order IDs. A new globally replayable gold-purchase API was not fabricated.
7. Capacity failures refuse purchase before payment; no mailbox system was found or invented. Twelve empty slots is a conservative worst-case reservation. Existing unrelated reward/overflow behavior was not rewritten.

## Verification

- `tools/lobby/test_shop_catalog.py`: actual model compiled under MSVC; IDs, hero/common matching, unconfigured purchase gating, daily duplicate/time-reversal checks, ten gold-priced castle stages and automatic capacity growth passed.
- `tools/lobby/verify_shop_spec.ps1`: 640×850 and 640×1400/1408 screenshots; three fixed tabs, Robin/Diana/Max filter taps, candidate detail, packages empty state, bottom scroll, covered dock input, cancel and back passed.
- Runtime integration checks: actual candidate pools, fixed development-only filtered grants, insufficient gold, full storage refusal, successful permanent generic grant, actual stored grade, gold accounting, rapid duplicate rejection, unavailable IAP, actual castle gold purchase/selection/capacity and premium-action rejection passed.
- Actual save dump encoder/decoder compatibility self-test (`CS_CASTLE_PROTOCOL_TEST=1`) passed; no serialized field/order changes were introduced.
- Existing Max/run snapshot regression: see final test log `output/max-weapon-review/phases.log`; permanent/run ownership and four choices are unchanged.

## Files

New: `ShopCatalogModel.h`, `ShopRuntime.inc`, `Config/ShopConfig.h`, model/runtime tests and these audit/report documents. Updated: `Func_Menu.*`, `Func_Input.cpp`, `Func_Iap.*`, `Def/TouchKeyDef.h`, `CastleMenuRuntime.inc`, `CastleMenuReview.inc`. No new artwork, guessed prices, odds, currency or production paid SKU was added.
