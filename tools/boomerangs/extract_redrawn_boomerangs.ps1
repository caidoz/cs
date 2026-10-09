Add-Type -AssemblyName System.Drawing
$sets = @(
    @{ file='source_1.png'; first=1; count=1 },
    @{ file='source_2_4.png'; first=2; count=3 },
    @{ file='source_5_7.png'; first=5; count=3 },
    @{ file='source_8_10.png'; first=8; count=3 }
)
foreach ($set in $sets) {
    $sheet = [System.Drawing.Bitmap]::FromFile((Join-Path $PSScriptRoot "redrawn\$($set.file)"))
    try {
        # The generated artwork is centered visually, not at exact thirds.
        # These gutters keep the wide hooked tips with their own weapon.
        $edges = if ($set.count -eq 1) { @(0, $sheet.Width) }
                 else { @(0, 690, 1390, $sheet.Width) }
        for ($i = 0; $i -lt $set.count; $i++) {
            $minX = $sheet.Width; $maxX = -1; $minY = $sheet.Height; $maxY = -1
            for ($y = 0; $y -lt $sheet.Height; $y++) {
                for ($x = $edges[$i]; $x -lt $edges[$i + 1]; $x++) {
                    if ($sheet.GetPixel($x, $y).A -gt 16) {
                        $minX = [Math]::Min($minX, $x)
                        $maxX = [Math]::Max($maxX, $x)
                        $minY = [Math]::Min($minY, $y)
                        $maxY = [Math]::Max($maxY, $y)
                    }
                }
            }
            if ($maxX -lt $minX) { throw "Empty boomerang $($set.first + $i)" }
            $w = $maxX - $minX + 1; $h = $maxY - $minY + 1
            $scale = [Math]::Min(60.0 / $w, 60.0 / $h)
            $dw = [int][Math]::Round($w * $scale); $dh = [int][Math]::Round($h * $scale)
            $icon = [System.Drawing.Bitmap]::new(64, 64, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
            $g = [System.Drawing.Graphics]::FromImage($icon)
            try {
                $g.Clear([System.Drawing.Color]::Transparent)
                $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
                $g.CompositingMode = [System.Drawing.Drawing2D.CompositingMode]::SourceCopy
                $g.DrawImage($sheet,
                    [System.Drawing.Rectangle]::new([int]((64-$dw)/2), [int]((64-$dh)/2), $dw, $dh),
                    [System.Drawing.Rectangle]::new($minX, $minY, $w, $h),
                    [System.Drawing.GraphicsUnit]::Pixel)
            } finally { $g.Dispose() }
            try { $icon.Save((Join-Path $PSScriptRoot "redrawn\$($set.first + $i).png"), [System.Drawing.Imaging.ImageFormat]::Png) }
            finally { $icon.Dispose() }
        }
    } finally { $sheet.Dispose() }
}

# Refined designs replace their initial sheet cuts. Keep a clear border so
# neither weapon tip appears clipped in a 2x2 inventory tile.
foreach ($id in @(1, 2, 3, 4)) {
    $source = [System.Drawing.Bitmap]::FromFile((Join-Path $PSScriptRoot "redrawn\override_$id.png"))
    try {
        $minX = $source.Width; $maxX = -1; $minY = $source.Height; $maxY = -1
        for ($y = 0; $y -lt $source.Height; $y++) {
            for ($x = 0; $x -lt $source.Width; $x++) {
                if ($source.GetPixel($x, $y).A -gt 16) {
                    $minX = [Math]::Min($minX, $x); $maxX = [Math]::Max($maxX, $x)
                    $minY = [Math]::Min($minY, $y); $maxY = [Math]::Max($maxY, $y)
                }
            }
        }
        $w = $maxX - $minX + 1; $h = $maxY - $minY + 1
        $scale = [Math]::Min(58.0 / $w, 58.0 / $h)
        $dw = [int][Math]::Round($w * $scale); $dh = [int][Math]::Round($h * $scale)
        $icon = [System.Drawing.Bitmap]::new(64, 64, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [System.Drawing.Graphics]::FromImage($icon)
        try {
            $g.Clear([System.Drawing.Color]::Transparent)
            $g.CompositingMode = [System.Drawing.Drawing2D.CompositingMode]::SourceCopy
            $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            $g.DrawImage($source,
                [System.Drawing.Rectangle]::new([int]((64-$dw)/2), [int]((64-$dh)/2), $dw, $dh),
                [System.Drawing.Rectangle]::new($minX, $minY, $w, $h),
                [System.Drawing.GraphicsUnit]::Pixel)
        } finally { $g.Dispose() }
        try { $icon.Save((Join-Path $PSScriptRoot "redrawn\$id.png"), [System.Drawing.Imaging.ImageFormat]::Png) }
        finally { $icon.Dispose() }
    } finally { $source.Dispose() }
}

# The remaining three-icon sheets sometimes include a tiny fragment from a
# neighboring panel. Remove only isolated alpha components under 32 pixels;
# the weapon's connected body and its deliberately wide arms remain intact.
foreach ($id in 5..10) {
    $path = Join-Path $PSScriptRoot "redrawn\$id.png"
    $bitmap = [System.Drawing.Bitmap]::FromFile($path)
    $seen = [bool[]]::new(4096)
    $components = [System.Collections.Generic.List[object]]::new()
    for ($start = 0; $start -lt 4096; $start++) {
        if ($seen[$start]) { continue }
        $seen[$start] = $true
        $sx = $start % 64; $sy = [int][Math]::Floor($start / 64)
        if ($bitmap.GetPixel($sx, $sy).A -le 16) { continue }
        $pixels = [System.Collections.Generic.List[int]]::new()
        $queue = [System.Collections.Generic.Queue[int]]::new()
        $queue.Enqueue($start)
        while ($queue.Count -gt 0) {
            $pixel = $queue.Dequeue(); $pixels.Add($pixel)
            $px = $pixel % 64; $py = [int][Math]::Floor($pixel / 64)
            for ($dy = -1; $dy -le 1; $dy++) {
                for ($dx = -1; $dx -le 1; $dx++) {
                    $nx = $px + $dx; $ny = $py + $dy
                    if ($nx -lt 0 -or $nx -ge 64 -or $ny -lt 0 -or $ny -ge 64) { continue }
                    $neighbor = $ny * 64 + $nx
                    if ($seen[$neighbor]) { continue }
                    $seen[$neighbor] = $true
                    if ($bitmap.GetPixel($nx, $ny).A -gt 16) { $queue.Enqueue($neighbor) }
                }
            }
        }
        $components.Add($pixels)
    }
    $clean = [System.Drawing.Bitmap]$bitmap.Clone()
    $bitmap.Dispose()
    foreach ($component in $components) {
        if ($component.Count -ge 32) { continue }
        foreach ($pixel in $component) {
            $clean.SetPixel($pixel % 64, [int][Math]::Floor($pixel / 64), [System.Drawing.Color]::Transparent)
        }
    }
    # A few sheet panels overlap by a thin strip at the left edge; that strip
    # belongs to the preceding icon, outside these weapons' silhouettes.
    if ($id -in @(6, 7, 9, 10)) {
        for ($y = 0; $y -lt 64; $y++) {
            for ($x = 0; $x -lt 14; $x++) {
                $clean.SetPixel($x, $y, [System.Drawing.Color]::Transparent)
            }
        }
    }
    $tempPath = Join-Path $PSScriptRoot "redrawn\$id.cleaned.png"
    try { $clean.Save($tempPath, [System.Drawing.Imaging.ImageFormat]::Png) }
    finally { $clean.Dispose() }
    Move-Item -LiteralPath $tempPath -Destination $path -Force
}
