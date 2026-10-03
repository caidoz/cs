Add-Type -AssemblyName System.Drawing

$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$sourcePath = Join-Path $root 'tools/castles/source_shells/castle_05_full.png'
$outDir = Join-Path $root 'Resources/res/castle_exterior'
$upperH = 300
$floors = 5
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
            # Broad copper dome crown; do not stretch it independently of the walls.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 640, $upperH),
                0, 0, 1024, 500, [Drawing.GraphicsUnit]::Pixel)
            # Only the narrow outside columns survive below the crown. The five
            # exact 512x128 room slots stay open; crossing beams from the source
            # must never cover room art or its walkable foreground.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, $upperH, 64, 640),
                180, 505, 110, 860, [Drawing.GraphicsUnit]::Pixel)
            $g.DrawImage($source, (New-Object Drawing.Rectangle 576, $upperH, 64, 640),
                805, 505, 130, 860, [Drawing.GraphicsUnit]::Pixel)
        } finally { $g.Dispose() }
        try {
            $shell.Save((Join-Path $outDir ('castle_05_hollow_stage_{0}.png' -f $stage)),
                [Drawing.Imaging.ImageFormat]::Png)
        } finally { $shell.Dispose() }
    }
    # Projection pieces keep their own aspect ratio and draw in front of the
    # outside wall; neither may trespass into the central room aperture.
    $gear = New-Object Drawing.Bitmap 128, 160, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g = [Drawing.Graphics]::FromImage($gear)
    try {
        $g.Clear([Drawing.Color]::Transparent)
        $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 128, 160),
            2, 440, 180, 255, [Drawing.GraphicsUnit]::Pixel)
    } finally { $g.Dispose() }
    try { $gear.Save((Join-Path $outDir 'castle_05_gear.png'), [Drawing.Imaging.ImageFormat]::Png) }
    finally { $gear.Dispose() }
    $beast = New-Object Drawing.Bitmap 160, 240, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g = [Drawing.Graphics]::FromImage($beast)
    try {
        $g.Clear([Drawing.Color]::Transparent)
        $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 160, 240),
            0, 967, 260, 390, [Drawing.GraphicsUnit]::Pixel)
    } finally { $g.Dispose() }
    try { $beast.Save((Join-Path $outDir 'castle_05_beast.png'), [Drawing.Imaging.ImageFormat]::Png) }
    finally { $beast.Dispose() }
} finally { $source.Dispose() }

foreach ($stage in 0..5) {
    $path = Join-Path $outDir ('castle_05_hollow_stage_{0}.png' -f $stage)
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

$preview = New-Object Drawing.Bitmap 936, 1120, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [Drawing.Graphics]::FromImage($preview)
try {
    $g.Clear([Drawing.Color]::FromArgb(25, 42, 47))
    $base = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_05_base_stage_0.png'))
    try { $g.DrawImageUnscaled($base, 164, $height) } finally { $base.Dispose() }
    for ($floor = 0; $floor -lt $floors; ++$floor) {
        $roomStage = if ($floor -eq ($floors - 1)) { 0 } else { 5 }
        $room = [Drawing.Bitmap]::FromFile((Join-Path $root ('Resources/res/castle_room_{0:d2}_{1}.png' -f ($floor + 1), $roomStage)))
        try { $g.DrawImageUnscaled($room, 164, $upperH + ($floors - 1 - $floor) * 128) }
        finally { $room.Dispose() }
    }
    $shell = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_05_hollow_stage_0.png'))
    try { $g.DrawImageUnscaled($shell, 100, 0) } finally { $shell.Dispose() }
    $gear = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_05_gear.png'))
    try { $g.DrawImageUnscaled($gear, 10, 312) } finally { $gear.Dispose() }
    $beast = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_05_beast.png'))
    try { $g.DrawImageUnscaled($beast, 0, 700) } finally { $beast.Dispose() }
    $wheel = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_05_wheel_stage_0.png'))
    try {
        $g.DrawImage($wheel, (New-Object Drawing.Rectangle 235, 1000, 114, 114))
        $g.DrawImage($wheel, (New-Object Drawing.Rectangle 491, 1000, 114, 114))
    } finally { $wheel.Dispose() }
    $balcony = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_05_balcony_stage_0.png'))
    try { $g.DrawImageUnscaled($balcony, 644, 812) } finally { $balcony.Dispose() }
} finally { $g.Dispose() }
try { $preview.Save((Join-Path $PSScriptRoot 'preview_castle_05_hollow.png'), [Drawing.Imaging.ImageFormat]::Png) }
finally { $preview.Dispose() }
Write-Host 'Built castle 5 copper shell: 640x940, five clear 512x128 openings.'
