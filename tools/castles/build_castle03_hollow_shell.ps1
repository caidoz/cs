Add-Type -AssemblyName System.Drawing

$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$sourcePath = Join-Path $root 'tools/castles/source_shells/castle_03_full.png'
$outDir = Join-Path $root 'Resources/res/castle_exterior'
if (!(Test-Path -LiteralPath $sourcePath)) { throw "Missing source: $sourcePath" }

$source = [Drawing.Bitmap]::FromFile($sourcePath)
try {
    for ($stage = 0; $stage -lt 6; ++$stage) {
        $shell = New-Object Drawing.Bitmap 640, 726, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [Drawing.Graphics]::FromImage($shell)
        try {
            $g.Clear([Drawing.Color]::Transparent)
            $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            # The painted crown keeps its proportions. Its lower edge meets the top room.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 145, 640, 197),
                0, 0, $source.Width, 414, [Drawing.GraphicsUnit]::Pixel)
            # Three floors form one continuous shell. The 512x384 room opening
            # is never painted over; only the outside 64px strips are retained.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 342, 64, 384),
                322, 414, 64, 694, [Drawing.GraphicsUnit]::Pixel)
            $g.DrawImage($source, (New-Object Drawing.Rectangle 576, 342, 64, 384),
                1091, 414, 180, 694, [Drawing.GraphicsUnit]::Pixel)
        } finally { $g.Dispose() }
        try {
            # Stage images use one aligned silhouette. Later stages brighten the
            # same painting without changing any room aperture or attachment point.
            $path = Join-Path $outDir ('castle_03_hollow_stage_{0}.png' -f $stage)
            $shell.Save($path, [Drawing.Imaging.ImageFormat]::Png)
        } finally { $shell.Dispose() }
    }
    $lion = New-Object Drawing.Bitmap 128, 160, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g = [Drawing.Graphics]::FromImage($lion)
    try {
        $g.Clear([Drawing.Color]::Transparent)
        $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 128, 160),
            0, 575, 320, 407, [Drawing.GraphicsUnit]::Pixel)
    } finally { $g.Dispose() }
    try { $lion.Save((Join-Path $outDir 'castle_03_lion.png'), [Drawing.Imaging.ImageFormat]::Png) }
    finally { $lion.Dispose() }
} finally { $source.Dispose() }

# Validate the exact transparent opening after export.
foreach ($stage in 0..5) {
    $path = Join-Path $outDir ('castle_03_hollow_stage_{0}.png' -f $stage)
    $img = [Drawing.Bitmap]::FromFile($path)
    try {
        for ($y = 342; $y -lt 726; ++$y) {
            for ($x = 64; $x -lt 576; ++$x) {
                if ($img.GetPixel($x, $y).A -ne 0) { throw "Room aperture is covered: $path ($x,$y)" }
            }
        }
    } finally { $img.Dispose() }
}
Write-Host 'Built castle 3 hollow shell: 640x726, clear 512x384 opening, separate lion.'

$preview = New-Object Drawing.Bitmap 936, 900, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [Drawing.Graphics]::FromImage($preview)
try {
    $g.Clear([Drawing.Color]::FromArgb(25, 42, 47))
    for ($floor = 0; $floor -lt 3; ++$floor) {
        $room = [Drawing.Bitmap]::FromFile((Join-Path $root ('Resources/res/castle_room_{0:d2}_{1}.png' -f ($floor + 1), 5)))
        try { $g.DrawImageUnscaled($room, 164, 342 + (2 - $floor) * 128) }
        finally { $room.Dispose() }
    }
    $shell = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_03_hollow_stage_0.png'))
    try { $g.DrawImageUnscaled($shell, 100, 0) } finally { $shell.Dispose() }
    $lion = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_03_lion.png'))
    try { $g.DrawImageUnscaled($lion, 18, 566) } finally { $lion.Dispose() }
} finally { $g.Dispose() }
try { $preview.Save((Join-Path $PSScriptRoot 'preview_castle_03_hollow.png'), [Drawing.Imaging.ImageFormat]::Png) }
finally { $preview.Dispose() }
