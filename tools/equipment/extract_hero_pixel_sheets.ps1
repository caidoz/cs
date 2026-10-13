param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

# Extract the three heroes' five edited strips into native-resolution sprites.
# Artwork is sampled on a half-resolution grid then enlarged with nearest
# neighbor so highlights, outlines and silhouettes form visible pixel clusters.
Add-Type -AssemblyName System.Drawing
$armorName = @{robin='armor'; diana='vest'; maxx='coat'}
foreach ($hero in @('robin','diana','maxx')) {
    $sheetDir = Join-Path $Root "content\equipment\pixel_art\$hero"
    $output = Join-Path $sheetDir 'native_sources'
    New-Item -ItemType Directory -Path $output -Force | Out-Null
foreach ($kind in @('helm','armor','pants','boots','glove')) {
    $sheet = [System.Drawing.Bitmap]::FromFile((Join-Path $sheetDir "$kind-pixel-sheet.png"))
    try {
        for ($i = 0; $i -lt 8; $i++) {
            $left = [int][Math]::Round($i * $sheet.Width / 8.0)
            $right = [int][Math]::Round(($i + 1) * $sheet.Width / 8.0)
            $minX=$right; $minY=$sheet.Height; $maxX=-1; $maxY=-1
            for ($y=0; $y -lt $sheet.Height; $y++) {
                for ($x=$left; $x -lt $right; $x++) {
                    if ($sheet.GetPixel($x,$y).A -ge 64) {
                        $minX=[Math]::Min($minX,$x); $maxX=[Math]::Max($maxX,$x)
                        $minY=[Math]::Min($minY,$y); $maxY=[Math]::Max($maxY,$y)
                    }
                }
            }
            if ($maxX -lt $minX) { throw "Missing generated $hero $kind tier $i" }
            $width = if ($kind -eq 'helm' -or $kind -eq 'boots') {128} else {64}
            $height = if ($kind -eq 'armor' -and $i -ge 6) {96} else {$width}
            $small = [System.Drawing.Bitmap]::new(($width / 2),($height / 2),[System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
            $g=[System.Drawing.Graphics]::FromImage($small)
            try {
                $g.Clear([System.Drawing.Color]::Transparent)
                $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
                $g.PixelOffsetMode=[System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality
                $margin=if($width -eq 128){4}else{1}
                $available=$small.Width-2*$margin
                $srcW=$maxX-$minX+1; $srcH=$maxY-$minY+1
                $scale=[Math]::Min($available/[double]$srcW,$available/[double]$srcH)
                $drawW=[int][Math]::Round($srcW*$scale)
                $drawH=[int][Math]::Round($srcH*$scale)
                $dx=[int][Math]::Floor(($small.Width-$drawW)/2)
                $dy=[int][Math]::Floor(($small.Height-$drawH)/2)
                if ($kind -eq 'armor' -and $i -ge 6) {
                    # Keep the shoulders and chest proportions; grow the lower
                    # robe/skirt so the design genuinely fills its third tile.
                    $upperSrc=[int][Math]::Round($srcH*0.55)
                    $upperH=17; $lowerH=27; $startY=2
                    $g.DrawImage($sheet,[System.Drawing.Rectangle]::new($dx,$startY,$drawW,$upperH),
                        [System.Drawing.Rectangle]::new($minX,$minY,$srcW,$upperSrc),
                        [System.Drawing.GraphicsUnit]::Pixel)
                    $g.DrawImage($sheet,[System.Drawing.Rectangle]::new($dx,$startY+$upperH,$drawW,$lowerH),
                        [System.Drawing.Rectangle]::new($minX,$minY+$upperSrc,$srcW,$srcH-$upperSrc),
                        [System.Drawing.GraphicsUnit]::Pixel)
                } else {
                    $g.DrawImage($sheet,[System.Drawing.Rectangle]::new($dx,$dy,$drawW,$drawH),
                        [System.Drawing.Rectangle]::new($minX,$minY,$srcW,$srcH),
                        [System.Drawing.GraphicsUnit]::Pixel)
                }
                if ($kind -eq 'boots') {
                    $g.CompositingMode=[System.Drawing.Drawing2D.CompositingMode]::SourceCopy
                    $g.FillRectangle([System.Drawing.Brushes]::Transparent,0,0,32,32)
                }
            } finally { $g.Dispose() }
            $native=[System.Drawing.Bitmap]::new($width,$height,[System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
            for($y=0;$y -lt $height;$y++) {
                for($x=0;$x -lt $width;$x++) {
                    $color=$small.GetPixel([int][Math]::Floor($x/2),[int][Math]::Floor($y/2))
                    if($color.A -ge 80) { $native.SetPixel($x,$y,[System.Drawing.Color]::FromArgb(255,$color.R,$color.G,$color.B)) }
                }
            }
            $small.Dispose()
            $relative=if($kind -eq 'helm'){"inventory_helm\${hero}_$($i+1).png"}
                      elseif($kind -eq 'armor'){"item_$($armorName[$hero])_${hero}$i.png"}
                      else{"item_${kind}_${hero}$i.png"}
            $path=Join-Path $output $relative
            New-Item -ItemType Directory -Path (Split-Path $path) -Force | Out-Null
            try {$native.Save($path,[System.Drawing.Imaging.ImageFormat]::Png)}
            finally {$native.Dispose()}
        }
    } finally {$sheet.Dispose()}
}
}
Write-Output 'Extracted 120 hero pixel-art source sprites'
