param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

Add-Type -AssemblyName System.Drawing
$items = Get-Content (Join-Path $Root 'Resources\res\inventory_boomerang\manifest.json') -Raw | ConvertFrom-Json
if ($items.Count -ne 35) { throw "Expected 35 boomerangs, found $($items.Count)" }
foreach ($item in $items) {
    $n = [int]$item.id
    $rows = if ($n -le 10) { 2 } else { 3 }
    $cols = if ($n -ge 30) { 3 } else { 2 }
    $minimumSlots = if ($rows -eq 2) { 3 } elseif ($cols -eq 2) { 4 } else { 5 }
    $maximumSlots = $rows * $cols
    if ($item.cols -ne $cols -or $item.rows -ne $rows) { throw "Wrong dimensions for $n" }
    if ($item.lostPixels -gt 40) { throw "Boomerang $n loses too much art to its cell mask" }
    $bitmap = [System.Drawing.Bitmap]::new((Join-Path $Root "Resources\res\inventory_boomerang\$n.png"))
    try {
        if ($bitmap.Width -ne $cols * 32 -or $bitmap.Height -ne $rows * 32) {
            throw "Wrong sprite size for $n"
        }
        $used = 0; $paintedTotal = 0
        for ($row = 0; $row -lt $rows; $row++) {
            for ($col = 0; $col -lt $cols; $col++) {
                $occupied = ($item.cells -band (1 -shl ($row * 4 + $col))) -ne 0
                if ($occupied) { $used++ }
                $painted = 0
                for ($y = ($rows - 1 - $row) * 32; $y -lt ($rows - $row) * 32; $y++) {
                    for ($x = $col * 32; $x -lt ($col + 1) * 32; $x++) {
                        if ($bitmap.GetPixel($x, $y).A -gt 16) { $painted++ }
                    }
                }
                if (-not $occupied -and $painted -gt 0) { throw "Artwork enters $n's empty cell" }
                if ($n -le 10 -and $occupied -and $painted -lt 60) {
                    throw "Early boomerang $n does not visibly fill its occupied cell"
                }
                $paintedTotal += $painted
            }
        }
        if ($used -lt $minimumSlots -or $used -gt $maximumSlots -or $paintedTotal -lt 50) {
            throw "Bad occupied shape for $n"
        }
    } finally {
        $bitmap.Dispose()
    }
}
Write-Output 'All 35 boomerangs match their visible inventory masks'
