param(
    [string]$SourceDir = (Join-Path $PSScriptRoot 'helmet_sheets'),
    [string]$OutputDir = (Join-Path (Resolve-Path (Join-Path $PSScriptRoot '..\..')) 'Resources\res\inventory_helm')
)

Add-Type -AssemblyName System.Drawing
New-Item -ItemType Directory -Path $OutputDir -Force | Out-Null

foreach ($hero in @('robin', 'diana', 'maxx')) {
    $source = Join-Path $SourceDir ($hero + '.png')
    $sheet = [System.Drawing.Bitmap]::FromFile($source)
    try {
        if ($sheet.Width -lt 8 -or $sheet.Height -lt 8) { throw "Invalid sheet: $source" }
        # Generated sheets retain transparent columns between objects, but
        # their centers are not evenly spaced. Segment those empty columns so
        # feathers and horns cannot be cut by a mathematical eighth.
        $runs = New-Object 'System.Collections.Generic.List[System.Drawing.Rectangle]'
        $start = -1
        for ($x = 0; $x -le $sheet.Width; $x++) {
            $occupied = $false
            if ($x -lt $sheet.Width) {
                for ($y = 0; $y -lt $sheet.Height; $y++) {
                    if ($sheet.GetPixel($x, $y).A -gt 16) { $occupied = $true; break }
                }
            }
            if ($occupied -and $start -lt 0) { $start = $x }
            if (-not $occupied -and $start -ge 0) {
                $runs.Add([System.Drawing.Rectangle]::new([int]$start, 0, [int]($x - $start), [int]$sheet.Height))
                $start = -1
            }
        }
        if ($runs.Count -ne 8) { throw "Expected 8 separated helmets in ${hero}: found $($runs.Count)" }
        for ($i = 0; $i -lt 8; $i++) {
            $x0 = $runs[$i].Left
            $x1 = $runs[$i].Right - 1
            $minX = $x1; $maxX = $x0; $minY = $sheet.Height; $maxY = -1
            for ($y = 0; $y -lt $sheet.Height; $y++) {
                for ($x = $x0; $x -le $x1; $x++) {
                    if ($sheet.GetPixel($x, $y).A -gt 16) {
                        if ($x -lt $minX) { $minX = $x }
                        if ($x -gt $maxX) { $maxX = $x }
                        if ($y -lt $minY) { $minY = $y }
                        if ($y -gt $maxY) { $maxY = $y }
                    }
                }
            }
            if ($maxY -lt 0) { throw "Missing $hero helmet $($i + 1)" }
            $srcW = $maxX - $minX + 1; $srcH = $maxY - $minY + 1
            $factor = [Math]::Min(112.0 / $srcW, 112.0 / $srcH)
            $drawW = [int][Math]::Round($srcW * $factor)
            $drawH = [int][Math]::Round($srcH * $factor)
            $icon = New-Object System.Drawing.Bitmap(128, 128, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
            $g = [System.Drawing.Graphics]::FromImage($icon)
            try {
                $g.Clear([System.Drawing.Color]::Transparent)
                $g.CompositingMode = [System.Drawing.Drawing2D.CompositingMode]::SourceCopy
                $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
                $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality
                $dest = New-Object System.Drawing.Rectangle([int][Math]::Floor((128 - $drawW) / 2), [int][Math]::Floor((128 - $drawH) / 2), $drawW, $drawH)
                $src = New-Object System.Drawing.Rectangle($minX, $minY, $srcW, $srcH)
                $g.DrawImage($sheet, $dest, $src, [System.Drawing.GraphicsUnit]::Pixel)
            } finally { $g.Dispose() }
            $target = Join-Path $OutputDir ("{0}_{1}.png" -f $hero, ($i + 1))
            try { $icon.Save($target, [System.Drawing.Imaging.ImageFormat]::Png) }
            finally { $icon.Dispose() }
            Write-Output $target
        }
    } finally { $sheet.Dispose() }
}

# Maxx's winged headband has a taller inventory silhouette than its sheet art.
$override = Join-Path $PSScriptRoot 'helmet_overrides\maxx_2.png'
$overrideImage = [System.Drawing.Bitmap]::FromFile($override)
try {
    if ($overrideImage.Width -ne 128 -or $overrideImage.Height -ne 128) { throw "Invalid headband override: $override" }
} finally { $overrideImage.Dispose() }
Copy-Item -LiteralPath $override -Destination (Join-Path $OutputDir 'maxx_2.png') -Force
