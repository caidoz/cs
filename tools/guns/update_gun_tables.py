# -*- coding: utf-8 -*-
"""Update content/equip_value.tsv, content/item_price.tsv, content/item_star.tsv
for 35 guns.
"""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

GUN_VALUES_35 = [
    10, 11, 13, 15, 17, 20, 23, 26, 30, 34, 39, 44, 51, 58, 67, 76,
    87, 100, 114, 131, 150, 172, 197, 225, 258, 295, 338, 387, 443,
    508, 581, 665, 762, 872, 999
]

GUN_PRICES_35 = [
    1000, 1500, 2000, 2800, 3800, 5000, 6500, 8000, 10000, 12500,
    15500, 19000, 23000, 28000, 34000, 41000, 49000, 58000, 68000,
    79000, 92000, 106000, 122000, 140000, 160000, 180000, 200000,
    220000, 240000, 260000, 280000, 300000, 320000, 340000, 360000
]

GUN_STARS_35 = (
    [100] * 5 +
    [200] * 5 +
    [300] * 5 +
    [400] * 5 +
    [500] * 4 +
    [600] * 11
)


def update_tsv(tsv_path, gun_list, col_name):
    lines = tsv_path.read_text(encoding='utf-8').splitlines()
    header_lines = []
    data_rows = []
    for line in lines:
        if line.startswith('#') or line.startswith('id\t'):
            header_lines.append(line)
        elif line.strip():
            parts = line.split('\t')
            data_rows.append(parts)

    # Swords are index 0..34 (35 items)
    # Guns are index 35..42 (8 items) -> replace with 35 items
    # Remaining items are index 43..
    sword_rows = data_rows[:35]
    gun_old_rows = data_rows[35:43]
    after_rows = data_rows[43:]

    assert len(sword_rows) == 35, f"Expected 35 swords, got {len(sword_rows)}"
    assert len(gun_old_rows) == 8, f"Expected 8 guns, got {len(gun_old_rows)}"

    new_gun_rows = []
    for i, val in enumerate(gun_list):
        new_gun_rows.append(['', '', '', str(val)])

    all_data = sword_rows + new_gun_rows + after_rows
    # re-index id column
    out_lines = list(header_lines)
    for new_id, row in enumerate(all_data):
        row[0] = str(new_id)
        out_lines.append('\t'.join(row))

    tsv_path.write_text('\n'.join(out_lines) + '\n', encoding='utf-8')
    print(f"Updated {tsv_path.name}: {len(data_rows)} -> {len(all_data)} rows")


def main():
    update_tsv(ROOT / 'content/equip_value.tsv', GUN_VALUES_35, 'value')
    update_tsv(ROOT / 'content/item_price.tsv', GUN_PRICES_35, 'price')
    update_tsv(ROOT / 'content/item_star.tsv', GUN_STARS_35, 'star')


if __name__ == '__main__':
    main()

