Add-Type -AssemblyName System.Drawing

$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$outDir = Join-Path $root 'Resources/res/castle_exterior'
$upperH = 320
$floors = 9
$height = $upperH + 128 * $floors
$source = [Drawing.Bitmap]::FromFile((Join-Path $root 'tools/castles/source_shells/castle_09_full.png'))
try {
    if ($source.Width -ne 1024 -or $source.Height -ne 1536) { throw 'Unexpected source dimensions' }
    foreach ($stage in 0..5) {
        $shell = New-Object Drawing.Bitmap 640, $height, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [Drawing.Graphics]::FromImage($shell)
        try {
            $g.Clear([Drawing.Color]::Transparent)
            $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 640, $upperH),
                0, 0, 1024, 480, [Drawing.GraphicsUnit]::Pixel)
            # Do not use the source's crossbars: separate room images provide
            # every floor. The 512-pixel center is transparent on all 9 rows.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, $upperH, 64, 1152),
                185, 480, 105, 1056, [Drawing.GraphicsUnit]::Pixel)
            $g.DrawImage($source, (New-Object Drawing.Rectangle 576, $upperH, 64, 1152),
                760, 480, 140, 1056, [Drawing.GraphicsUnit]::Pixel)
        } finally { $g.Dispose() }
        try {
            $shell.Save((Join-Path $outDir ('castle_09_hollow_stage_{0}.png' -f $stage)),
                [Drawing.Imaging.ImageFormat]::Png)
        } finally { $shell.Dispose() }
    }
    # Keep the repeated bat wings outside the left wall at their natural
    # width. Squeezing them into a 64px strip would erase the silhouette.
    $wing = New-Object Drawing.Bitmap 128, 1152, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g = [Drawing.Graphics]::FromImage($wing)
    try {
        $g.Clear([Drawing.Color]::Transparent)
        $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 128, 1152),
            0, 480, 230, 1056, [Drawing.GraphicsUnit]::Pixel)
    } finally { $g.Dispose() }
    try { $wing.Save((Join-Path $outDir 'castle_09_wings.png'), [Drawing.Imaging.ImageFormat]::Png) }
    finally { $wing.Dispose() }
} finally { $source.Dispose() }

$parts = [Drawing.Bitmap]::FromFile((Join-Path $root 'tools/castles/source_mobility/castle_09_parts.png'))
try {
    if ($parts.Width -ne 1536 -or $parts.Height -ne 1024) { throw 'Unexpected parts dimensions' }
    $partDefs = @(
        @{ Name = 'flightbase'; Width = 512; Height = 128; X = 0; Y = 100; W = 1536; H = 350; Dir = 'castle_mobility' },
        @{ Name = 'balcony'; Width = 192; Height = 128; X = 800; Y = 470; W = 730; H = 520; Dir = 'castle_exterior' }
    )
    foreach ($def in $partDefs) {
        $out = New-Object Drawing.Bitmap $def.Width, $def.Height, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [Drawing.Graphics]::FromImage($out)
        try {
            $g.Clear([Drawing.Color]::Transparent)
            $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            $g.DrawImage($parts, (New-Object Drawing.Rectangle 0, 0, $def.Width, $def.Height),
                $def.X, $def.Y, $def.W, $def.H, [Drawing.GraphicsUnit]::Pixel)
        } finally { $g.Dispose() }
        try {
            foreach ($stage in 0..5) {
                $path = Join-Path $root ('Resources/res/{0}/castle_09_{1}_stage_{2}.png' -f $def.Dir, $def.Name, $stage)
                $out.Save($path, [Drawing.Imaging.ImageFormat]::Png)
            }
        } finally { $out.Dispose() }
    }
} finally { $parts.Dispose() }

# Three plume centers align to the three engine mouths at 15%, 50%, 85%.
$exhaustSource = [Drawing.Bitmap]::FromFile((Join-Path $root 'tools/castles/source_mobility/castle_09_exhaust.png'))
try {
    if ($exhaustSource.Width -ne 2172 -or $exhaustSource.Height -ne 724) { throw 'Unexpected exhaust dimensions' }
    $exhaust = New-Object Drawing.Bitmap 512, 128, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g = [Drawing.Graphics]::FromImage($exhaust)
    try {
        $g.Clear([Drawing.Color]::Transparent)
        $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $g.DrawImage($exhaustSource, (New-Object Drawing.Rectangle 0, 0, 512, 128),
            0, 50, 2172, 630, [Drawing.GraphicsUnit]::Pixel)
    } finally { $g.Dispose() }
    try {
        $exhaust.Save((Join-Path $root 'Resources/res/castle_mobility/castle_09_exhaust.png'),
            [Drawing.Imaging.ImageFormat]::Png)
    } finally { $exhaust.Dispose() }
} finally { $exhaustSource.Dispose() }

foreach ($stage in 0..5) {
    $path = Join-Path $outDir ('castle_09_hollow_stage_{0}.png' -f $stage)
    $img = [Drawing.Bitmap]::FromFile($path)
    try {
        if ($img.Width -ne 640 -or $img.Height -ne $height) { throw "Bad size: $path" }
        for ($y = $upperH; $y -lt $height; ++$y) {
            for ($x = 64; $x -lt 576; ++$x) {
                if ($img.GetPixel($x, $y).A -ne 0) { throw "Room aperture covered: $path ($x,$y)" }
            }
        }
    } finally { $img.Dispose() }
}

$preview = New-Object Drawing.Bitmap 936, 1780, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [Drawing.Graphics]::FromImage($preview)
try {
    $g.Clear([Drawing.Color]::FromArgb(25, 42, 47))
    for ($floor = 0; $floor -lt $floors; ++$floor) {
        $roomStage = if ($floor -eq ($floors - 1)) { 0 } else { 5 }
        $room = [Drawing.Bitmap]::FromFile((Join-Path $root ('Resources/res/castle_room_{0:d2}_{1}.png' -f ($floor + 1), $roomStage)))
        try { $g.DrawImageUnscaled($room, 164, $upperH + ($floors - 1 - $floor) * 128) }
        finally { $room.Dispose() }
    }
    $shell = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_09_hollow_stage_0.png'))
    try { $g.DrawImageUnscaled($shell, 100, 0) } finally { $shell.Dispose() }
    $wings = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_09_wings.png'))
    try { $g.DrawImageUnscaled($wings, 0, $upperH) } finally { $wings.Dispose() }
    $exhaust = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_09_exhaust.png'))
    try { $g.DrawImageUnscaled($exhaust, 164, $height + 94) } finally { $exhaust.Dispose() }
    $base = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_09_flightbase_stage_0.png'))
    try { $g.DrawImageUnscaled($base, 164, $height) } finally { $base.Dispose() }
    $balcony = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_09_balcony_stage_0.png'))
    try { $g.DrawImageUnscaled($balcony, 644, $height - 128) } finally { $balcony.Dispose() }
} finally { $g.Dispose() }
try { $preview.Save((Join-Path $PSScriptRoot 'preview_castle_09_hollow.png'), [Drawing.Imaging.ImageFormat]::Png) }
finally { $preview.Dispose() }
Write-Host 'Built castle 9 crystal shell: 640x1472, nine clear 512x128 openings.'


