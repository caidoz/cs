Add-Type -AssemblyName System.Drawing

$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$sourcePath = Join-Path $root 'tools/castles/source_shells/castle_02_full.png'
$outDir = Join-Path $root 'Resources/res/castle_exterior'
if (!(Test-Path -LiteralPath $sourcePath)) { throw "Missing source: $sourcePath" }

$source = [Drawing.Bitmap]::FromFile($sourcePath)
try {
    for ($stage = 0; $stage -lt 6; ++$stage) {
        $shell = New-Object Drawing.Bitmap 640, 476, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [Drawing.Graphics]::FromImage($shell)
        try {
            $g.Clear([Drawing.Color]::Transparent)
            $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            # A single low blue turret and stone parapet form the crown.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 640, 220),
                0, 0, 1536, 525, [Drawing.GraphicsUnit]::Pixel)
            # Slim stone/iron side strips wrap exactly two 512x128 rooms.
            # Neither the AI's interior shadows nor its horizontal bars are used.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 220, 64, 256),
                171, 527, 149, 407, [Drawing.GraphicsUnit]::Pixel)
            $g.DrawImage($source, (New-Object Drawing.Rectangle 576, 220, 64, 256),
                1216, 527, 147, 407, [Drawing.GraphicsUnit]::Pixel)
        } finally { $g.Dispose() }
        try {
            $shell.Save((Join-Path $outDir ('castle_02_hollow_stage_{0}.png' -f $stage)),
                [Drawing.Imaging.ImageFormat]::Png)
        } finally { $shell.Dispose() }
    }
} finally { $source.Dispose() }

foreach ($stage in 0..5) {
    $path = Join-Path $outDir ('castle_02_hollow_stage_{0}.png' -f $stage)
    $img = [Drawing.Bitmap]::FromFile($path)
    try {
        if ($img.Width -ne 640 -or $img.Height -ne 476) { throw "Bad size: $path" }
        for ($y = 220; $y -lt 476; ++$y) {
            for ($x = 64; $x -lt 576; ++$x) {
                if ($img.GetPixel($x, $y).A -ne 0) { throw "Room aperture covered: $path ($x,$y)" }
            }
        }
    } finally { $img.Dispose() }
}

$preview = New-Object Drawing.Bitmap 900, 650, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [Drawing.Graphics]::FromImage($preview)
try {
    $g.Clear([Drawing.Color]::FromArgb(25, 42, 47))
    for ($floor = 0; $floor -lt 2; ++$floor) {
        $roomStage = if ($floor -eq 1) { 0 } else { 5 }
        $room = [Drawing.Bitmap]::FromFile((Join-Path $root ('Resources/res/castle_room_{0:d2}_{1}.png' -f ($floor + 1), $roomStage)))
        try { $g.DrawImageUnscaled($room, 124, 220 + (1 - $floor) * 128) }
        finally { $room.Dispose() }
    }
    $shell = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_02_hollow_stage_0.png'))
    try { $g.DrawImageUnscaled($shell, 60, 0) } finally { $shell.Dispose() }
    $base = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_02_base_stage_0.png'))
    try { $g.DrawImageUnscaled($base, 124, 476) } finally { $base.Dispose() }
    $wheel = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_02_wheel_stage_0.png'))
    try {
        $g.DrawImage($wheel, (New-Object Drawing.Rectangle 195, 537, 114, 114))
        $g.DrawImage($wheel, (New-Object Drawing.Rectangle 451, 537, 114, 114))
    } finally { $wheel.Dispose() }
    $balcony = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_02_balcony_stage_0.png'))
    try { $g.DrawImageUnscaled($balcony, 604, 348) } finally { $balcony.Dispose() }
} finally { $g.Dispose() }
try { $preview.Save((Join-Path $PSScriptRoot 'preview_castle_02_hollow.png'), [Drawing.Imaging.ImageFormat]::Png) }
finally { $preview.Dispose() }
Write-Host 'Built castle 2 stone shell: 640x476, clear 512x256 opening.'
