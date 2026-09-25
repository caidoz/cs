from pathlib import Path
from collections import deque
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
GEN = Path(r"C:\Users\polyp\.codex\generated_images\01a0ad19-e9c6-79c3-9634-d83b8c4e5d36")
OUT = ROOT / "Resources" / "res"

SHEETS = [
    "exec-852d3c80-9053-4f97-bcef-d4d3fcf95dac.png",
    "exec-00a03864-f545-4928-904b-f1e905ee745f.png",
    "exec-17928c0e-6c25-48a3-906b-d5dde462ea32.png",
    "exec-d77001ef-8773-4b8b-b8ec-865f0f43572e.png",
    "exec-a190c0e1-4ea6-47fe-80a0-270b519fc4bd.png",
    "exec-4ded0695-fed7-46ca-9c1c-ee4ee7c4c2ba.png",
    "exec-1e9fe7f8-5e87-4955-8deb-6ef828727b2f.png",
    "exec-eaed14ac-2a1c-44fe-bbb1-0ca23a4e8c8a.png",
    "exec-b47e0bf0-80d0-4a73-9596-1e36163b090e.png",
    "exec-d7e139fc-4a8d-48d1-b0d8-6d881791d8a8.png",
    "exec-07e72a3d-b91c-4000-b594-6a24337d228a.png",
    "exec-48fa857b-1c05-4c02-a97e-2c5521b91e3f.png",
    "exec-32ad4b0d-ad16-4f25-9b6a-6897ea266f9a.png",
    "exec-ad3b27ec-6ec2-43f9-b49f-2066763ebd45.png",
    "exec-b6b637ba-b124-4c0d-b8b7-c96c81cf8042.png",
    "exec-891c5956-f8e9-4787-90e9-05bfcb9db3ae.png",
    "exec-6a5cd4b8-1425-49a0-baf7-87115ad40f70.png",
    "exec-4dd3b445-c482-4b3c-be7c-6034b78b026a.png",
    "exec-8f71c72e-a98f-4232-857a-24769d8da336.png",
    "exec-1cc4c679-f765-49e6-a8e0-c734a76c4652.png",
]

# Character-free body art.  The source sheets below are still used only for
# locomotion-part extraction; these final bodies deliberately keep every deck
# and balcony empty so lobby occupants can be drawn by the game itself.
CLEAN_BODIES = [
	"exec-31d9a404-46d8-475a-b2e6-cbc98cba706e.png",
	"exec-490f9d79-e448-4e7c-baf2-6a19d736282f.png",
	"exec-cc22f8d1-ce02-4a43-8df3-6e2dc9adde32.png",
	"exec-07adfcff-e79f-4f31-bdfe-7d718555bce5.png",
	"exec-5b3278ef-8fc4-4511-ae06-b817bee34014.png",
	"exec-053ea456-8c16-4ded-b6cf-6170f989add6.png",
	"exec-28d99832-b803-476a-9937-1d1d05495e04.png",
	"exec-f9adf4e0-6c32-4e34-9162-7212fc56b6cf.png",
	"exec-857cb12d-a420-4917-b5b6-8e010c28d49b.png",
	"exec-79d7e6e6-26e2-4851-b385-3b2185859fa8.png",
	"exec-c4ae4da7-c9b0-446e-b0c1-dce540efe420.png",
	"exec-50cc702a-bb09-4fff-bf8e-7ee6125777cd.png",
	"exec-b4a9bc60-d0fa-4b31-b5e1-e9a74f97c10c.png",
	"exec-00c026b3-9e8d-4b1b-b8ab-028babcd3bbd.png",
	"exec-6cfe96dc-0260-4c15-86c7-a5ff3f5729bf.png",
	"exec-64cf4c40-e071-4458-94db-e48139aa114f.png",
	"exec-0f656e38-e3f4-42c0-9bea-7468a3b0231d.png",
	"exec-1d265d3f-7ffa-4bdc-b109-112174ea8dd0.png",
	"exec-53200d7e-a433-4216-91b3-c6844c1d61fe.png",
	"exec-3fd9fcd0-3fe0-4c2b-a62d-439bfd612779.png",
]

# The generator keeps the requested left-body/right-parts layout but the body
# width varies by silhouette.  These boundaries were measured from the final
# alpha sheets so no locomotion frame leaks into the castle texture.
SPLIT_RATIO = [
    .62, .62, .62, .62, .32, .52, .61, .40, .43, .50,
    .46, .46, .48, .48, .44, .60, .50, .46, .48, .46,
]

# Every directional mobile castle travels toward screen-right.  These two
# authored bodies arrived facing left and must be mirrored consistently on
# every rebuild.
FLIP_BODY = {6, 13}


def hard_alpha(im):
    im = im.convert("RGBA")
    a = im.getchannel("A").point(lambda v: 0 if v < 24 else v)
    im.putalpha(a)
    return im


def trim(im, pad=4):
    box = im.getchannel("A").getbbox()
    if not box:
        return Image.new("RGBA", (1, 1))
    x0, y0, x1, y1 = box
    return im.crop((max(0, x0-pad), max(0, y0-pad), min(im.width, x1+pad), min(im.height, y1+pad)))


