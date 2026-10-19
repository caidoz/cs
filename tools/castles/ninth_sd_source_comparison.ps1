param()
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
Add-Type -AssemblyName System.Drawing
$dir=Join-Path $root 'content/castles/ninth_modular_sd_v1'
$canvas=[System.Drawing.Bitmap]::new(1000,1300)
$g=[System.Drawing.Graphics]::FromImage($canvas)
$font=[System.Drawing.Font]::new('Segoe UI',20)
try {
 $g.Clear([System.Drawing.Color]::FromArgb(24,34,49))
 $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
 $g.DrawString('ORIGINAL ART / SAME WIDTH',$font,[System.Drawing.Brushes]::White,20,20)
 $entries=@(@('previous-wide/stage-0.png',29,19,1184,985,'BEFORE / WIDE'),@('generated-master.png',215,25,621,1493,'AFTER / TALL'))
 for($i=0;$i -lt 2;$i++) {
  $e=$entries[$i];$im=[System.Drawing.Image]::FromFile((Join-Path $dir $e[0]))
  try {
   $height=400.0*$e[4]/$e[3];$x=50+500*$i
   $g.DrawImage($im,[System.Drawing.RectangleF]::new($x,1200-$height,400,$height),[System.Drawing.RectangleF]::new($e[1],$e[2],$e[3],$e[4]),[System.Drawing.GraphicsUnit]::Pixel)
   $g.DrawString($e[5],$font,[System.Drawing.Brushes]::White,[single]$x,1230)
  } finally {$im.Dispose()}
 }
 $canvas.Save((Join-Path $dir 'source-before-after.png'),[System.Drawing.Imaging.ImageFormat]::Png)
} finally {$font.Dispose();$g.Dispose();$canvas.Dispose()}
