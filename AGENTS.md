# Resource workflow

- User instruction (2026-11-18): do not create art or intermediate files inside `Resources/res`, and do not create new subfolders there.
- All future image work must start outside the build resource tree. Import only final assets that are actually used by the game; a loader reference or preload alone is not evidence of use. Keep unused finals, alternatives and source files in the external asset library.
- Generate drafts, source artwork, variants, references and intermediate exports in `asset_library/work/<task>/`. Existing reference art is in `asset_library/reference/Resources/res/`.
- Promote only a selected final asset using `python tools/assets/runtime_assets.py add <source> --name <flat-name.png>`. Production masters live in `asset_library/production/`; new runtime names must be flat (`res/<flat-name.png>`).
- `content/runtime-assets.json` is the explicit build allowlist. Do not add recursive directory globs to build packaging. Every runtime image must be directly under `res/`; there are no legacy subfolder exceptions. Keep image-name strings and dynamic filename formats flat too.
- Run `python tools/assets/runtime_assets.py stage` after editing a production/reference master. `Resources/res` contains generated runtime copies only. Never edit these copies directly.
- For PNG changes, run `python tools/assets/optimize_images.py --apply` before staging. It preserves original masters and verifies exact RGBA pixels, dimensions and alpha-channel semantics. Edit `original_source` for encoded assets; staging rejects stale encodings. Existing .png runtime IDs can contain lossless WebP payloads; inspect format magic instead of relying on the suffix.
- Keep runtime data (`Resources/data/content.pack`), fonts and audio approved in the same catalog. Source art, metadata, prompts, backups, logs and archives must not be bundled.
- Validate with `python tools/assets/runtime_assets.py check` and native runtime reviews. Android's asset-pack task stages only approved files automatically.
- Keep runtime images below the catalog's 200 MiB image budget. The removed two-castle duel must not be restored; current PVP is the single enemy-castle siege in `Classes/MergeSiege.inc`, sharing the basic castle renderer.
- Preserve the source aspect ratio of artwork. Only UI window/button frames and transient animation effects may scale the axes independently. Castle hull visible widths must remain equal.
