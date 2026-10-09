param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

Add-Type -AssemblyName System.Drawing
$items = Get-Content (Join-Path $Root 'Resources\res\inventory_gun\manifest.json') -Raw | ConvertFrom-Json
if ($items.Count -ne 35) { throw "Expected 35 guns, found $($items.Count)" }
$visibleHeights = @{}
for ($n = 1; $n -le 35; $n++) {
    $item = $items[$n - 1]
    if ($item.id -ne $n) { throw "Wrong manifest order at $n" }
    $rows = if ($n -le 10) { 2 } elseif ($n -le 29) { 3 } else { 4 }
    $mask = [int]$item.cells
    if ($n -in @(32,33) -and ($item.cols -ne 2 -or $item.rows -ne 4 -or $mask -ne 0x3333)) {
        throw "Inventory gun $n must match its neighbors at 2x4"
    }
    if ($n -eq 30 -and $mask -ne 0x3333) {
        throw 'Inventory gun 30 must use the full 2x4 footprint after widening'
    }
    $bitmap = [System.Drawing.Bitmap]::new((Join-Path $Root "Resources\res\inventory_gun\$n.png"))
    try {
        if ($bitmap.Width -ne 64 -or $bitmap.Height -ne ($rows * 32)) {
            throw "Inventory gun $n has wrong dimensions"
        }
        $used = 0
        $top = $bitmap.Height; $bottom = -1
        for ($row = 0; $row -lt $rows; $row++) {
            for ($col = 0; $col -lt 2; $col++) {
                $occupied = ($mask -band (1 -shl (($rows - 1 - $row) * 4 + $col))) -ne 0
                if ($occupied) { $used++ }
                $alpha = 0
                for ($y = $row * 32; $y -lt ($row + 1) * 32; $y++) {
                    for ($x = $col * 32; $x -lt ($col + 1) * 32; $x++) {
                        if ($bitmap.GetPixel($x, $y).A -gt 16) {
                            $alpha++
                            $top = [Math]::Min($top,$y)
                            $bottom = [Math]::Max($bottom,$y)
                        }
                    }
                }
                if (-not $occupied -and $alpha -gt 0) {
                    throw "Inventory gun $n paints into an empty cell ($col,$row)"
                }
                if ($occupied -and $alpha -eq 0) {
                    throw "Inventory gun $n marks an empty cell ($col,$row) as occupied"
                }
            }
        }
        if ($n -le 10 -and ($used -ne 4 -or $mask -ne 0x33)) {
            throw "Inventory gun $n must occupy a complete 2x2 footprint"
        }
        if ($n -ge 11 -and $n -le 29 -and ($used -ne 6 -or $mask -ne 0x333)) {
            throw "Inventory gun $n must occupy a complete 2x3 footprint"
        }
        if ($used -lt 2) { throw "Inventory gun $n has too few occupied cells" }
        $visibleHeights[$n] = $bottom-$top+1
    } finally {
        $bitmap.Dispose()
    }
}
for ($i=1; $i -lt 6; $i++) {
    $stageAnchors = @(1,6,11,16,23,30)
    if ($visibleHeights[$stageAnchors[$i]] -le $visibleHeights[$stageAnchors[$i-1]]) {
        throw "Gun art does not grow between stage $i and $($i+1)"
    }
}
Write-Output 'All 35 inventory guns match their image-derived cell masks'
