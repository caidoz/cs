# Shop implementation audit — 2026-10-29

## Existing paths

- `Func_Input.cpp`: lobby shop → `AVK_SHOP` → `POPUPTYPE_SHOPINFO`; currency shortcuts call `ShopJumpToIapSection`. `Func_Menu.cpp::ShopDraw/ShopIapDraw` currently implement a single scrolling list with a castle upgrade link, six gold/energy/premium bundles, six existing gold-priced boxes and pass/starter/inventory IAP entries. The current category shortcuts scroll rather than switch fixed tabs.
- Existing currencies: `robin.gold`, `robin.coin` (rainbow/premium), `robin.heart` (energy). `GetBoxPrice` and `rewardBoxData`/`GachaData` define existing generic boxes. They do **not** define priced hero-specific weapon/armor/companion/special shop SKUs.
- `Func_Iap.cpp`: pending journal (`purchase.dat`), transaction/order IDs, retries and server-owned grants exist. Windows uses a fake store; mobile `IapStoreBuy` is unimplemented. `server/go/purchase.go` has transactional grants and order deduplication but its verifier is an allow-all placeholder. Thus no live cash purchase is currently verified end-to-end. `ShopPriceText` currently invents fallback KRW prices; remove these.
- `IAP_INVEN_20` is a legacy identifier. Preserve its numeric position/save and pending-journal compatibility, but forbid new exposure/purchases. Existing pending transactions must still be recoverable.
- Pass timestamps and effects exist; no confirmed live store connection or ad-removal SDK was found. Hide unconnected live IAP/ads; never advertise fake purchase as production-ready.

## Castle and storage

- `CastleMenuModel.h`: ten castle stages; current ownership unlock requires the preceding castle's parts at level five for gold purchase. Existing `GoldPrice`, `UpgradeCost`, part/room state and `Migrate` must remain authoritative. Runtime currently also offers premium instant purchase/upgrade; remove those paths from the UI/commands under the gold-only rule.
- `CastleMenuRuntime.inc::CastleSaveChanges`: update max inventory, refresh all heroes and save. `CastleInventoryCapacity`, `CastleEquipmentCapacity`, grid masks and selected castle derive expanded capacity automatically. Keep existing progression requirements/costs; do not invent a replacement level curve.
- `Core.h::ROBINDATA`, cereal serialization and `Func_Net.cpp` TSV encode persistent inventory, castle progress and `freeRewardTimeStamp`. No save-structure change is necessary for inactive/unpriced proposed SKUs.
- Existing free reward timestamp and 18-hour `FREEITEMTIME` are legacy scheduling only. No authoritative daily shop reward amount, midnight reset policy or claim API exists. Keep the new daily slot disabled until configured; do not turn the old timer into a fabricated daily economy.
- `Func_Item.cpp::GetItem`: equipment gets independent inventory instances, materials can stack; capacity exhaustion returns failure and shows notice. Existing box animation grants items later; gold currently deducts before rewards are delivered, so reserve/check worst-case capacity and prevent duplicate confirmation. Do not add new purchasable inventory expansion.
- Additional finding during grant tests: `MakeItem` explicitly normalizes all stored item grades to zero. Preserve this existing policy; result UI must display the stored instance rather than an intermediate rolled grade. Dedicated supply grade distributions cannot be advertised until this policy is approved/reconciled.
- `Func_Battle.cpp::StageRunEquipmentEnd` restores permanent equipment/inventory snapshots and clears the run grid. Four-choice run purchases remain in run-local grid/storage, separate from `robin.inven`. Do not rewrite this ownership boundary. Permanent shop grant entry points must reject active runs rather than write into a snapshot that will be restored.

## UI and implementation plan

- Coordinates use bottom-origin Y with top-edge rectangle coordinates. Shop owns the full screen below resource bars, including former bottom navigation; only body content scrolls. `SetSectionClip` also clips purchase touch areas. Verify 640×850 and 640×1400, fixed tabs, hidden dock input and scroll endpoints.
- Reuse existing pixel panels, NeoDunggeunmo, actual item/crew icons and catalog text. No art generation. Use real `crewData`/`GetItemDetail` identities; do not introduce temporary ally names.
- Add a small shop catalog/model with stable textual product IDs and explicit availability/hero/ownership fields. Reuse existing generic boxes as available products; dedicated supplies show actual filtered pools and an unavailable state until prices/rates are approved. Development-only fixed grants are self-test fixtures, never live purchase buttons.
- Expected changes: new `ShopCatalogModel.h`, `ShopRuntime.inc`, config/header API; `Func_Menu.cpp`, `Func_Input.cpp`, `Func_Iap.*`, `CastleMenuRuntime.inc`, review hooks/scripts, model tests and report. Preserve IAP journals, SKU enums, reward tables, server grant/restore paths, save serialization and existing run equipment handling.

## OPEN_QUESTIONS

1. Daily reward amount and reset policy are not defined. Disabled configuration is required.
2. Dedicated hero supply prices and probabilities are undefined. Do not derive them from unrelated generic boxes or manufacture premium prices.
3. Live store SDK, verified receipt service, refunds/restore and server-authoritative free claims are incomplete; document separately from existing development fake store.
4. Existing castle stages are ten owned selectable castles with per-part requirements, not a new scalar level field. Preserve this save-compatible representation and gold cost table.
5. Purchased box animation has a crash window between charge and grant. Add persistent pending-box recovery using existing save fields/transaction record rather than pretending animation is an atomic grant.
