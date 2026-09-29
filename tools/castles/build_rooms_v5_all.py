"""Build the ten room themes as 60 fixed 512x128 runtime sprites."""
from pathlib import Path
from PIL import Image, ImageDraw


ROOT = Path(__file__).resolve().parents[2]
SOURCE_ROOT = ROOT / "content/castles/modular_v5"
RUNTIME = ROOT / "Resources/res/castle_rooms"
ROOM_SIZE = (512, 128)
MASTER_SIZE = (1024, 1536)

THEMES = (
    ("floor_01_food", "food_room/farm_6stage_clear_walkway.png"),
    ("floor_02_blacksmith", "floor_02_blacksmith/master_6stage.png"),
    ("floor_03_residential", "floor_03_residential/master_6stage.png"),
    ("floor_04_restaurant", "floor_04_restaurant/master_6stage.png"),
    ("floor_05_department_store", "floor_05_department_store/master_6stage.png"),
    ("floor_06_spa", "floor_06_spa/master_6stage.png"),
    ("floor_07_science", "floor_07_science/master_6stage.png"),
    ("floor_08_biotech", "floor_08_biotech/master_6stage.png"),
    ("floor_09_library", "floor_09_library/master_6stage.png"),
    ("floor_10_imperial", "floor_10_imperial/master_6stage.png"),
)


def build() -> None:
    RUNTIME.mkdir(parents=True, exist_ok=True)
    catalog = Image.new("RGBA", (6 * 256, 10 * 64), (20, 29, 35, 255))
    draw = ImageDraw.Draw(catalog)
    count = 0

    for floor_index, (theme, relative_master) in enumerate(THEMES, start=1):
        master_path = SOURCE_ROOT / relative_master
        master = Image.open(master_path).convert("RGBA")
        if master.size != MASTER_SIZE:
            raise ValueError(f"{master_path}: expected {MASTER_SIZE}, got {master.size}")

        output_dir = SOURCE_ROOT / theme
        output_dir.mkdir(parents=True, exist_ok=True)
        for stage in range(6):
            row = master.crop((0, stage * 256, 1024, (stage + 1) * 256))
            room = row.resize(ROOM_SIZE, Image.Resampling.LANCZOS)
            source_path = output_dir / f"stage_{stage}.png"
            runtime_path = RUNTIME / f"floor_{floor_index:02d}_stage_{stage}.png"
            room.save(source_path, optimize=True)
            room.save(runtime_path, optimize=True)
            if Image.open(runtime_path).size != ROOM_SIZE:
                raise ValueError(f"bad runtime size: {runtime_path}")
            catalog.alpha_composite(room.resize((256, 64), Image.Resampling.LANCZOS),
                                    (stage * 256, (floor_index - 1) * 64))
            count += 1

    if count != 60:
        raise ValueError(f"expected 60 rooms, built {count}")
    catalog_path = SOURCE_ROOT / "rooms_10x6_catalog.png"
    catalog.save(catalog_path, optimize=True)
    print(f"built {count} rooms at 512x128; catalog={catalog_path}")


if __name__ == "__main__":
    build()
