Add-Type -AssemblyName System.Drawing

$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$sourcePath = Join-Path $root 'tools/castles/source_shells/castle_06_full.png'
$outDir = Join-Path $root 'Resources/res/castle_exterior'
$upperH = 320
$floors = 6
$height = $upperH + 128 * $floors
$source = [Drawing.Bitmap]::FromFile($sourcePath)
try {
    if ($source.Width -ne 1024 -or $source.Height -ne 1536) { throw 'Unexpected source dimensions' }
    foreach ($stage in 0..5) {
        $shell = New-Object Drawing.Bitmap 640, $height, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [Drawing.Graphics]::FromImage($shell)
        try {
            $g.Clear([Drawing.Color]::Transparent)
            $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            # Keep the asymmetric crown intact and use a single uniform room grid.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 640, $upperH),
                0, 0, 1024, 550, [Drawing.GraphicsUnit]::Pixel)
            # The side masonry is narrow; all six 512x128 center slots stay clear.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, $upperH, 64, 768),
                135, 550, 110, 940, [Drawing.GraphicsUnit]::Pixel)
            $g.DrawImage($source, (New-Object Drawing.Rectangle 576, $upperH, 64, 768),
                815, 550, 125, 940, [Drawing.GraphicsUnit]::Pixel)
        } finally { $g.Dispose() }
        try {
            $shell.Save((Join-Path $outDir ('castle_06_hollow_stage_{0}.png' -f $stage)),
                [Drawing.Imaging.ImageFormat]::Png)
        } finally { $shell.Dispose() }
    }
    # The dragon juts outside the left wall instead of masking a room.
    $dragon = New-Object Drawing.Bitmap 160, 256, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g = [Drawing.Graphics]::FromImage($dragon)
    try {
        $g.Clear([Drawing.Color]::Transparent)
        $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 160, 256),
            0, 992, 200, 345, [Drawing.GraphicsUnit]::Pixel)
    } finally { $g.Dispose() }
    try { $dragon.Save((Join-Path $outDir 'castle_06_dragon.png'), [Drawing.Imaging.ImageFormat]::Png) }
    finally { $dragon.Dispose() }
} finally { $source.Dispose() }

# Use the same dragon-metal palette for the lower hull, wheel and commander
# deck. The old teal/wood pieces visually belonged to another castle.
$parts = [Drawing.Bitmap]::FromFile((Join-Path $root 'tools/castles/source_mobility/castle_06_parts.png'))
try {
    $partDefs = @(
        @{ Name = 'base'; Width = 512; Height = 64; X = 10; Y = 108; W = 1510; H = 230; Dir = 'castle_mobility' },
        @{ Name = 'wheel'; Width = 128; Height = 128; X = 34; Y = 385; W = 580; H = 580; Dir = 'castle_mobility' },
        @{ Name = 'balcony'; Width = 192; Height = 128; X = 660; Y = 390; W = 860; H = 575; Dir = 'castle_exterior' }
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
                $path = Join-Path $root ('Resources/res/{0}/castle_06_{1}_stage_{2}.png' -f $def.Dir, $def.Name, $stage)
                $out.Save($path, [Drawing.Imaging.ImageFormat]::Png)
            }
        } finally { $out.Dispose() }
    }
} finally { $parts.Dispose() }

foreach ($stage in 0..5) {
    $path = Join-Path $outDir ('castle_06_hollow_stage_{0}.png' -f $stage)
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

$preview = New-Object Drawing.Bitmap 936, 1270, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [Drawing.Graphics]::FromImage($preview)
try {
    $g.Clear([Drawing.Color]::FromArgb(25, 42, 47))
    $base = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_06_base_stage_0.png'))
    try { $g.DrawImageUnscaled($base, 164, $height) } finally { $base.Dispose() }
    for ($floor = 0; $floor -lt $floors; ++$floor) {
        $roomStage = if ($floor -eq ($floors - 1)) { 0 } else { 5 }
        $room = [Drawing.Bitmap]::FromFile((Join-Path $root ('Resources/res/castle_room_{0:d2}_{1}.png' -f ($floor + 1), $roomStage)))
        try { $g.DrawImageUnscaled($room, 164, $upperH + ($floors - 1 - $floor) * 128) }
        finally { $room.Dispose() }
    }
    $shell = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_06_hollow_stage_0.png'))
    try { $g.DrawImageUnscaled($shell, 100, 0) } finally { $shell.Dispose() }
    $wheel = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_06_wheel_stage_0.png'))
    try {
        $g.DrawImage($wheel, (New-Object Drawing.Rectangle 235, 1148, 114, 114))
        $g.DrawImage($wheel, (New-Object Drawing.Rectangle 491, 1148, 114, 114))
    } finally { $wheel.Dispose() }
    $balcony = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_06_balcony_stage_0.png'))
    try { $g.DrawImageUnscaled($balcony, 644, 960) } finally { $balcony.Dispose() }
    $dragon = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_06_dragon.png'))
    try { $g.DrawImageUnscaled($dragon, 0, 790) } finally { $dragon.Dispose() }
} finally { $g.Dispose() }
try { $preview.Save((Join-Path $PSScriptRoot 'preview_castle_06_hollow.png'), [Drawing.Imaging.ImageFormat]::Png) }
finally { $preview.Dispose() }
Write-Host 'Built castle 6 dragon shell: 640x1088, six clear 512x128 openings.'
