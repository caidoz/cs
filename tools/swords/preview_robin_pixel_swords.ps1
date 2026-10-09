param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

Add-Type -AssemblyName System.Drawing
$outDir = Join-Path $Root 'output\robin_sword_pixel_art'
New-Item -ItemType Directory -Force -Path $outDir | Out-Null

foreach ($id in @(1, 35)) {
    $source = [System.Drawing.Bitmap]::FromFile((Join-Path $outDir "concept_$id.png"))
    try {
        $minX = $source.Width; $minY = $source.Height; $maxX = -1; $maxY = -1
        for ($y = 0; $y -lt $source.Height; $y++) {
            for ($x = 0; $x -lt $source.Width; $x++) {
                if ($source.GetPixel($x, $y).A -gt 16) {
                    $minX = [Math]::Min($minX, $x); $maxX = [Math]::Max($maxX, $x)
                    $minY = [Math]::Min($minY, $y); $maxY = [Math]::Max($maxY, $y)
                }
            }
        }
        $width = if ($id -eq 1) { 32 } else { 64 }
        $height = if ($id -eq 1) { 64 } else { 128 }
        $artW = $maxX - $minX + 1; $artH = $maxY - $minY + 1
        $scale = [Math]::Min(($width - 4.0) / $artW, ($height - 4.0) / $artH)
        $drawW = if ($id -eq 1) { 24 } else { [int][Math]::Round($artW * $scale) }
        $drawH = [int][Math]::Round($artH * $scale)
        $native = [System.Drawing.Bitmap]::new($width, $height, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [System.Drawing.Graphics]::FromImage($native)
        try {
            $g.Clear([System.Drawing.Color]::Transparent)
            $g.CompositingMode = [System.Drawing.Drawing2D.CompositingMode]::SourceCopy
            $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
            $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
            $g.DrawImage($source,
                [System.Drawing.Rectangle]::new([int][Math]::Floor(($width - $drawW) / 2), [int][Math]::Floor(($height - $drawH) / 2), $drawW, $drawH),
                [System.Drawing.Rectangle]::new($minX, $minY, $artW, $artH),
                [System.Drawing.GraphicsUnit]::Pixel)
        } finally { $g.Dispose() }
        try { $native.Save((Join-Path $outDir "pixel_$id.png"), [System.Drawing.Imaging.ImageFormat]::Png) }
        finally { $native.Dispose() }
    } finally { $source.Dispose() }
}

$board = [System.Drawing.Bitmap]::new(740, 1000, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [System.Drawing.Graphics]::FromImage($board)
$g.Clear([System.Drawing.Color]::FromArgb(17, 23, 36))
$titleFont = [System.Drawing.Font]::new('Malgun Gothic', 17, [System.Drawing.FontStyle]::Bold)
$labelFont = [System.Drawing.Font]::new('Malgun Gothic', 12, [System.Drawing.FontStyle]::Regular)
$white = [System.Drawing.SolidBrush]::new([System.Drawing.Color]::FromArgb(235, 240, 250))
$blue = [System.Drawing.Pen]::new([System.Drawing.Color]::FromArgb(86, 127, 178), 1)
try {
    $g.DrawString('ROBIN  |  FIRST & LAST SWORD', $titleFont, $white, 34, 14)
    foreach ($column in @(@{ x=65; text='BEFORE' }, @{ x=420; text='PIXEL ART' })) {
        $g.DrawString($column.text, $labelFont, $white, $column.x, 59)
    }
    foreach ($item in @(@{ id=1; top=96; label='1  |  1 x 2  |  32 x 64' },
                       @{ id=35; top=390; label='35  |  2 x 4  |  64 x 128' })) {
        $g.DrawString($item.label, $labelFont, $white, 33, $item.top)
        $nativeW = if ($item.id -eq 1) { 32 } else { 64 }
        $nativeH = if ($item.id -eq 1) { 64 } else { 128 }
        $scale = 4
        $drawW = $nativeW * $scale; $drawH = $nativeH * $scale
        $top = $item.top + 36
        foreach ($column in @(@{ x=60; file="Resources\res\w0_$($item.id).png" },
                             @{ x=415; file="output\robin_sword_pixel_art\pixel_$($item.id).png" })) {
            $left = $column.x + [int][Math]::Floor((256 - $drawW) / 2)
            $path = Join-Path $Root $column.file
            for ($x = 0; $x -le $nativeW; $x += 32) {
                $gx = $left + $x * $scale
                $g.DrawLine($blue, $gx, $top, $gx, $top + $drawH)
            }
            for ($y = 0; $y -le $nativeH; $y += 32) {
                $gy = $top + $y * $scale
                $g.DrawLine($blue, $left, $gy, $left + $drawW, $gy)
            }
            $sprite = [System.Drawing.Bitmap]::FromFile($path)
            try {
                $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
                $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
                $g.DrawImage($sprite, [System.Drawing.Rectangle]::new($left, $top, $drawW, $drawH))
            } finally { $sprite.Dispose() }
        }
    }
} finally {
    $blue.Dispose(); $white.Dispose(); $labelFont.Dispose(); $titleFont.Dispose(); $g.Dispose()
}
try { $board.Save((Join-Path $outDir 'before_after.png'), [System.Drawing.Imaging.ImageFormat]::Png) }
finally { $board.Dispose() }
Write-Output (Join-Path $outDir 'before_after.png')
