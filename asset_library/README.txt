Resource authoring and packaging (2026-11-18)

Folders
  work/<task>/                       New artwork, prompts, drafts and intermediate files.
  reference/Resources/res/            Existing original assets and archived alternatives.
  production/                        Approved new final masters, flat filenames.
  ../Resources/res/                  Generated runtime copies. Do not edit or generate here.

Approve a new final image
  python tools/assets/runtime_assets.py add asset_library/work/task/final.png --name final-icon.png
  Use res/final-icon.png in the game, then run:
  python tools/assets/runtime_assets.py stage

Update an existing image
  Edit the source named in content/runtime-assets.json, then run stage.
  Existing nested runtime paths remain for compatibility; new names must be flat.

Build
  Android assets_base automatically stages only the explicit catalog before packaging.
  Visual Studio prebuild stages the development resources; postbuild synchronizes only approved files.
  CMake stages the same catalog in its build directory.
  No wildcard directory packaging of this library is allowed.

Checks
  python tools/assets/runtime_assets.py check
  python tools/assets/test_runtime_assets.py
  python tools/assets/test_lossless_images.py
  python tools/assets/check_aab.py proj.android/app/build/outputs/bundle/release/cs-release.aab

Lossless runtime compression
----------------------------
  python tools/assets/optimize_images.py --apply
  python tools/assets/runtime_assets.py stage

Run the optimizer after adding a PNG or changing its original_source master.
Every selected encoding is decoded and checked for identical RGBA bytes and
dimensions. Originally alpha-bearing PNGs retain an alpha feature hint even when
all pixels are opaque; this preserves the game's legacy premultiplied panel blends.
Originals stay intact. Verified encodings are flat .webp masters in
production/; reusable encoder intermediates are in work/runtime-encoding/cache/.
Original runtime .png names are compatibility IDs. Generated runtime copies may
contain WebP data: Cocos Image reads format magic and supports WebP on Android,
Windows and iOS. This preserves atlas references and content-update paths without
renderer aliases. Do not use filename suffixes to inspect the encoded file format.
Staging checks original and encoded master hashes and rejects stale encodings.
Future flat runtime names may use .webp directly when no compatibility ID exists.

The initial catalog conservatively retains files named by C++ catalogs and dynamic
loading families. Files with remaining game-code references are not guessed unused.
Excluded originals and metadata are preserved here, not deleted.
For a CDN release, refresh the existing updater fingerprints with tools/content/make_manifest.py
after staging. Its input Resources now contains only approved runtime files.
Superseded runtime art
---------------------
content/archived-runtime-assets.json records assets retired from production and
the renderer evidence for each removal. Their masters remain under this library.
Historical CS_LEGACY_CASTLE_ART / CS_PREVIOUS_CASTLE_ART comparisons require the
archived art; normal builds intentionally exclude it. Do not restore obsolete
versions to the production allowlist to make an old art comparison run.
CS_ASSET_AUDIT=<absolute path outside Resources> optionally records each image
request and whether it loaded. Native release-resource reviews use this to check
for missing art after pruning. Production art resolution and colors are unchanged.

