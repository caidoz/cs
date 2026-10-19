param()
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
Add-Type -AssemblyName System.Drawing
$review=Join-Path $root 'output/fixed-width-review'
$canvas=[System.Drawing.Bitmap]::new(960,486)
$g=[System.Drawing.Graphics]::FromImage($canvas)
$font=[System.Drawing.Font]::new('Segoe UI',15)
try {
 $g.Clear([System.Drawing.Color]::FromArgb(24,34,49))
 $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
 $images=@('castle-01-base.png','castle-10-base.png','castle-10-upper.png')
 $labels=@('01 / WIDTH 352','10 / WIDTH 352','10 / VERTICAL PAN')
 for($i=0;$i -lt 3;$i++) {
  $im=[System.Drawing.Image]::FromFile((Join-Path $review $images[$i]))
  try {$g.DrawString($labels[$i],$font,[System.Drawing.Brushes]::White,[single]($i*320+5),5);$g.DrawImage($im,[System.Drawing.Rectangle]::new($i*320,36,320,450))}
  finally {$im.Dispose()}
 }
 $canvas.Save((Join-Path $review 'comparison.png'),[System.Drawing.Imaging.ImageFormat]::Png)
} finally {$font.Dispose();$g.Dispose();$canvas.Dispose()}
