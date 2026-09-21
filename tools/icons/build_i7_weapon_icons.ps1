param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path
)

Add-Type -AssemblyName System.Drawing

$res = Join-Path $Root "Resources\res"
$atlasPath = Join-Path $res "i7.png"
$cell = 32
$gap = 1
$columns = 8
$iconCount = 70
$baseY = 398
$rows = [Math]::Ceiling($iconCount / [double]$columns)
$newHeight = $baseY + $rows * ($cell + $gap)

$old = [System.Drawing.Bitmap]::FromFile($atlasPath)
$atlas = New-Object System.Drawing.Bitmap $old.Width, $newHeight, ([System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [System.Drawing.Graphics]::FromImage($atlas)
$g.Clear([System.Drawing.Color]::Transparent)
$g.CompositingMode = [System.Drawing.Drawing2D.CompositingMode]::SourceCopy
$g.DrawImageUnscaled($old, 0, 0)
$old.Dispose()

function Get-AlphaBounds([System.Drawing.Bitmap]$bitmap) {
    $minX = $bitmap.Width; $minY = $bitmap.Height; $maxX = -1; $maxY = -1
    for ($y = 0; $y -lt $bitmap.Height; $y++) {
        for ($x = 0; $x -lt $bitmap.Width; $x++) {
            if ($bitmap.GetPixel($x, $y).A -gt 8) {
                if ($x -lt $minX) { $minX = $x }; if ($x -gt $maxX) { $maxX = $x }
                if ($y -lt $minY) { $minY = $y }; if ($y -gt $maxY) { $maxY = $y }
            }
        }
    }
    if ($maxX -lt 0) { return [System.Drawing.Rectangle]::new(0, 0, $bitmap.Width, $bitmap.Height) }
    return [System.Drawing.Rectangle]::new($minX, $minY, $maxX - $minX + 1, $maxY - $minY + 1)
}

$g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
$g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality
$g.CompositingQuality = [System.Drawing.Drawing2D.CompositingQuality]::HighQuality
$g.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::None

for ($n = 0; $n -lt $iconCount; $n++) {
    $series = if ($n -lt 35) { 1 } else { 2 }
    $index = ($n % 35) + 1
    $sourcePath = Join-Path $res ("w{0}_{1}.png" -f $series, $index)
    if (-not (Test-Path $sourcePath)) { throw "Missing source: $sourcePath" }
    $source = [System.Drawing.Bitmap]::FromFile($sourcePath)
    # Character-held gun textures are vertical, but inventory icons follow the
    # horizontal silhouette used by the original i4 gun row.
    if ($series -eq 1) {
        $source.RotateFlip([System.Drawing.RotateFlipType]::Rotate90FlipNone)
    }
    $bounds = Get-AlphaBounds $source
    $maxContent = 30.0
    $scale = [Math]::Min($maxContent / $bounds.Width, $maxContent / $bounds.Height)
    $dw = [Math]::Max(1, [int][Math]::Round($bounds.Width * $scale))
    $dh = [Math]::Max(1, [int][Math]::Round($bounds.Height * $scale))
    $col = $n % $columns; $row = [Math]::Floor($n / $columns)
    $dx = 1 + $col * ($cell + $gap) + [Math]::Floor(($cell - $dw) / 2)
    $dy = $baseY + $row * ($cell + $gap) + [Math]::Floor(($cell - $dh) / 2)
    $dest = [System.Drawing.Rectangle]::new($dx, $dy, $dw, $dh)
    $g.DrawImage($source, $dest, $bounds, [System.Drawing.GraphicsUnit]::Pixel)
    $source.Dispose()
}

$g.Dispose()
$tmp = "$atlasPath.tmp.png"
$atlas.Save($tmp, [System.Drawing.Imaging.ImageFormat]::Png)
$atlas.Dispose()
Move-Item -LiteralPath $tmp -Destination $atlasPath -Force
Write-Host "Built $atlasPath (265x$newHeight), 70 weapon icons at y=$baseY"
