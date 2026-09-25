"""Split the approved lobby UI concept sheet into transparent runtime icons."""

from pathlib import Path
from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
SOURCE = Path(
    r"C:\Users\polyp\.codex\generated_images\01a0ad19-e9c6-79c3-9634-d83b8c4e5d36"
    r"\exec-ce1d29df-1f92-4e2f-8ad5-db961bd2c45e.png"
)
OUTPUT = ROOT / "Resources" / "res"
NAMES = (
    "lobby_nav_shop", "lobby_nav_equip", "lobby_nav_adventure", "lobby_nav_castle",
    "lobby_nav_dungeon", "lobby_energy", "lobby_day", "lobby_night",
)


def main() -> None:
    sheet = Image.open(SOURCE).convert("RGBA")
    cell_w, cell_h = sheet.width // 4, sheet.height // 2
    for index, name in enumerate(NAMES):
        col, row = index % 4, index // 4
        cell = sheet.crop((col * cell_w, row * cell_h,
                           (col + 1) * cell_w, (row + 1) * cell_h))
        bounds = cell.getchannel("A").getbbox()
        if bounds is None:
            raise ValueError(f"empty icon cell {index}")
        art = cell.crop(bounds)
        scale = min(116 / art.width, 116 / art.height)
        art = art.resize((round(art.width * scale), round(art.height * scale)),
                         Image.Resampling.LANCZOS)
        icon = Image.new("RGBA", (128, 128))
        icon.alpha_composite(art, ((128 - art.width) // 2, (128 - art.height) // 2))
        icon.save(OUTPUT / f"{name}.png", optimize=True)


if __name__ == "__main__":
    main()
