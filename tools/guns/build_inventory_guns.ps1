param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

# Keep each gun in one piece. The inventory mask follows the actual opaque
# pixels; changing its silhouette to satisfy a fixed cell count broke the art.
Add-Type -AssemblyName System.Drawing
$outDir = Join-Path $Root 'Resources\res\inventory_gun'
New-Item -ItemType Directory -Path $outDir -Force | Out-Null
$records = [System.Collections.Generic.List[object]]::new()

function Keep-LargestComponent([System.Drawing.Bitmap]$bitmap) {
    $width = $bitmap.Width; $height = $bitmap.Height
    $visited = [bool[]]::new($width*$height)
    $largest = [System.Collections.Generic.List[int]]::new()
    for ($y = 0; $y -lt $height; $y++) {
        for ($x = 0; $x -lt $width; $x++) {
            $start = $y*$width+$x
            if ($visited[$start] -or $bitmap.GetPixel($x,$y).A -le 16) { continue }
            $queue = [System.Collections.Generic.Queue[int]]::new()
            $component = [System.Collections.Generic.List[int]]::new()
            $queue.Enqueue($start); $visited[$start] = $true
            while ($queue.Count) {
                $current = $queue.Dequeue(); $component.Add($current)
                $px = $current % $width; $py = [int][Math]::Floor($current/$width)
                for ($dy = -1; $dy -le 1; $dy++) {
                    for ($dx = -1; $dx -le 1; $dx++) {
                        $nx = $px+$dx; $ny = $py+$dy
                        if ($nx -lt 0 -or $nx -ge $width -or $ny -lt 0 -or $ny -ge $height) { continue }
                        $next = $ny*$width+$nx
                        if ($visited[$next] -or $bitmap.GetPixel($nx,$ny).A -le 16) { continue }
                        $visited[$next] = $true; $queue.Enqueue($next)
                    }
                }
            }
            if ($component.Count -gt $largest.Count) { $largest = $component }
        }
    }
    $keep = [bool[]]::new($width*$height)
    foreach ($pixel in $largest) { $keep[$pixel] = $true }
    for ($y = 0; $y -lt $height; $y++) {
        for ($x = 0; $x -lt $width; $x++) {
            if (-not $keep[$y*$width+$x]) {
                $bitmap.SetPixel($x,$y,[System.Drawing.Color]::Transparent)
            }
        }
    }
}

