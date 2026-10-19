param()
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
Add-Type -AssemblyName System.Drawing
$out=Join-Path $root 'content/castles/map_icons_v1'
$dirs=@('starter','second','third','fourth','fifth','sixth','seventh','eighth','ninth','tenth')
$sheet=[System.Drawing.Bitmap]::new(1280,560)
$sg=[System.Drawing.Graphics]::FromImage($sheet)
$font=[System.Drawing.Font]::new('Segoe UI',15)
try {
 $sg.Clear([System.Drawing.Color]::FromArgb(25,34,47))
 for($i=0;$i -lt 10;$i++) {
  $src=[System.Drawing.Image]::FromFile((Join-Path $root "content/castles/$($dirs[$i])_modular_sd_v1/reassembled-game-closed.png"))
  $guide=[System.Drawing.Bitmap]::new(768,768)
  $g=[System.Drawing.Graphics]::FromImage($guide)
  try {
   $g.Clear([System.Drawing.Color]::Transparent)
   $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
   $scale=[Math]::Min(650.0/$src.Width,680.0/$src.Height)
   $g.DrawImage($src,[System.Drawing.RectangleF]::new(384-$src.Width*$scale/2,710-$src.Height*$scale,$src.Width*$scale,$src.Height*$scale))
   $guide.Save((Join-Path $out ('references/castle-{0:00}.png' -f ($i+1))),[System.Drawing.Imaging.ImageFormat]::Png)
   $x=($i%5)*256;$y=[Math]::Floor($i/5)*280
   $sg.DrawImage($guide,[System.Drawing.Rectangle]::new($x,$y,256,256))
   $sg.DrawString(('{0:00}' -f ($i+1)),$font,[System.Drawing.Brushes]::White,[single]($x+10),[single]($y+250))
  } finally {$g.Dispose();$guide.Dispose();$src.Dispose()}
 }
 $sheet.Save((Join-Path $out 'references/contact-sheet.png'),[System.Drawing.Imaging.ImageFormat]::Png)
} finally {$font.Dispose();$sg.Dispose();$sheet.Dispose()}
