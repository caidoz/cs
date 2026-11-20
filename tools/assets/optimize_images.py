"""Create verified lossless runtime encodings without changing artwork masters.

Existing .png runtime names are compatibility IDs used by code, atlas metadata,
and the content updater. Keep these IDs; Cocos Image detects PNG/WebP from file
magic, not the extension (cocos/platform/CCImage.cpp). Approved WebP masters have
the correct .webp extension outside Resources. No renderer alias or CDN path
change is needed. PNG stays selected whenever WebP is not smaller.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
import hashlib
import io
import json
from pathlib import Path
import shutil
import time
import threading

from PIL import Image, features

ROOT = Path(__file__).resolve().parents[2]
LEGACY_VERSION = 'webp-lossless-exact-v1-method4'
VERSION = 'webp-lossless-exact-v2-alpha-compatible-method4'
_encoding_locks = {}
_locks_guard = threading.Lock()


def preserve_alpha_hint(data, source_has_alpha):
    """Retain an opaque PNG alpha channel's renderer semantics.

    Cocos uses WebP's alpha feature hint to select premultiplied blending. An
    opaque RGBA PNG must remain RGBA even when WebP optimizes opaque alpha away;
    legacy custom panel blends depend on this. VP8L's alpha_is_used is explicitly
    a decoding-neutral hint (https://developers.google.com/speed/webp/docs/webp_lossless_bitstream_specification).
    Keep it set for originally alpha-bearing sources; pixel data is untouched.
    """
    if not source_has_alpha: return data
    result = bytearray(data)
    pos, found = 12, False
    while pos + 8 <= len(result):
        kind = result[pos:pos+4]
        size = int.from_bytes(result[pos+4:pos+8], 'little')
        if kind == b'VP8X': result[pos+8] |= 0x10
        if kind == b'VP8L':
            if size < 5 or result[pos+8] != 0x2f: raise ValueError('Invalid VP8L header')
            result[pos+12] |= 0x10
            found = True
        pos += 8 + size + (size & 1)
    if not found: raise ValueError('Lossless VP8L image required')
    return bytes(result)


def encode(asset):
    source = ROOT / asset.get('original_source', asset['source'])
    if source.suffix.lower() != '.png': return asset, None
    key = hashlib.sha256(source.read_bytes()).hexdigest()
    with _locks_guard:
        lock = _encoding_locks.setdefault(key, threading.Lock())
    with lock:
        return encode_unique(asset)


def encode_unique(asset):
    original = asset.get('original_source', asset['source'])
    source = ROOT / original
    if source.suffix.lower() != '.png':
        return asset, None
    raw = source.read_bytes()
    key = hashlib.sha256(VERSION.encode() + raw).hexdigest()
    cache = ROOT / 'asset_library/work/runtime-encoding/cache'
    cache.mkdir(parents=True, exist_ok=True)
    encoded = cache / (key + '.webp')
    proof = cache / (key + '.json')
    # A reused cache entry must still match the verified encoded content hash.
    record = json.loads(proof.read_text()) if proof.exists() else {}
    if not encoded.exists() or hashlib.sha256(encoded.read_bytes()).hexdigest() != record.get('encoded_sha256'):
        with Image.open(io.BytesIO(raw)) as loaded:
            if getattr(loaded, 'n_frames', 1) != 1:
                raise ValueError(f'Animated source requires separate approval: {original}')
            has_alpha = 'A' in loaded.getbands() or 'transparency' in loaded.info
            image = loaded.convert('RGBA')
        legacy_key = hashlib.sha256(LEGACY_VERSION.encode() + raw).hexdigest()
        legacy_file, legacy_proof = cache/(legacy_key+'.webp'), cache/(legacy_key+'.json')
        old = json.loads(legacy_proof.read_text()) if legacy_proof.exists() else {}
        if legacy_file.exists() and old.get('rgba_exact') and old.get('source_sha256') == hashlib.sha256(raw).hexdigest() and hashlib.sha256(legacy_file.read_bytes()).hexdigest() == old.get('encoded_sha256'):
            data = legacy_file.read_bytes()
        else:
            output = io.BytesIO()
            image.save(output, format='WEBP', lossless=True, quality=100, method=4, exact=True)
            data = output.getvalue()
        data = preserve_alpha_hint(data, has_alpha)
        with Image.open(io.BytesIO(data)) as decoded:
            if decoded.size != image.size or decoded.convert('RGBA').tobytes() != image.tobytes():
                raise ValueError(f'Lossless pixel verification failed: {original}')
            if ('A' in decoded.getbands()) != has_alpha:
                raise ValueError(f'Original alpha-channel semantics were not preserved: {original}')
        record = {'source_sha256': hashlib.sha256(raw).hexdigest(),
                  'encoded_sha256': hashlib.sha256(data).hexdigest(),
                  'rgba_sha256': hashlib.sha256(image.tobytes()).hexdigest(),
                  'size': list(image.size), 'source_bytes': len(raw), 'encoded_bytes': len(data),
                  'encoding': VERSION, 'rgba_exact': True, 'alpha_semantics_preserved': True}
        # Unique temporary paths also make identical input assets safe when
        # their encodes finish in parallel. Only complete files enter the cache.
        import uuid
        token = uuid.uuid4().hex
        temp = cache / (key + '.' + token + '.tmp')
        temp.write_bytes(data)
        temp.replace(encoded)
        temp = cache / (key + '.' + token + '.json.tmp')
        temp.write_text(json.dumps(record, indent=2))
        temp.replace(proof)
    result = dict(asset)
    if record['encoded_bytes'] < len(raw):
        master = ROOT / 'asset_library/production' / ('runtime-' + key + '.webp')
        master.parent.mkdir(parents=True, exist_ok=True)
        if not master.exists() or hashlib.sha256(master.read_bytes()).hexdigest() != record['encoded_sha256']:
            shutil.copy2(encoded, master)
        result.update(source=master.relative_to(ROOT).as_posix(), original_source=original,
                      encoding='webp-lossless', rgba_sha256=record['rgba_sha256'],
                      original_sha256=record['source_sha256'], encoded_sha256=record['encoded_sha256'])
    else:
        result['source'] = original
        for field in ('original_source', 'encoding', 'rgba_sha256', 'original_sha256', 'encoded_sha256'):
            result.pop(field, None)
    return result, dict(record, target=asset['target'], selected_webp=record['encoded_bytes'] < len(raw))


def optimize(apply=False, workers=4):
    if not features.check('webp'):
        raise RuntimeError('Pillow with WebP support is required for offline asset authoring')
    catalog_path = ROOT / 'content/runtime-assets.json'
    catalog = json.loads(catalog_path.read_text(encoding='utf-8'))
    originals = catalog['assets']
    selected, proofs = {}, []
    started = time.monotonic()
    with ThreadPoolExecutor(max_workers=workers) as executor:
        tasks = [executor.submit(encode, asset) for asset in originals]
        for n, task in enumerate(as_completed(tasks), 1):
            asset, proof = task.result()
            selected[asset['target']] = asset
            if proof: proofs.append(proof)
            if n % 100 == 0 or n == len(tasks):
                print(f'VERIFIED {n}/{len(tasks)} assets ({time.monotonic()-started:.0f}s)', flush=True)
    before = sum((ROOT / asset.get('original_source', asset['source'])).stat().st_size for asset in originals)
    after = sum((ROOT / asset['source']).stat().st_size for asset in selected.values())
    report = {'original_bytes': before, 'optimized_bytes': after,
              'saved_bytes': before-after, 'converted_files': sum(p['selected_webp'] for p in proofs),
              'all_rgba_exact': all(p['rgba_exact'] for p in proofs), 'images': sorted(proofs, key=lambda p:p['target'])}
    (ROOT / 'reports/runtime-assets/lossless-encoding.json').write_text(json.dumps(report, indent=2))
    if apply:
        catalog['assets'] = [selected[a['target']] for a in originals]
        catalog_path.write_text(json.dumps(catalog, indent=2) + '\n', encoding='utf-8')
    print(f"{'APPLIED' if apply else 'PREVIEW'} {before/2**20:.1f} -> {after/2**20:.1f} MiB; "
          f"{report['converted_files']} exact-pixel encodings", flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--apply', action='store_true')
    parser.add_argument('--workers', type=int, default=4)
    args = parser.parse_args()
    if not 1 <= args.workers <= 8: parser.error('workers must be 1..8')
    optimize(args.apply, args.workers)
