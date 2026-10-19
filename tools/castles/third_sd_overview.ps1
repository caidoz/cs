param()
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
Add-Type -AssemblyName System.Drawing
$assetDir=Join-Path $root 'content/castles/third_modular_sd_v1'
$font=New-Object System.Drawing.Font 'Segoe UI',18
$title=New-Object System.Drawing.Font 'Segoe UI',23
try {
    foreach($state in 'closed','open') {
        $canvas=New-Object System.Drawing.Bitmap 1200,1100
        $g=[System.Drawing.Graphics]::FromImage($canvas)
        try {
            $g.Clear([System.Drawing.Color]::FromArgb(24,34,49))
            $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            $g.DrawString("CASTLE 03 / GRANITE BASTION / $state",$title,[System.Drawing.Brushes]::White,22,12)
            foreach($stage in 0..5) {
                $dir=$assetDir
                if($stage -gt 0) { $dir=Join-Path $assetDir "upgrade-$stage" }
                $image=[System.Drawing.Image]::FromFile((Join-Path $dir "reassembled-game-$state.png"))
                try {
                    $x=($stage%3)*400
                    $y=[Math]::Floor($stage/3)*510+65
                    $g.DrawString("Lv.$stage",$font,[System.Drawing.Brushes]::Gold,[single]($x+20),[single]$y)
                    $g.DrawImage($image,[System.Drawing.Rectangle]::new($x+10,$y+28,380,466))
                } finally { $image.Dispose() }
            }
            $name=if($state -eq 'closed') { 'upgrade-overview.png' } else { 'room-overview.png' }
            $canvas.Save((Join-Path $assetDir $name),[System.Drawing.Imaging.ImageFormat]::Png)
        } finally { $g.Dispose(); $canvas.Dispose() }
    }
    # Equal viewport width and a shared authored wheel-contact line.
    $canvas=New-Object System.Drawing.Bitmap 1150,650
    $g=[System.Drawing.Graphics]::FromImage($canvas)
    try {
        $g.Clear([System.Drawing.Color]::FromArgb(24,34,49))
        $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $g.DrawString('CASTLES 01 - 03 / SAME WIDTH / SHARED GROUND',$title,[System.Drawing.Brushes]::White,20,14)
        $dirs=@('starter_modular_sd_v1','second_modular_sd_v1','third_modular_sd_v1')
        $grounds=@(990,1163,1321)
        $labels=@('01 / WOOD / 1 ROOM','02 / SANDSTONE / 2 ROOMS','03 / GRANITE / 3 ROOMS')
        foreach($i in 0..2) {
            $image=[System.Drawing.Image]::FromFile((Join-Path $root "content/castles/$($dirs[$i])/reassembled-game-closed.png"))
            try {
                $unit=350.0/$image.Width
                $x=15+$i*380
                $y=570-$grounds[$i]*$unit
                $g.DrawImage($image,[System.Drawing.RectangleF]::new($x,$y,350,$image.Height*$unit))
                $g.DrawString($labels[$i],$font,[System.Drawing.Brushes]::White,[single]$x,600)
            } finally { $image.Dispose() }
        }
        $g.DrawLine([System.Drawing.Pens]::SlateGray,10,570,1140,570)
        $canvas.Save((Join-Path $assetDir 'castle-01-03-comparison.png'),[System.Drawing.Imaging.ImageFormat]::Png)
    } finally { $g.Dispose(); $canvas.Dispose() }
} finally { $font.Dispose(); $title.Dispose() }
