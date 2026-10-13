param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

Add-Type -AssemblyName System.Drawing
$res=Join-Path $Root 'Resources\res'
$base=Join-Path $Root 'content\equipment\pixel_art'
foreach($weapon in @('gun','boomerang')) {
    $canvas=[System.Drawing.Bitmap]::new(896,640,[System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g=[System.Drawing.Graphics]::FromImage($canvas)
    $g.Clear([System.Drawing.Color]::FromArgb(22,31,43))
    $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
    try {
        for($n=1;$n -le 35;$n++) {
            $item=[System.Drawing.Bitmap]::FromFile((Join-Path $res "inventory_$weapon\$n.png"))
            try {
                $col=($n-1)%7;$row=[int][Math]::Floor(($n-1)/7)
                $scale=[Math]::Min(112.0/$item.Width,112.0/$item.Height)
                $w=[int][Math]::Round($item.Width*$scale)
                $h=[int][Math]::Round($item.Height*$scale)
                $x=$col*128+[int][Math]::Floor((128-$w)/2)
                $y=$row*128+[int][Math]::Floor((128-$h)/2)
                $g.DrawImage($item,[System.Drawing.Rectangle]::new($x,$y,$w,$h))
            } finally {$item.Dispose()}
        }
    } finally {$g.Dispose()}
    try {$canvas.Save((Join-Path $base "inventory_$weapon\final-preview.png"),[System.Drawing.Imaging.ImageFormat]::Png)}
    finally {$canvas.Dispose()}
}
