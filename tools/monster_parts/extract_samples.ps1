param([string]$OutputDir = 'output/monster-parts-sample/extracted', [switch]$LibraryOnly)
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
$root = Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$out = Join-Path $root $OutputDir
New-Item -ItemType Directory -Force $out | Out-Null
$pack = [IO.File]::ReadAllBytes((Join-Path $root 'Resources/data/content.pack'))
if ([BitConverter]::ToUInt32($pack,0) -ne 0x314B5049) { throw 'Invalid content pack' }
$entryCount = [BitConverter]::ToInt32($pack,8)
$dataStart = 16 + $entryCount*48
function Read-PackArray([string]$name) {
    for ($j=0; $j -lt $entryCount; $j++) {
        $e=16+$j*48
        $key=[Text.Encoding]::ASCII.GetString($pack,$e,32).TrimEnd([char]0)
        if ($key -ne $name) { continue }
        $size=$pack[$e+32]
        $count=[BitConverter]::ToUInt32($pack,$e+36)
        $start=$dataStart+[BitConverter]::ToUInt32($pack,$e+40)
        for ($k=0; $k -lt $count; $k++) {
            if ($size -eq 2) { [BitConverter]::ToUInt16($pack,$start+$k*2) }
            elseif ($size -eq 4) { [BitConverter]::ToUInt32($pack,$start+$k*4) }
            else { throw "Unexpected cell size $size" }
        }
        return
    }
    throw "Missing pack array $name"
}
$offsets = @(Read-PackArray 'cmfOffBlob')
$slots = @(Read-PackArray 'cmfOffSlot')
$sheetRanges = @(Read-PackArray 'cmfImgOff')
if ($LibraryOnly) { return }
$canvas = New-Object Drawing.Bitmap 1120,1560
$g = [Drawing.Graphics]::FromImage($canvas)
$g.Clear([Drawing.Color]::FromArgb(23,27,38))
$g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
$g.PixelOffsetMode = [Drawing.Drawing2D.PixelOffsetMode]::Half
$font = New-Object Drawing.Font 'Malgun Gothic',13
$records = @()
$top = 10
foreach ($id in @(13,9,42)) {
    $sheet = [Drawing.Bitmap]::FromFile((Join-Path $root "Resources/res/c$id.png"))
    $header = [IO.File]::ReadAllText((Join-Path $root "Classes/Cmf/c$id.h"))
    $count = [int][regex]::Match($header,"TOTALC${id}OFF\s*=\s*(\d+)").Groups[1].Value
    $g.DrawString("c$id / $count source rectangles",$font,[Drawing.Brushes]::White,10,$top)
    $top += 35
    $first=$sheetRanges[$id*5]
    $end=[math]::Min($count,$sheetRanges[$id*5+1])
    for ($i=$first; $i -lt $end; $i++) {
        $p = $slots[$id] + $i*4
        $x,$y,$w,$h = $offsets[$p..($p+3)]
        # Shipped PNG sheets already use CMF's 2x coordinates.
        if ($x+$w -gt $sheet.Width -or $y+$h -gt $sheet.Height) { throw "Out of bounds c$id part $i at $p : $x,$y,$w,$h (slot $($slots[$id]))" }
        $rect = New-Object Drawing.Rectangle $x,$y,$w,$h
        $part = $sheet.Clone($rect,[Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $filename = "c${id}_part_{0:d2}.png" -f $i
        $part.Save((Join-Path $out $filename),[Drawing.Imaging.ImageFormat]::Png)
        $cx=(($i-$first)%7)*160; $cy=$top+[math]::Floor(($i-$first)/7)*125
        $g.FillRectangle([Drawing.Brushes]::DarkSlateGray,$cx+4,$cy+4,152,94)
        $scale=[math]::Max(1,[math]::Min(4,[math]::Floor([math]::Min(144/$w,86/$h))))
        $dest=New-Object Drawing.Rectangle ([int]($cx+80-$w*$scale/2)),([int]($cy+48-$h*$scale/2)),([int]($w*$scale)),([int]($h*$scale))
        $g.DrawImage($part,$dest,0,0,$w,$h,[Drawing.GraphicsUnit]::Pixel)
        $g.DrawString("#$i (${w}x${h})",$font,[Drawing.Brushes]::White,$cx+8,$cy+98)
        $records += [pscustomobject]@{cmf=$id;part=$i;sheet="Resources/res/c$id.png";rect=@($x,$y,$w,$h);file=$filename}
        $part.Dispose()
    }
    $top += [math]::Ceiling(($end-$first)/7)*125+25
    $sheet.Dispose()
}
$canvas.Save((Join-Path $out 'source-parts-contact.png'),[Drawing.Imaging.ImageFormat]::Png)
$records | ConvertTo-Json -Depth 5 | Set-Content (Join-Path $out 'sources.json') -Encoding UTF8
$g.Dispose(); $canvas.Dispose(); $font.Dispose()
Write-Output "Extracted $($records.Count) original CMF parts into $out"
