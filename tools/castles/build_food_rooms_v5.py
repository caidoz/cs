"""Build base + five farm upgrades with an unobstructed character walkway."""
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "content/castles/modular_v5/food_room"
RUNTIME = ROOT / "Resources/res/castle_rooms_v5"


def alpha_box(image: Image.Image):
    return image.getchannel("A").point(lambda v: 255 if v > 128 else 0).getbbox()


def exact_four_to_one(image: Image.Image) -> Image.Image:
    image = image.crop(alpha_box(image))
    w, h = image.size
    wanted_w = h * 4
    if w > wanted_w:
        # Remove only the tiny symmetric overrun (about 1.5% for stage 2).
        cut = w - wanted_w
        image = image.crop((cut//2, 0, cut//2+wanted_w, h))
    elif w < wanted_w:
        canvas = Image.new("RGBA", (wanted_w, h))
        canvas.alpha_composite(image, ((wanted_w-w)//2, 0))
        image = canvas
    return image.resize((512, 128), Image.Resampling.LANCZOS)


def build() -> None:
    RUNTIME.mkdir(parents=True, exist_ok=True)
    sheet = Image.open(SOURCE / "farm_6stage_clear_walkway.png").convert("RGBA")
    if sheet.size != (1024, 1536):
        raise ValueError(f"expected 1024x1536 six-row master, got {sheet.size}")
    rooms = {}
    for stage in range(6):
        # Each authored row is natively 1024x256 (exactly 4:1).
        row = sheet.crop((0, stage*256, 1024, (stage+1)*256))
        rooms[stage] = row.resize((512, 128), Image.Resampling.LANCZOS)

    for stage in range(6):
        name = f"food_room_stage_{stage}.png"
        rooms[stage].save(SOURCE / name, optimize=True)
        rooms[stage].save(RUNTIME / name, optimize=True)

    preview = Image.new("RGBA", (512, 6*128), (20, 29, 35, 255))
    for stage in range(6):
        preview.alpha_composite(rooms[stage], (0, stage*128))
    preview.save(SOURCE / "food_room_6_stages_stacked.png", optimize=True)
    print("built 6 farm states: exact 512x128, zero-gap stack, continuous walkway")


if __name__ == "__main__":
    build()
