# Flame laser and muzzle charge

Laser castles (indices 6 through 9) gather eight moving particles into a growing luminous sphere at the actual muzzle, then fire a flame-textured beam. The beam has a 48 reference pixel body (previously 23), a wider translucent aura and a white hot core. Its width flickers and its opacity fades during recovery. Both ends carry matching hot glows. Damage timing is unchanged.

Castle colors: red/orange, silver/cyan, violet, and gold. The crystal shot at index 5 remains its own projectile.

Asset: `Resources/res/turret_attack/flame-laser.png`, generated using built-in imagegen, resized for runtime, registered as `TURRET_FLAME_LASER_IMG`.

Prompt:

A single horizontal magical flame laser beam VFX sprite for a polished fantasy 2D game. Truly transparent background. Long straight continuous brilliant WHITE core surrounded by pearl white and pale grey flame tongues, wispy licking flames along upper and lower edges, powerful volumetric hot energy with soft alpha halo. Monochrome neutral WHITE only, no colors: designed for runtime color tinting. Beam fills canvas horizontally all the way from left edge to right edge, no origin orb or impact burst, no taper at either end, roughly uniform central thickness, narrower turbulent flame tips above and below. Wide landscape composition, clean isolated asset, no text, no weapons, no scene, no ground shadow.

Validation: turret presentation tests; Debug Win32 normal cs.exe; live turret capture checks at 640x850 and 640x1408.
