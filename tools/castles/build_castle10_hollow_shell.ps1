Add-Type -AssemblyName System.Drawing

$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$outDir = Join-Path $root 'Resources/res/castle_exterior'
$upperH = 330
$floors = 10
$height = $upperH + 128 * $floors
$source = [Drawing.Bitmap]::FromFile((Join-Path $root 'tools/castles/source_shells/castle_10_full.png'))
try {
    if ($source.Width -ne 1024 -or $source.Height -ne 1536) { throw 'Unexpected source dimensions' }
    foreach ($stage in 0..5) {
        $shell = New-Object Drawing.Bitmap 640, $height, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [Drawing.Graphics]::FromImage($shell)
        try {
            $g.Clear([Drawing.Color]::Transparent)
            $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            # Keep the entire sun-dome crown at full authored width.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 640, $upperH),
                0, 0, 1024, 530, [Drawing.GraphicsUnit]::Pixel)
            # Only side arcades and banners survive in the ten room rows.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, $upperH, 64, 1280),
                95, 530, 125, 920, [Drawing.GraphicsUnit]::Pixel)
            $g.DrawImage($source, (New-Object Drawing.Rectangle 576, $upperH, 64, 1280),
                805, 530, 125, 920, [Drawing.GraphicsUnit]::Pixel)
        } finally { $g.Dispose() }
        try {
            $shell.Save((Join-Path $outDir ('castle_10_hollow_stage_{0}.png' -f $stage)),
                [Drawing.Imaging.ImageFormat]::Png)
        } finally { $shell.Dispose() }
    }
} finally { $source.Dispose() }

foreach ($stage in 0..5) {
    $path = Join-Path $outDir ('castle_10_hollow_stage_{0}.png' -f $stage)
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

$preview = New-Object Drawing.Bitmap 936, 1900, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [Drawing.Graphics]::FromImage($preview)
try {
    $g.Clear([Drawing.Color]::FromArgb(25, 42, 47))
    for ($floor = 0; $floor -lt $floors; ++$floor) {
        $roomStage = if ($floor -eq ($floors - 1)) { 0 } else { 5 }
        $room = [Drawing.Bitmap]::FromFile((Join-Path $root ('Resources/res/castle_room_{0:d2}_{1}.png' -f ($floor + 1), $roomStage)))
        try { $g.DrawImageUnscaled($room, 164, $upperH + ($floors - 1 - $floor) * 128) }
        finally { $room.Dispose() }
    }
    $shell = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_10_hollow_stage_0.png'))
    try { $g.DrawImageUnscaled($shell, 100, 0) } finally { $shell.Dispose() }
    $exhaust = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_hover_exhaust_10.png'))
    try { $g.DrawImageUnscaled($exhaust, 164, $height + 108) } finally { $exhaust.Dispose() }
    $base = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_10_flightbase_stage_0.png'))
    try { $g.DrawImageUnscaled($base, 164, $height) } finally { $base.Dispose() }
    $balcony = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_10_balcony_stage_0.png'))
    try { $g.DrawImageUnscaled($balcony, 644, $height - 128) } finally { $balcony.Dispose() }
} finally { $g.Dispose() }
try { $preview.Save((Join-Path $PSScriptRoot 'preview_castle_10_hollow.png'), [Drawing.Imaging.ImageFormat]::Png) }
finally { $preview.Dispose() }
Write-Host 'Built castle 10 royal shell: 640x1610, ten clear 512x128 openings.'
