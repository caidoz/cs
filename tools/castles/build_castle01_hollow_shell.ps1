Add-Type -AssemblyName System.Drawing

$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$sourcePath = Join-Path $root 'tools/castles/source_shells/castle_01_full.png'
$outDir = Join-Path $root 'Resources/res/castle_exterior'
if (!(Test-Path -LiteralPath $sourcePath)) { throw "Missing source: $sourcePath" }

$source = [Drawing.Bitmap]::FromFile($sourcePath)
try {
    for ($stage = 0; $stage -lt 6; ++$stage) {
        $shell = New-Object Drawing.Bitmap 640, 288, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [Drawing.Graphics]::FromImage($shell)
        try {
            $g.Clear([Drawing.Color]::Transparent)
            $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            # Only the wooden roof/lookout is used. The generated wheels and
            # undercarriage are discarded; the game's rotating wheels remain.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 0, 640, 160),
                0, 0, $source.Width, 408, [Drawing.GraphicsUnit]::Pixel)
            # Keep the side posts thin and leave the authored room slot fully clear.
            $g.DrawImage($source, (New-Object Drawing.Rectangle 0, 160, 64, 128),
                175, 405, 117, 216, [Drawing.GraphicsUnit]::Pixel)
            $g.DrawImage($source, (New-Object Drawing.Rectangle 576, 160, 64, 128),
                1552, 405, 136, 216, [Drawing.GraphicsUnit]::Pixel)
        } finally { $g.Dispose() }
        try {
            $shell.Save((Join-Path $outDir ('castle_01_hollow_stage_{0}.png' -f $stage)),
                [Drawing.Imaging.ImageFormat]::Png)
        } finally { $shell.Dispose() }
    }
} finally { $source.Dispose() }

foreach ($stage in 0..5) {
    $path = Join-Path $outDir ('castle_01_hollow_stage_{0}.png' -f $stage)
    $img = [Drawing.Bitmap]::FromFile($path)
    try {
        if ($img.Width -ne 640 -or $img.Height -ne 288) { throw "Bad size: $path" }
        for ($y = 160; $y -lt 288; ++$y) {
            for ($x = 64; $x -lt 576; ++$x) {
                if ($img.GetPixel($x, $y).A -ne 0) { throw "Room aperture covered: $path ($x,$y)" }
            }
        }
    } finally { $img.Dispose() }
}

$preview = New-Object Drawing.Bitmap 900, 480, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [Drawing.Graphics]::FromImage($preview)
try {
    $g.Clear([Drawing.Color]::FromArgb(25, 42, 47))
    $room = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_room_01_0.png'))
    try { $g.DrawImageUnscaled($room, 124, 160) } finally { $room.Dispose() }
    $shell = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_01_hollow_stage_0.png'))
    try { $g.DrawImageUnscaled($shell, 60, 0) } finally { $shell.Dispose() }
    $base = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_01_base_stage_0.png'))
    try { $g.DrawImageUnscaled($base, 124, 288) } finally { $base.Dispose() }
    $wheel = [Drawing.Bitmap]::FromFile((Join-Path $root 'Resources/res/castle_mobility/castle_01_wheel_stage_0.png'))
    try {
        $g.DrawImage($wheel, (New-Object Drawing.Rectangle 196, 350, 112, 112))
        $g.DrawImage($wheel, (New-Object Drawing.Rectangle 452, 350, 112, 112))
    } finally { $wheel.Dispose() }
    $balcony = [Drawing.Bitmap]::FromFile((Join-Path $outDir 'castle_01_balcony_stage_0.png'))
    try { $g.DrawImageUnscaled($balcony, 604, 160) } finally { $balcony.Dispose() }
} finally { $g.Dispose() }
try { $preview.Save((Join-Path $PSScriptRoot 'preview_castle_01_hollow.png'), [Drawing.Imaging.ImageFormat]::Png) }
finally { $preview.Dispose() }

Write-Host 'Built castle 1 timber shell: 640x288, clear 512x128 opening, no baked wheels.'
