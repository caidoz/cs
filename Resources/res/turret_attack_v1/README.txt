Dedicated artillery resources (version 1)

missile.png: independent copy of the native Diana c1 sprite sheet. Only the
guided-shot parts are rendered by the artillery. This has its own image ID,
texture, and sprite pool; hero texture changes cannot mutate the turret asset.

laser.png: independent copy of the native c27 sprite sheet. The artillery uses
the same broad (0,146,128,36) and narrow (0,206,128,16) beam strips as SpiderDraw,
with its own charging, beam duration, muzzle anchor, and resource identity.

The originals are retained unchanged. Artillery does not spawn or borrow live
hero/monster objects. Its sequence owns launch, guided flight, impact, and recovery.