for ($n = 1; $n -le 35; $n++) {
    $rows = if ($n -le 10) { 2 } elseif ($n -le 29) { 3 } else { 4 }
    $height = $rows * 32
    if ($n -eq 30) {
        # Heavy L silhouette: widened barrel and a right-turning base.
        Copy-Item -LiteralPath (Join-Path $outDir '30_art.png') -Destination (Join-Path $outDir '30.png') -Force
        $records.Add([pscustomobject]@{id=$n;cols=2;rows=4;cells=0x3333})
        continue
    }
    if ($n -eq 19) {
        # Redrawn as one connected receiver and grip, with attached flame fins.
        Copy-Item -LiteralPath (Join-Path $outDir '19_art.png') -Destination (Join-Path $outDir '19.png') -Force
        $records.Add([pscustomobject]@{id=$n;cols=2;rows=3;cells=0x333})
        continue
    }
    $source = [System.Drawing.Bitmap]::new((Join-Path $Root "Resources\res\w1_$n.png"))
    try {
        # These source files contain detached fragments from the source sheet.
        if ($n -in @(4,7,10)) { Keep-LargestComponent $source }
        $minX = $source.Width; $minY = $source.Height; $maxX = -1; $maxY = -1
        for ($sy = 0; $sy -lt $source.Height; $sy++) {
            for ($sx = 0; $sx -lt $source.Width; $sx++) {
                if ($source.GetPixel($sx,$sy).A -gt 16) {
                    $minX = [Math]::Min($minX,$sx); $minY = [Math]::Min($minY,$sy)
                    $maxX = [Math]::Max($maxX,$sx); $maxY = [Math]::Max($maxY,$sy)
                }
            }
        }
        if ($maxX -lt $minX) { throw "Gun $n has no visible pixels" }
        $artW = $maxX - $minX + 1; $artH = $maxY - $minY + 1
        # Let the actual sprite grow with its item index. Anchor the grip at
        # the bottom so the upgraded barrel/body rises into the extra space.
        $drawH = if ($n -le 10) {
            56 + [int][Math]::Round(($n-1)*4.0/9)
        } elseif ($n -le 29) {
            80 + [int][Math]::Round(($n-11)*12.0/18)
        } else {
            $height - 4
        }
        $drawW = [int][Math]::Round($artW * $drawH / [double]$artH * 1.15)
        if ($drawW -gt 60) {
            $drawW = 60
        }
        $drawW = [Math]::Max(1,$drawW)
        if ($n -le 10) {
            # A complete 2x2 card reads much better than a tiny silhouette
            # bent to keep one cell empty. Enlarge the entire source together.
            $drawW = [Math]::Max($drawW,44 + [int][Math]::Round(($n-1)*12.0/9))
        } elseif ($n -le 29) {
            # The 3-5 star guns should carry visibly heavier housings within
            # their 2x3 card, instead of looking like thin 1-column wands.
            $drawW = [Math]::Max($drawW,52 + [int][Math]::Round(($n-11)*8.0/18))
        }
        $temp = [System.Drawing.Bitmap]::new($drawW,$height,[System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
        try {
            $g = [System.Drawing.Graphics]::FromImage($temp)
            try {
                $g.Clear([System.Drawing.Color]::Transparent)
                $g.CompositingMode = [System.Drawing.Drawing2D.CompositingMode]::SourceCopy
                $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
                $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality
                $drawY = $height-$drawH-2
                $g.DrawImage($source,[System.Drawing.Rectangle]::new(0,
                    $drawY,$drawW,$drawH),
                    [System.Drawing.Rectangle]::new($minX,$minY,$artW,$artH),[System.Drawing.GraphicsUnit]::Pixel)
            } finally { $g.Dispose() }

            $pixels = [System.Collections.Generic.List[object]]::new()
            for ($y = 0; $y -lt $height; $y++) {
                for ($x = 0; $x -lt $drawW; $x++) {
                    if ($temp.GetPixel($x,$y).A -gt 16) { $pixels.Add(@($x,$y)) }
                }
            }
            $bestScore = [int]::MaxValue; $bestX = 2; $bestMask = 0
            for ($offset = 2; $offset -le (62-$drawW); $offset++) {
                $candidate = 0
                foreach ($pixel in $pixels) {
                    $col = [int][Math]::Floor(($pixel[0]+$offset)/32)
                    $row = $rows - 1 - [int][Math]::Floor($pixel[1]/32)
                    $candidate = $candidate -bor (1 -shl ($row*4+$col))
                }
                $count = 0
                for ($bit = 0; $bit -lt ($rows*4); $bit++) {
                    if ($candidate -band (1 -shl $bit)) { $count++ }
                }
                $score = $(if ($n -le 10) { [Math]::Abs($count-4)*1000 }
                    elseif ($n -le 29) { [Math]::Abs($count-6)*1000 }
                    else { $count*1000 }) +
                    [Math]::Abs($offset - (64-$drawW)/2.0)
                if ($score -lt $bestScore) {
                    $bestScore = $score; $bestX = $offset; $bestMask = $candidate
                }
            }
            $target = [System.Drawing.Bitmap]::new(64,$height,[System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
            try {
                $g = [System.Drawing.Graphics]::FromImage($target)
                try { $g.DrawImageUnscaled($temp,$bestX,0) } finally { $g.Dispose() }
                $target.Save((Join-Path $outDir "$n.png"),[System.Drawing.Imaging.ImageFormat]::Png)
            } finally { $target.Dispose() }
            $records.Add([pscustomobject]@{id=$n;cols=2;rows=$rows;cells=$bestMask})
        } finally { $temp.Dispose() }
    } finally { $source.Dispose() }
}

$header = [System.Collections.Generic.List[string]]::new()
$header.Add('// Generated by tools/guns/build_inventory_guns.ps1.')
$header.Add('#pragma once')
$header.Add('struct InventoryGunShape { int cols, rows; unsigned short cells; };')
$header.Add('static const InventoryGunShape kInventoryGunShapes[35] = {')
foreach ($record in $records) {
    $hex = $record.cells.ToString('X')
    $header.Add("    {$($record.cols), $($record.rows), 0x$hex}, // w1_$($record.id)")
}
$header.Add('};')
[System.IO.File]::WriteAllLines((Join-Path $Root 'Classes\Data\InventoryGunShapes.h'),$header,[System.Text.UTF8Encoding]::new($false))
$records | ConvertTo-Json -Depth 2 | Set-Content -LiteralPath (Join-Path $outDir 'manifest.json') -Encoding UTF8
Write-Output 'Built 35 unwarped inventory gun sprites and matching masks'
