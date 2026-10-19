param()
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$out=Join-Path $root 'content/castles/map_icons_v1'
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
public static class MapIconExport {
 public static Rectangle Bounds(Bitmap src) {
  int minX=src.Width,minY=src.Height,maxX=-1,maxY=-1;
  var d=src.LockBits(new Rectangle(0,0,src.Width,src.Height),ImageLockMode.ReadOnly,PixelFormat.Format32bppArgb);
  try {
   var row=new byte[src.Width*4];
   for(int y=0;y<src.Height;y++) {
    Marshal.Copy(IntPtr.Add(d.Scan0,y*d.Stride),row,0,row.Length);
    for(int x=0;x<src.Width;x++) if(row[x*4+3]>=16) {
     minX=Math.Min(minX,x);minY=Math.Min(minY,y);maxX=Math.Max(maxX,x);maxY=Math.Max(maxY,y);
    }
   }
  } finally {src.UnlockBits(d);}
  if(maxX<minX) throw new Exception("Empty map icon");
  minX=Math.Max(0,minX-6);minY=Math.Max(0,minY-6);
  maxX=Math.Min(src.Width-1,maxX+6);maxY=Math.Min(src.Height-1,maxY+6);
  return Rectangle.FromLTRB(minX,minY,maxX+1,maxY+1);
 }
}
'@
foreach($dir in 'png','preview-64','preview-96','preview-128','preview-256') { New-Item -ItemType Directory -Force (Join-Path $out $dir) | Out-Null }
$labels=@('WOOD','SANDSTONE','GRANITE','BASALT','IRON','SILVER','PHOENIX','EAGLE','CRYSTAL','SUN PALACE')
$font=[System.Drawing.Font]::new('Segoe UI',15)
try {
 foreach($level in 1..10) {
  $name='castle-map-{0:00}.png' -f $level
  $original=[System.Drawing.Image]::FromFile((Join-Path $out "originals/$name"))
  try {
   $bounds=[MapIconExport]::Bounds($original)
   foreach($size in 1024,256,128,96,64) {
    $image=[System.Drawing.Bitmap]::new($size,$size,[System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g=[System.Drawing.Graphics]::FromImage($image)
    try {
     $g.Clear([System.Drawing.Color]::Transparent)
     $g.CompositingMode=[System.Drawing.Drawing2D.CompositingMode]::SourceCopy
     $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
     $padding=$size/32.0
     $available=$size-2*$padding
     $unit=[Math]::Min($available/[double]$bounds.Width,$available/[double]$bounds.Height)
     $w=$bounds.Width*$unit;$h=$bounds.Height*$unit
     $g.DrawImage($original,[System.Drawing.RectangleF]::new(($size-$w)/2,$size-$padding-$h,$w,$h),[System.Drawing.RectangleF]::new($bounds.X,$bounds.Y,$bounds.Width,$bounds.Height),[System.Drawing.GraphicsUnit]::Pixel)
     $folder=if($size -eq 1024){'png'}else{"preview-$size"}
     $image.Save((Join-Path $out "$folder/$name"),[System.Drawing.Imaging.ImageFormat]::Png)
    } finally {$g.Dispose();$image.Dispose()}
   }
  } finally {$original.Dispose()}
 }
 foreach($theme in 'dark','light') {
  $sheet=[System.Drawing.Bitmap]::new(1280,580)
  $g=[System.Drawing.Graphics]::FromImage($sheet)
  try {
   $color=if($theme -eq 'dark'){[System.Drawing.Color]::FromArgb(16,22,35)}else{[System.Drawing.Color]::FromArgb(240,231,213)}
   $brush=if($theme -eq 'dark'){[System.Drawing.Brushes]::White}else{[System.Drawing.Brushes]::Black}
   $g.Clear($color)
   for($i=0;$i -lt 10;$i++) {
    $im=[System.Drawing.Image]::FromFile((Join-Path $out ('preview-256/castle-map-{0:00}.png' -f ($i+1))))
    try {
     $x=($i%5)*256;$y=[Math]::Floor($i/5)*290
     $g.DrawImageUnscaled($im,$x,$y)
     $g.DrawString(('{0:00} / {1}' -f ($i+1),$labels[$i]),$font,$brush,[single]($x+10),[single]($y+260))
    } finally {$im.Dispose()}
   }
   $sheet.Save((Join-Path $out "overview-$theme.png"),[System.Drawing.Imaging.ImageFormat]::Png)
  } finally {$g.Dispose();$sheet.Dispose()}
 }
 $sheet=[System.Drawing.Bitmap]::new(1000,250)
 $g=[System.Drawing.Graphics]::FromImage($sheet)
 try {
  $g.Clear([System.Drawing.Color]::FromArgb(10,15,25))
  for($i=0;$i -lt 10;$i++) {
   $g.DrawString(('{0:00}' -f ($i+1)),$font,[System.Drawing.Brushes]::White,[single]($i*100+35),2)
   foreach($size in 96,64) {
    $im=[System.Drawing.Image]::FromFile((Join-Path $out ('preview-{0}/castle-map-{1:00}.png' -f $size,($i+1))))
    try {$g.DrawImageUnscaled($im,($i*100+(100-$size)/2),$(if($size -eq 96){30}else{165}))}
    finally {$im.Dispose()}
   }
  }
  $sheet.Save((Join-Path $out 'small-size-check.png'),[System.Drawing.Imaging.ImageFormat]::Png)
 } finally {$g.Dispose();$sheet.Dispose()}
} finally {$font.Dispose()}
Compress-Archive -Path (Join-Path $out 'png/*.png') -DestinationPath (Join-Path $out 'castle-map-icons-1024.zip') -Force
'PASS exported ten 1024x1024 PNGs, small previews, contact sheets and ZIP'
