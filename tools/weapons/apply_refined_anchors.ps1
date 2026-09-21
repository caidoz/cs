param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

Add-Type -AssemblyName System.Drawing
$ids = @(1, 4, 7, 10, 13, 16, 19, 22)
$res = Join-Path $Root 'Resources\res'
$work = Join-Path $Root 'output\refined-weapon-anchors'
$raw = Join-Path $work 'raw'
$originals = Join-Path $work 'originals'
New-Item -ItemType Directory -Force -Path $raw, $originals | Out-Null

function Get-Bounds([System.Drawing.Bitmap]$bitmap, [int]$threshold) {
    $minX = $bitmap.Width; $minY = $bitmap.Height; $maxX = -1; $maxY = -1
    for ($y = 0; $y -lt $bitmap.Height; $y++) {
        for ($x = 0; $x -lt $bitmap.Width; $x++) {
            if ($bitmap.GetPixel($x, $y).A -gt $threshold) {
                if ($x -lt $minX) { $minX = $x }
                if ($y -lt $minY) { $minY = $y }
                if ($x -gt $maxX) { $maxX = $x }
                if ($y -gt $maxY) { $maxY = $y }
            }
        }
    }
    if ($maxX -lt 0) { throw 'Empty source image' }
    return [System.Drawing.Rectangle]::new($minX, $minY, $maxX - $minX + 1, $maxY - $minY + 1)
}

foreach ($series in @(1, 2)) {
    foreach ($index in $ids) {
        $name = "w${series}_${index}.png"
        $assetPath = Join-Path $res $name
        $originalPath = Join-Path $originals $name
        $rawPath = Join-Path $raw $name
        if (-not (Test-Path $rawPath)) { throw "Missing generated source: $rawPath" }
        if (-not (Test-Path $originalPath)) { Copy-Item -LiteralPath $assetPath -Destination $originalPath }
        $original = [System.Drawing.Bitmap]::FromFile($originalPath)
        $generated = [System.Drawing.Bitmap]::FromFile($rawPath)
        $target = Get-Bounds $original 8
        $source = Get-Bounds $generated 12

        $scale = [Math]::Min($target.Width / [double]$source.Width, $target.Height / [double]$source.Height)
        $width = [Math]::Max(1, [int][Math]::Round($source.Width * $scale))
        $height = [Math]::Max(1, [int][Math]::Round($source.Height * $scale))
        $x = $target.X + [int][Math]::Floor(($target.Width - $width) / 2)
        $y = $target.Y + [int][Math]::Floor(($target.Height - $height) / 2)

        $output = [System.Drawing.Bitmap]::new($original.Width, $original.Height, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [System.Drawing.Graphics]::FromImage($output)
        $g.Clear([System.Drawing.Color]::Transparent)
        $g.CompositingMode = [System.Drawing.Drawing2D.CompositingMode]::SourceCopy
        $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality
        $g.DrawImage($generated, [System.Drawing.Rectangle]::new($x, $y, $width, $height), $source, [System.Drawing.GraphicsUnit]::Pixel)
        $g.Dispose()
        $original.Dispose()
        $generated.Dispose()

        $tempPath = "$assetPath.refined.png"
        $output.Save($tempPath, [System.Drawing.Imaging.ImageFormat]::Png)
        $output.Dispose()
        Move-Item -LiteralPath $tempPath -Destination $assetPath -Force
        Write-Host "$name $($target.Width)x$($target.Height) within $($target.X),$($target.Y)"
    }
}
