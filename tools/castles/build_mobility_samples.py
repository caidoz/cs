"""Build the castle 1 wheel set and castle 7 hover sample at fixed sizes."""
from pathlib import Path
from PIL import Image, ImageChops, ImageDraw, ImageFilter


ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "content/castles/mobility_samples"
RUNTIME = ROOT / "Resources/res/castle_mobility"

BASE_SHEET = Path(r"C:\Users\polyp\.codex\generated_images\01a0de43-6120-72f2-9314-8e5fb074b287\exec-e5a11879-3c18-4766-a3ab-8129a47a5b51.png")
WHEEL_SHEET = Path(r"C:\Users\polyp\.codex\generated_images\01a0de43-6120-72f2-9314-8e5fb074b287\exec-f662a797-486b-43d2-9aa0-1ada2852cf08.png")
HOVER_SHEET = Path(r"C:\Users\polyp\.codex\generated_images\01a0de43-6120-72f2-9314-8e5fb074b287\exec-f0642b05-04f3-4cd2-96f5-1f933f8ae323.png")
CASTLE_07_BASE = Path(r"C:\Users\polyp\.codex\generated_images\01a0de43-6120-72f2-9314-8e5fb074b287\exec-4bcea24c-0dff-422b-b507-f502cacacbab.png")


def clean_alpha(image: Image.Image) -> Image.Image:
    image = image.convert("RGBA")
    alpha = image.getchannel("A").point(lambda value: 0 if value < 8 else value)
    image.putalpha(alpha)
    return image


def contain(image: Image.Image, size: tuple[int, int]) -> Image.Image:
    bbox = image.getchannel("A").getbbox()
    if not bbox:
        raise ValueError("source sprite has no visible pixels")
    image = image.crop(bbox)
    image.thumbnail(size, Image.Resampling.LANCZOS)
    result = Image.new("RGBA", size)
    result.alpha_composite(image, ((size[0] - image.width) // 2, (size[1] - image.height) // 2))
    return result


def save(image: Image.Image, name: str, expected: tuple[int, int]) -> None:
    if image.size != expected:
        raise ValueError(f"{name}: expected {expected}, got {image.size}")
    image.save(SOURCE / name, optimize=True)
    image.save(RUNTIME / name, optimize=True)


def build() -> None:
    SOURCE.mkdir(parents=True, exist_ok=True)
    RUNTIME.mkdir(parents=True, exist_ok=True)

    bases = clean_alpha(Image.open(BASE_SHEET))
    if bases.size != (1448, 1086):
        raise ValueError(f"unexpected base sheet size: {bases.size}")
    for stage in range(6):
        row = bases.crop((0, stage * 181, 1448, (stage + 1) * 181))
        save(row.resize((512, 64), Image.Resampling.LANCZOS),
             f"castle_01_base_stage_{stage}.png", (512, 64))

    wheels = clean_alpha(Image.open(WHEEL_SHEET))
    if wheels.size != (1024, 1536):
        raise ValueError(f"unexpected wheel sheet size: {wheels.size}")
    for stage in range(6):
        # The authored wheel occupies the centered square in each 1024x256 row.
        wheel = wheels.crop((384, stage * 256, 640, (stage + 1) * 256))
        # Adjacent wheels nearly touch in the source sheet. A feathered round
        # isolation mask retains the wheel and rejects the neighboring row.
        mask = Image.new("L", (256, 256))
        ImageDraw.Draw(mask).ellipse((16, 16, 240, 240), fill=255)
        mask = mask.filter(ImageFilter.GaussianBlur(1.5))
        wheel.putalpha(ImageChops.multiply(wheel.getchannel("A"), mask))
        save(contain(wheel, (128, 128)),
             f"castle_01_wheel_stage_{stage}.png", (128, 128))

    hover = clean_alpha(Image.open(HOVER_SHEET))
    if hover.size != (1774, 887):
        raise ValueError(f"unexpected hover sheet size: {hover.size}")
    castle_07_base = contain(clean_alpha(Image.open(CASTLE_07_BASE)), (512, 64))
    undercarriage = contain(hover.crop((0, 443, 1774, 887)), (512, 64))
    save(castle_07_base, "castle_07_base_stage_0.png", (512, 64))
    save(undercarriage, "castle_07_hover_stage_0.png", (512, 64))

    for legacy in ("castle_07_platform_stage_0.png", *(f"castle_01_platform_stage_{i}.png" for i in range(6))):
        for directory in (SOURCE, RUNTIME):
            path = directory / legacy
            if path.exists():
                path.unlink()
    for legacy_preview in ("castle_01_platform_wheel_preview.png", "castle_07_hover_preview.png"):
        path = SOURCE / legacy_preview
        if path.exists():
            path.unlink()

    preview = Image.new("RGBA", (768, 6 * 160), (20, 29, 35, 255))
    for stage in range(6):
        p = Image.open(RUNTIME / f"castle_01_base_stage_{stage}.png")
        w = Image.open(RUNTIME / f"castle_01_wheel_stage_{stage}.png")
        preview.alpha_composite(p, (0, stage * 160))
        preview.alpha_composite(w, (576, stage * 160 + 16))
    preview.save(SOURCE / "castle_01_base_wheel_preview.png", optimize=True)
    hover_preview = Image.new("RGBA", (512, 128), (20, 29, 35, 255))
    hover_preview.alpha_composite(castle_07_base, (0, 0))
    hover_preview.alpha_composite(undercarriage, (0, 64))
    hover_preview.save(SOURCE / "castle_07_base_hover_preview.png", optimize=True)
    print("built 14 mobility sprites: 7 castle bases, 1 hover part, and 6 wheels")


if __name__ == "__main__":
    build()
