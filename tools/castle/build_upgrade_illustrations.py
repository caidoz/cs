"""Split the generated castle-upgrade concept sheet into runtime UI assets."""

from pathlib import Path
from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
SOURCE = Path(
    r"C:\Users\polyp\.codex\generated_images\01a0ad19-e9c6-79c3-9634-d83b8c4e5d36"
    r"\exec-4c796794-172d-4cd0-928d-d1363f5d5daa.png"
)
OUTPUT = ROOT / "Resources" / "res"


def main() -> None:
    sheet = Image.open(SOURCE).convert("RGBA")
    cell_w = sheet.width // 5
    cell_h = sheet.height // 2
    inset = 5

    for index in range(10):
        column = index % 5
        row = index // 5
        left = column * cell_w + inset
        top = row * cell_h + inset
        right = (column + 1) * cell_w - inset
        bottom = (row + 1) * cell_h - inset
        panel = sheet.crop((left, top, right, bottom))
        panel = panel.resize((384, 384), Image.Resampling.LANCZOS)
        panel.save(OUTPUT / f"castle_upgrade{index}.png", optimize=True)


if __name__ == "__main__":
    main()
