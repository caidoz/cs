# Stage five heavy cannon

The navy/brass gun now seats its rear flange at native hull coordinate (336,272), previously (368,266). Its muzzle and mirrored placement follow the same mount transform.

Castle index 4 uses Shell instead of Missiles: one straight, rotating 46 reference pixel heavy shot, with the existing single damage event at arrival. Other castles retain their shot types.

Asset: `Resources/res/turret_attack/heavy-shell.png`, 256x256 RGBA, registered as `TURRET_HEAVY_SHELL_IMG`. Generated with the built-in imagegen tool and resized for runtime use.

Prompt:

Create a single transparent-background game projectile sprite, no background shadow. A chunky spherical heavy cannon shot made of deep navy blue blackened iron, with one broad worn antique brass equatorial reinforcing band and six small brass rivets, bright steel highlight upper left, deep shaded lower right, a small embossed gold lion medallion facing viewer. Fantasy medieval steampunk hand-painted pixel-edged detailed game asset matching navy-and-brass castle cannon. Perfectly round silhouette, no fins, no rocket motor, no smoke, no flame, no lettering, no surrounding decoration. Centered isolated, fills 85 percent of square canvas. Highly legible when rendered 40 pixels wide. Transparent background.

Validation: turret presentation unit checks, Debug Win32 build `cs_heavy_cannon.exe`, live turret review at 640x850 and 640x1408.
