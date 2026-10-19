param()
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
Add-Type -AssemblyName System.Drawing
$assetDir=Join-Path $root 'content/castles/second_modular_sd_v1'
$canvas=New-Object System.Drawing.Bitmap 1200,900
$g=[System.Drawing.Graphics]::FromImage($canvas)
$g.Clear([System.Drawing.Color]::FromArgb(24,34,49))
$g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
$font=New-Object System.Drawing.Font 'Segoe UI',18
$title=New-Object System.Drawing.Font 'Segoe UI',23
$g.DrawString('CASTLE 02 / SANDSTONE / Lv.0 - Lv.5',$title,[System.Drawing.Brushes]::White,22,12)
try {
    foreach($stage in 0..5) {
        $dir=$assetDir
        if($stage -gt 0) { $dir=Join-Path $assetDir "upgrade-$stage" }
        $image=[System.Drawing.Image]::FromFile((Join-Path $dir 'reassembled-game-closed.png'))
        try {
            $x=($stage%3)*400
            $y=[Math]::Floor($stage/3)*420+65
            $g.DrawString("Lv.$stage",$font,[System.Drawing.Brushes]::Gold,[single]($x+20),[single]$y)
            $g.DrawImage($image,[System.Drawing.Rectangle]::new($x+8,$y+28,384,384))
        } finally { $image.Dispose() }
    }
    $canvas.Save((Join-Path $assetDir 'upgrade-overview.png'),[System.Drawing.Imaging.ImageFormat]::Png)
} finally { $g.Dispose(); $canvas.Dispose(); $font.Dispose(); $title.Dispose() }
