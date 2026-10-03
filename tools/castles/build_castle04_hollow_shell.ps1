Add-Type -AssemblyName System.Drawing

$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$sourcePath = Join-Path $root 'tools/castles/source_shells/castle_04_full.png'
$outDir = Join-Path $root 'Resources/res/castle_exterior'
if (!(Test-Path -LiteralPath $sourcePath)) { throw "Missing source: $sourcePath" }

$source = [Drawing.Bitmap]::FromFile($sourcePath)
try {
    for ($stage = 0; $stage -lt 6; ++$stage) {
        $shell = New-Object Drawing.Bitmap 640, 852, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [Drawing.Graphics]::FromImage($shell)
        try {
            $g.Clear([Drawing.Color]::Transparent)
            $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            # Preserve the broad blue-spired crown without stretching it sideways.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 640, 340),
                0, 0, 1024, 544, [Drawing.GraphicsUnit]::Pixel)
            # The middle 512 authored pixels remain transparent for four
            # separately upgraded rooms. The eagle is excluded from the strip
            # and drawn at full size in its own foreground pass.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 340, 64, 320),
                125, 545, 40, 584, [Drawing.GraphicsUnit]::Pixel)
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 660, 64, 192),
                125, 760, 40, 369, [Drawing.GraphicsUnit]::Pixel)
            $g.DrawImage($source, (New-Object Drawing.Rectangle 576, 340, 64, 512),
                865, 545, 40, 922, [Drawing.GraphicsUnit]::Pixel)
        } finally { $g.Dispose() }
        try {
            $shell.Save((Join-Path $outDir ('castle_04_hollow_stage_{0}.png' -f $stage)),
                [Drawing.Imaging.ImageFormat]::Png)
        } finally { $shell.Dispose() }
    }
    $eagle = New-Object Drawing.Bitmap 128, 160, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g = [Drawing.Graphics]::FromImage($eagle)
    try {
        $g.Clear([Drawing.Color]::Transparent)
        $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 128, 160),
            28, 1120, 255, 320, [Drawing.GraphicsUnit]::Pixel)
    } finally { $g.Dispose() }
    try { $eagle.Save((Join-Path $outDir 'castle_04_eagle.png'), [Drawing.Imaging.ImageFormat]::Png) }
    finally { $eagle.Dispose() }
} finally { $source.Dispose() }

foreach ($stage in 0..5) {
    $path = Join-Path $outDir ('castle_04_hollow_stage_{0}.png' -f $stage)
    $img = [Drawing.Bitmap]::FromFile($path)
    try {
        if ($img.Width -ne 640 -or $img.Height -ne 852) { throw "Bad size: $path" }
        for ($y = 340; $y -lt 852; ++$y) {
            for ($x = 64; $x -lt 576; ++$x) {
                if ($img.GetPixel($x, $y).A -ne 0) { throw "Room aperture covered: $path ($x,$y)" }
            }
        }
    } finally { $img.Dispose() }
}

$preview = New-Object Drawing.Bitmap 936, 1030, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [Drawing.Graphics]::FromImage($preview)
try {
    $g.Clear([Drawing.Color]::FromArgb(25, 42, 47))
    $base = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_04_base_stage_0.png'))
    try { $g.DrawImageUnscaled($base, 164, 852) } finally { $base.Dispose() }
    for ($floor = 0; $floor -lt 4; ++$floor) {
        $roomStage = if ($floor -eq 3) { 0 } else { 5 }
        $room = [Drawing.Bitmap]::FromFile((Join-Path $root ('Resources/res/castle_room_{0:d2}_{1}.png' -f ($floor + 1), $roomStage)))
        try { $g.DrawImageUnscaled($room, 164, 340 + (3 - $floor) * 128) }
        finally { $room.Dispose() }
    }
    $shell = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_04_hollow_stage_0.png'))
    try { $g.DrawImageUnscaled($shell, 100, 0) } finally { $shell.Dispose() }
    $wheel = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_04_wheel_stage_0.png'))
    try {
        $g.DrawImage($wheel, (New-Object Drawing.Rectangle 235, 913, 114, 114))
        $g.DrawImage($wheel, (New-Object Drawing.Rectangle 491, 913, 114, 114))
    } finally { $wheel.Dispose() }
    $balcony = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_04_balcony_stage_0.png'))
    try { $g.DrawImageUnscaled($balcony, 644, 724) } finally { $balcony.Dispose() }
    $eagle = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_04_eagle.png'))
    try { $g.DrawImageUnscaled($eagle, 18, 692) } finally { $eagle.Dispose() }
} finally { $g.Dispose() }
try { $preview.Save((Join-Path $PSScriptRoot 'preview_castle_04_hollow.png'), [Drawing.Imaging.ImageFormat]::Png) }
finally { $preview.Dispose() }
Write-Host 'Built castle 4 white-stone shell: 640x852, clear 512x512 opening, separate eagle.'
