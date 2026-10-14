# Castle popup redesign

The castle popup covers all five main navigation tabs and owns their input area. The common top currency bar remains visible. Closing the popup restores the navigation.

The assembly uses `CastlePartsRoomScale()`, the same scale as battle. Its current visible bounds are centered at screen X; its full assembly height is centered at screen Y. Large castles keep this scale and support vertical swipes within the preview rather than shrinking. Part buttons connect to renderer-provided roof, wall, interior, cannon and chassis anchors. The same buttons switch to the five room upgrades.

The inventory preview reads the battle grid coordinates directly. All physical cells are available positions; the weapon room separately limits the **total occupied cells**, so the preview does not invent individually locked cells.

## Combat rating

Castle rating equals structural rating + projected hero stats + projected active crew stats + cannon damage-per-second contribution. Structural rating is `(castle index + 1) * 1000 + equipment capacity * 25 + (castle index + 1) * sum(part levels * 100 + room levels * 80)`. The rating is a comparison score, not damage; the separate cannon damage/hit-count/cooldown labels show combat values. Upgrade pages compare current and next rating.

## Currency rules

- Gold castle purchase costs `paid castle price * 100` and retains the previous castle's completed-part requirement.
- Paid instant castle purchase retains sequential castle ownership but bypasses the completed-part requirement.
- Gold part/room upgrades retain existing costs.
- Paid instant part/room upgrades cost `ceil(gold upgrade cost / 100)` and advance one level.
- Ownership, level cap and insufficient balances are checked before spending. Both paths use the existing save/refresh code.
- The gold prerequisite message appears in the center for three seconds after tapping; it is not a permanent purchase-button label.

Validation: standalone model tests cover both purchase routes and upgrades, insufficient balances, upgrade cap and rising structural rating. The UI review clicks the actual gold upgrade, paid upgrade and paid purchase buttons and checks persisted balances after a server save/reload. A separate review captures the first and last castles and both vertical pan directions.
