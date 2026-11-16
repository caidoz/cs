$ErrorActionPreference='Stop'
& (Join-Path $PSScriptRoot 'extract_samples.ps1')
Add-Type -AssemblyName System.Drawing
$root=Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$out=Join-Path $root 'output/monster-parts-sample/extracted'
$definitions=@(
    @{name='거친발멧돼지';cmf=13;parts=@(
        @{name='엄니·주둥이';id=8;crop=@(0,20,34,24);cell=@(2,1);at=@(2,0)},
        @{name='발굽';id=20;cell=@(1,2);at=@(2,1)},
        @{name='가시 가죽';id=9;cell=@(2,2);at=@(0,0)})},
    @{name='맹독해파리';cmf=9;parts=@(
        @{name='갓';id=11;cell=@(2,2);at=@(0,0)},
        @{name='촉수 다발';id=12;cell=@(1,2);at=@(2,0)},
        @{name='짧은 촉수';id=13;cell=@(1,2);at=@(3,0)})},
    @{name='드래곤좀비';cmf=42;parts=@(
        @{name='턱뼈';id=10;cell=@(2,1);at=@(2,0)},
        @{name='늑골';id=9;cell=@(2,2);at=@(0,0)},
        @{name='꼬리뼈';id=12;cell=@(1,2);at=@(4,0)},
        @{name='발톱';id=16;cell=@(1,2);at=@(2,1)})}
)
$img=New-Object Drawing.Bitmap 1440,1050
$g=[Drawing.Graphics]::FromImage($img)
$g.Clear([Drawing.Color]::FromArgb(20,24,34))
$g.InterpolationMode=[Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
$g.PixelOffsetMode=[Drawing.Drawing2D.PixelOffsetMode]::Half
$title=New-Object Drawing.Font 'Malgun Gothic',24,([Drawing.FontStyle]::Bold)
$font=New-Object Drawing.Font 'Malgun Gothic',13
$small=New-Object Drawing.Font 'Malgun Gothic',10
$g.DrawString('CMF 원본 픽셀 추출 → 인벤토리 배치',$title,[Drawing.Brushes]::Wheat,24,14)
$g.DrawString('원본 색상·투명도 유지 / 정수 배율 확대 / 새로 그린 부위 없음',$font,[Drawing.Brushes]::LightGray,26,62)
$manifest=@()
function Draw-PixelImage($image,[int]$x,[int]$y,[int]$w,[int]$h) {
    $s=[math]::Max(1,[math]::Min(4,[math]::Floor([math]::Min($w/$image.Width,$h/$image.Height))))
    $dw=$image.Width*$s; $dh=$image.Height*$s
    $r=New-Object Drawing.Rectangle ([int]($x+($w-$dw)/2)),([int]($y+($h-$dh)/2)),([int]$dw),([int]$dh)
    $g.DrawImage($image,$r,0,0,$image.Width,$image.Height,[Drawing.GraphicsUnit]::Pixel)
}
$row=0
foreach($monster in $definitions) {
    $top=110+$row*300
    $g.DrawRectangle([Drawing.Pens]::SlateGray,20,$top,1400,280)
    $g.DrawString($monster.name,$title,[Drawing.Brushes]::Wheat,36,($top+12))
    $g.DrawString('추출 부위',$font,[Drawing.Brushes]::LightGray,36,($top+60))
    $index=0
    foreach($def in $monster.parts) {
        $path=Join-Path $out ("c{0}_part_{1:d2}.png" -f $monster.cmf,$def.id)
        $source=[Drawing.Bitmap]::FromFile($path)
        $part=$source
        if($def.crop) {
            $r=New-Object Drawing.Rectangle $def.crop[0],$def.crop[1],$def.crop[2],$def.crop[3]
            $part=$source.Clone($r,[Drawing.Imaging.PixelFormat]::Format32bppArgb)
        }
        $asset="icon_c{0}_{1:d2}.png" -f $monster.cmf,$def.id
        $part.Save((Join-Path $out $asset),[Drawing.Imaging.ImageFormat]::Png)
        $x=40+$index*175
        Draw-PixelImage $part $x ($top+80) 155 132
        $g.DrawString($def.name,$font,[Drawing.Brushes]::White,$x,($top+219))
        $method=if($def.crop){'원본 추가 크롭'}else{'CMF 직접 추출'}
        $g.DrawString("$method #$($def.id)",$small,[Drawing.Brushes]::LightGray,$x,($top+247))
        $bx=940; $by=$top+30; $cell=72
        # Draw empty grid once before the first block.
        if($index -eq 0) {
            for($gy=0;$gy -lt 3;$gy++){for($gx=0;$gx -lt 6;$gx++){
                $g.DrawRectangle([Drawing.Pens]::DimGray,($bx+$gx*$cell),($by+$gy*$cell),$cell,$cell)
            }}
        }
        $px=$bx+$def.at[0]*$cell; $py=$by+$def.at[1]*$cell
        $pw=$def.cell[0]*$cell; $ph=$def.cell[1]*$cell
        $brush=New-Object Drawing.SolidBrush ([Drawing.Color]::FromArgb(75,38,48))
        $g.FillRectangle($brush,($px+2),($py+2),($pw-4),($ph-4))
        $g.DrawRectangle([Drawing.Pens]::IndianRed,($px+2),($py+2),($pw-4),($ph-4))
        Draw-PixelImage $part ($px+8) ($py+8) ($pw-16) ($ph-16)
        $brush.Dispose()
        $manifest += [pscustomobject]@{monster=$monster.name;cmf=$monster.cmf;part=$def.id;name=$def.name;method=$method;crop=$def.crop;asset=$asset;size=$def.cell;position=$def.at}
        if($part -ne $source){$part.Dispose()};$source.Dispose()
        $index++
    }
    $g.DrawString('6 × 3칸 · 배치 검토용 / 전투 수치 미적용',$small,[Drawing.Brushes]::LightGray,940,($top+252))
    $row++
}
$img.Save((Join-Path $out 'inventory-original-pixels.png'),[Drawing.Imaging.ImageFormat]::Png)
$manifest | ConvertTo-Json -Depth 6 | Set-Content (Join-Path $out 'inventory-parts.json') -Encoding UTF8
$g.Dispose();$img.Dispose();$title.Dispose();$font.Dispose();$small.Dispose()
Write-Output 'Created inventory-original-pixels.png and 10 semantic icons.'
