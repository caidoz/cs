# -*- coding: utf-8 -*-
"""
tools/boomerangs/update_boomerang_tables.py
Expands boomerangs from 8 items to 35 items in:
- content/equip_value.tsv (198 -> 225 rows, +27)
- content/item_price.tsv (355 -> 382 rows, +27)
- content/item_star.tsv (592 -> 619 rows, +27)
"""
import os

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

# 35 equip values (matching swords and guns curve)
BOOMERANG_EQUIP_VALUES = [
    10, 11, 13, 15, 17, 20, 23, 26, 30, 34,
    39, 44, 51, 58, 67, 76, 87, 100, 114, 131,
    150, 172, 197, 225, 258, 295, 338, 387, 443, 508,
    581, 665, 762, 872, 999
]

# 35 item prices (scaling smoothly from 1100 to 365000)
BOOMERANG_PRICES = [
    1100, 1700, 2500, 3600, 4800, 6500, 8500, 11000, 14000, 17500,
    21500, 26000, 31000, 37000, 43000, 50000, 58000, 67000, 77000, 88000,
    100000, 114000, 129000, 145000, 165000, 185000, 205000, 225000, 245000, 265000,
    285000, 305000, 325000, 345000, 365000
]

# 35 stars: 5x100, 5x200, 5x300, 5x400, 4x500, 11x600
BOOMERANG_STARS = [100]*5 + [200]*5 + [300]*5 + [400]*5 + [500]*4 + [600]*11

def update_table(tsv_rel_path, new_values, old_cnt=8, new_cnt=35, boomerang_start=70):
    path = os.path.join(ROOT, tsv_rel_path)
    with open(path, "r", encoding="utf-8") as fp:
        lines = fp.readlines()

    header_lines = []
    data_rows = []
    for line in lines:
        if line.startswith("#") or line.startswith("id\t"):
            header_lines.append(line)
        elif line.strip():
            parts = line.rstrip("\r\n").split("\t")
            data_rows.append(parts)

    print(f"[{tsv_rel_path}] Original data rows: {len(data_rows)}")
    
    # 0..69: swords (0..34) and guns (35..69)
    prefix_rows = data_rows[:boomerang_start]
    # 70..77: old boomerangs
    old_boomerang_rows = data_rows[boomerang_start:boomerang_start + old_cnt]
    # 78..end: items after boomerangs
    suffix_rows = data_rows[boomerang_start + old_cnt:]

    print(f"  Prefix rows (swords + guns): {len(prefix_rows)}")
    print(f"  Old boomerang rows: {len(old_boomerang_rows)}")
    print(f"  Suffix rows: {len(suffix_rows)}")

    # Build new boomerang rows
    new_boomerang_rows = []
    for i, val in enumerate(new_values):
        row_id = boomerang_start + i
        # Format: id \t enum_name \t label \t value
        row = [str(row_id), "", "", str(val)]
        new_boomerang_rows.append(row)

    # Reindex suffix rows (+27)
    delta = new_cnt - old_cnt
    reindexed_suffix = []
    for parts in suffix_rows:
        old_id = int(parts[0])
        new_id = old_id + delta
        new_parts = [str(new_id)] + parts[1:]
        reindexed_suffix.append(new_parts)

    all_rows = prefix_rows + new_boomerang_rows + reindexed_suffix
    print(f"  New total rows: {len(all_rows)} (+{delta})")

    # Write back
    with open(path, "w", encoding="utf-8", newline="") as fp:
        for h in header_lines:
            fp.write(h)
        for r in all_rows:
            fp.write("\t".join(r) + "\n")

    print(f"Updated {tsv_rel_path} successfully!\n")

def main():
    update_table("content/equip_value.tsv", BOOMERANG_EQUIP_VALUES)
    update_table("content/item_price.tsv", BOOMERANG_PRICES)
    update_table("content/item_star.tsv", BOOMERANG_STARS)

if __name__ == "__main__":
    main()

