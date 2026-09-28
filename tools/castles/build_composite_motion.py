from collections import deque
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
RES = ROOT / "Resources" / "res"
REVIEW = ROOT / "Resources" / "concept" / "castle_20_composite_motion.png"

# kind, source part, count, horizontal attachment points, displayed part width
LAYOUT = [
    ("wheel", 0, 2, (.22, .78), .15),
    ("wheel", 1, 2, (.20, .80), .15),
    ("float",18, 3, (.25, .50, .75), .09),
    ("wheel", 3, 3, (.16, .50, .84), .14),
    ("walk",  4, 1, (.50,), .42),
    ("walk", 14, 4, (.18, .39, .61, .82), .13),
    ("walk", 12, 2, (.31, .69), .13),
    ("walk",  7, 2, (.40, .60), .17),
    ("walk",  8, 2, (.39, .61), .16),
    ("walk",  9, 2, (.40, .60), .15),
    ("walk", 10, 2, (.35, .65), .19),
    ("walk", 11, 2, (.40, .60), .15),
    ("walk", 12, 2, (.40, .60), .14),
    ("walk", 13, 2, (.40, .60), .16),
    ("walk", 14, 2, (.40, .60), .17),
    ("float",15, 2, (.36, .64), .18),
    ("walk", 16, 2, (.40, .60), .16),
    ("float",17, 3, (.25, .50, .75), .13),
    ("float",18, 3, (.25, .50, .75), .11),
    ("float",18, 3, (.25, .50, .75), .10),
]


def largest_component(im):
    a = im.getchannel("A")
    w, h = im.size
    pix = a.load()
    seen = bytearray(w * h)
    best = []
    for sy in range(h):
        for sx in range(w):
            p = sy * w + sx
            if seen[p] or pix[sx, sy] < 16:
                continue
            q = deque([(sx, sy)])
            seen[p] = 1
            points = []
            while q:
                x, y = q.popleft()
                points.append((x, y))
                for nx, ny in ((x-1, y), (x+1, y), (x, y-1), (x, y+1)):
                    if 0 <= nx < w and 0 <= ny < h:
                        np = ny * w + nx
                        if not seen[np] and pix[nx, ny] >= 16:
                            seen[np] = 1
                            q.append((nx, ny))
            if len(points) > len(best):
                best = points
    mask = Image.new("L", (w, h))
    out_alpha = mask.load()
    for x, y in best:
        out_alpha[x, y] = pix[x, y]
    out = im.copy()
    out.putalpha(mask)
    box = out.getchannel("A").getbbox()
    return out.crop(box) if box else Image.new("RGBA", (1, 1))


def source_pose(raw, kind, pose):
    if kind == "wheel":
        return raw.rotate(-pose * 45, Image.Resampling.NEAREST, expand=True)
    cell_w = raw.width // 4
    return largest_component(raw.crop((pose * cell_w, 0, (pose + 1) * cell_w, raw.height)))


def build_stage(stage):
    body = Image.open(RES / f"castle{stage}.png").convert("RGBA")
    kind, part_index, count, anchors, width_ratio = LAYOUT[stage]
    raw = Image.open(RES / f"castle_part{part_index}.png").convert("RGBA")
    sheet = Image.new("RGBA", (4096, 1024))

    # Keep every stage inside an identical runtime cell.  These values are also
    # written in CastleWheelManager.h, so the original body camera transform is
    # recovered exactly when the complete frame is drawn.
    body_scale = min(900.0 / body.width, 820.0 / body.height)
    if stage == 4:
        body_scale = .8
    bw = round(body.width * body_scale)
    bh = round(body.height * body_scale)
    bx = 0 if stage == 4 else (1024 - bw) // 2
    by = 72 if stage == 4 else 32
    scaled_body = body.resize((bw, bh), Image.Resampling.NEAREST)
    body_bottom = by + bh

    for pose in range(4):
        cell = Image.new("RGBA", (1024, 1024))
        part = source_pose(raw, kind, pose)

        # The snail source is a face/neck motion, not a centred foot.  This is
        # the measured placement approved in snail_frame1_composite.png,
        # reduced with the body onto the common 1024px runtime cell.
        if stage == 4:
            part = part.resize((327, 327), Image.Resampling.NEAREST)
            cell.alpha_composite(part, (592, 364))
            cell.alpha_composite(scaled_body, (bx, by))
            sheet.alpha_composite(cell, (pose * 1024, 0))
            continue

        target_w = max(1, round(bw * width_ratio))
        target_h = max(1, round(part.height * target_w / part.width))
        part = part.resize((target_w, target_h), Image.Resampling.NEAREST)
        # Walking sprites contain a long upper shank/root.  Most of it belongs
        # behind the body; exposing it below the lowest decorative pixel made
        # every foot look detached.  Floating engines need a smaller insertion.
        overlap = .35 if kind == "float" else .65
        py = min(round(body_bottom - target_h * overlap), 1012 - target_h)
        for n in range(count):
            # Alternating legs use the opposite pose without changing their
            # authored socket.  Wheels share one physical rotation angle.
            draw_part = part
            if kind == "walk" and n % 2:
                draw_part = source_pose(raw, kind, (pose + 2) % 4)
                dh = max(1, round(draw_part.height * target_w / draw_part.width))
                draw_part = draw_part.resize((target_w, dh), Image.Resampling.NEAREST)
                draw_y = min(round(body_bottom - dh * overlap), 1012 - dh)
            else:
                draw_y = py
            cx = bx + round(anchors[n] * bw)
            cell.alpha_composite(draw_part, (cx - target_w // 2, draw_y))
        cell.alpha_composite(scaled_body, (bx, by))
        sheet.alpha_composite(cell, (pose * 1024, 0))

    sheet.save(RES / f"castle_move{stage}.png", optimize=True)
    return body_scale, bx, by, sheet


def main():
    meta = []
    review = Image.new("RGBA", (1024, 1280), (35, 42, 55, 255))
    for stage in range(20):
        scale, bx, by, sheet = build_stage(stage)
        meta.append((scale, bx, by))
        thumb = sheet.crop((0, 0, 1024, 1024))
        thumb.thumbnail((240, 240), Image.Resampling.NEAREST)
        x = (stage % 4) * 256 + (256 - thumb.width) // 2
        y = (stage // 4) * 256 + (256 - thumb.height) // 2
        review.alpha_composite(thumb, (x, y))
    review.save(REVIEW, optimize=True)
    print("static const CompositeLayout kComposite[20] = {")
    for scale, bx, by in meta:
        print(f"\t{{{scale:.8f}f, {bx}, {by}}},")
    print("};")


if __name__ == "__main__":
    main()