def find_split(im):
    a = im.getchannel("A")
    lo, hi = int(im.width * .38), int(im.width * .76)
    sparse = []
    for x in range(lo, hi):
        occupied = sum(1 for y in range(0, im.height, 4) if a.getpixel((x, y)) >= 64)
        sparse.append(occupied <= 2)
    runs, start = [], None
    for i, empty in enumerate(sparse + [False]):
        if empty and start is None:
            start = i
        elif not empty and start is not None:
            runs.append((i-start, lo+start, lo+i))
            start = None
    if runs:
        _, x0, x1 = max(runs)
        return (x0+x1)//2
    return int(im.width * .62)


def four_frames(area):
    # Locate the four authored poses by connected alpha islands.  This avoids
    # carrying a tower/flag fragment into frame zero when a wide body overlaps
    # the nominal left/right layout boundary.
    step = 4
    small = area.getchannel("A").resize(
        (max(1, area.width//step), max(1, area.height//step)), Image.Resampling.NEAREST)
    w, h = small.size
    pix = small.load()
    seen = bytearray(w*h)
    comps = []
    for sy in range(h):
        for sx in range(w):
            pos = sy*w+sx
            if seen[pos] or pix[sx, sy] < 64:
                continue
            q = [(sx, sy)]; seen[pos] = 1; qi = 0
            x0=x1=sx; y0=y1=sy; count=0
            while qi < len(q):
                x, y = q[qi]; qi += 1; count += 1
                x0=min(x0,x); x1=max(x1,x); y0=min(y0,y); y1=max(y1,y)
                for nx, ny in ((x-1,y),(x+1,y),(x,y-1),(x,y+1)):
                    if 0<=nx<w and 0<=ny<h:
                        np=ny*w+nx
                        if not seen[np] and pix[nx,ny]>=64:
                            seen[np]=1; q.append((nx,ny))
            if count >= 30 and x0 > 1:
                comps.append((count, x0, y0, x1+1, y1+1))
    chosen = sorted(sorted(comps, reverse=True)[:4], key=lambda c:c[1])
    frames = []
    for _count, x0, y0, x1, y1 in chosen:
        frames.append(trim(area.crop((max(0,x0*step-4), max(0,y0*step-4),
                                      min(area.width,x1*step+4), min(area.height,y1*step+4))), 2))
    if len(frames) != 4:
        frames = []
        for n in range(4):
            x0 = area.width*n//4
            x1 = area.width*(n+1)//4
            frames.append(trim(area.crop((x0, 0, x1, area.height)), 2))
    # Runtime slices this texture with width/4.  Use fixed cells and a real
    # transparent gutter so filtering can never sample the neighbouring pose.
    cell_w = 256
    cell_h = 256
    sheet = Image.new("RGBA", (cell_w*4, cell_h))
    for n, f in enumerate(frames):
        # A generated pose can carry a disconnected flag/tower fragment from the
        # body half of the source sheet.  Keep only the pose's connected island
        # before packing it into the runtime cell.
        f = largest_island(f)
        f.thumbnail((cell_w-16, cell_h-16), Image.Resampling.NEAREST)
        sheet.alpha_composite(f, (n*cell_w+(cell_w-f.width)//2, cell_h-8-f.height))
    return sheet


def largest_island(area):
    step = 4
    small = area.getchannel("A").resize(
        (max(1, area.width//step), max(1, area.height//step)), Image.Resampling.NEAREST)
    w, h = small.size; pix = small.load(); seen = bytearray(w*h); best = None
    for sy in range(h):
        for sx in range(w):
            p = sy*w+sx
            if seen[p] or pix[sx,sy] < 64: continue
            q=[(sx,sy)]; seen[p]=1; qi=0; x0=x1=sx; y0=y1=sy; count=0
            while qi < len(q):
                x,y=q[qi]; qi+=1; count+=1
                x0=min(x0,x); x1=max(x1,x); y0=min(y0,y); y1=max(y1,y)
                for nx,ny in ((x-1,y),(x+1,y),(x,y-1),(x,y+1)):
                    if 0<=nx<w and 0<=ny<h:
                        np=ny*w+nx
                        if not seen[np] and pix[nx,ny]>=64:
                            seen[np]=1; q.append((nx,ny))
            candidate=(count,x0,y0,x1+1,y1+1)
            if best is None or candidate[0] > best[0]: best=candidate
    if best is None: return trim(area)
    _,x0,y0,x1,y1=best
    return trim(area.crop((max(0,x0*step-4),max(0,y0*step-4),
                           min(area.width,x1*step+4),min(area.height,y1*step+4))),2)


def build():
    OUT.mkdir(parents=True, exist_ok=True)
    for idx, name in enumerate(SHEETS):
        src = hard_alpha(Image.open(GEN/name))
        split = int(src.width * SPLIT_RATIO[idx])
        body = trim(hard_alpha(Image.open(GEN/CLEAN_BODIES[idx])))
        if idx in FLIP_BODY:
            body = body.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
        parts = trim(src.crop((split, 0, src.width, src.height)))

        # Keep source detail but cap GPU texture size.  Apparent progression is
        # controlled by the render scale, not destructive resampling.
        body.thumbnail((1024, 1024), Image.Resampling.NEAREST)
        body.save(OUT/f"castle{idx}.png", optimize=True)

        if idx in (0, 1, 2, 3, 5, 6):
            wheel = largest_island(parts)
            wheel.thumbnail((256, 256), Image.Resampling.NEAREST)
            wheel.save(OUT/f"castle_move{idx}.png", optimize=True)
        else:
            motion = four_frames(parts)
            motion.save(OUT/f"castle_move{idx}.png", optimize=True)
        print(idx, body.size, (OUT/f"castle_move{idx}.png").name)


if __name__ == "__main__":
    build()
