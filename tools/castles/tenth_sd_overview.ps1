param()
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
Add-Type -AssemblyName System.Drawing
$assetDir=Join-Path $root 'content/castles/tenth_modular_sd_v1'
$font=New-Object System.Drawing.Font 'Segoe UI',17
$title=New-Object System.Drawing.Font 'Segoe UI',22
try {
 foreach($state in 'closed','open') {
  $canvas=New-Object System.Drawing.Bitmap 1200,2000
  $g=[System.Drawing.Graphics]::FromImage($canvas)
  try {
   $g.Clear([System.Drawing.Color]::FromArgb(24,34,49))
   $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
   $g.DrawString("CASTLE 10 / ROYAL SUN PALACE / $state",$title,[System.Drawing.Brushes]::White,22,12)
   foreach($stage in 0..5) {
    $dir=$assetDir
    if($stage -gt 0) { $dir=Join-Path $assetDir "upgrade-$stage" }
    $im=[System.Drawing.Image]::FromFile((Join-Path $dir "reassembled-game-$state.png"))
    try {
     $x=($stage%3)*400; $y=[Math]::Floor($stage/3)*950+65
     $g.DrawString("Lv.$stage",$font,[System.Drawing.Brushes]::Gold,[single]($x+20),[single]$y)
     $unit=[Math]::Min(380.0/$im.Width,890.0/$im.Height)
     $g.DrawImage($im,[System.Drawing.RectangleF]::new($x+200-$im.Width*$unit/2,$y+28,$im.Width*$unit,$im.Height*$unit))
    } finally { $im.Dispose() }
   }
   $name=if($state -eq 'closed') {'upgrade-overview.png'} else {'room-overview.png'}
   $canvas.Save((Join-Path $assetDir $name),[System.Drawing.Imaging.ImageFormat]::Png)
  } finally { $g.Dispose();$canvas.Dispose() }
 }
 $canvas=New-Object System.Drawing.Bitmap 3800,1500
 $g=[System.Drawing.Graphics]::FromImage($canvas)
 try {
  $g.Clear([System.Drawing.Color]::FromArgb(24,34,49))
  $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
  $g.DrawString('CASTLES 01 - 10 / SAME WIDTH / SHARED GROUND',$title,[System.Drawing.Brushes]::White,20,14)
  $dirs=@('starter_modular_sd_v1','second_modular_sd_v1','third_modular_sd_v1','fourth_modular_sd_v1','fifth_modular_sd_v1','sixth_modular_sd_v1','seventh_modular_sd_v1','eighth_modular_sd_v1','ninth_modular_sd_v1','tenth_modular_sd_v1')
  $meta=Get-Content (Join-Path $root 'Classes/Data/TenthSdParts.h') -Raw
  $tenthGround=[int]([regex]::Match($meta,'GroundY=(\d+)').Groups[1].Value)
  $grounds=@(990,1163,1321,1472,1688,999,995,995,995,$tenthGround)
  $labels=@('01 / WOOD / 1 ROOM','02 / SANDSTONE / 2 ROOMS','03 / GRANITE / 3 ROOMS','04 / BASALT / 4 ROOMS','05 / IRON / 5 ROOMS','06 / SILVER / 6 ROOMS','07 / BLACK MARBLE / 7 ROOMS','08 / WHITE MARBLE / 8 ROOMS','09 / CRYSTAL / 9 ROOMS','10 / SUN PALACE / 10 ROOMS')
  foreach($i in 0..9) {
   $im=[System.Drawing.Image]::FromFile((Join-Path $root "content/castles/$($dirs[$i])/reassembled-game-closed.png"))
   try {
    $unit=350.0/$im.Width; $x=15+$i*380; $y=1400-$grounds[$i]*$unit
    $g.DrawImage($im,[System.Drawing.RectangleF]::new($x,$y,350,$im.Height*$unit))
    $g.DrawString($labels[$i],$font,[System.Drawing.Brushes]::White,[single]$x,1450)
   } finally { $im.Dispose() }
  }
  $g.DrawLine([System.Drawing.Pens]::SlateGray,10,1400,3790,1400)
  $canvas.Save((Join-Path $assetDir 'castle-01-10-comparison.png'),[System.Drawing.Imaging.ImageFormat]::Png)
 } finally { $g.Dispose(); $canvas.Dispose() }
 foreach($state in 'closed','open') {
  $review=Join-Path $root 'output/tenth-upgrades-review'
  if(!(Test-Path (Join-Path $review "stage-5-$state.png"))) { continue }
  $canvas=New-Object System.Drawing.Bitmap 960,950
  $g=[System.Drawing.Graphics]::FromImage($canvas)
  try {
   $g.Clear([System.Drawing.Color]::FromArgb(24,34,49))
   foreach($stage in 0..5) {
    $im=[System.Drawing.Image]::FromFile((Join-Path $review "stage-$stage-$state.png"))
    try {
     $x=($stage%3)*320; $y=[Math]::Floor($stage/3)*475
     $g.DrawString("Lv.$stage",$font,[System.Drawing.Brushes]::Gold,[single]$x,[single]$y)
     $g.DrawImage($im,[System.Drawing.Rectangle]::new($x,$y+22,320,450))
    } finally { $im.Dispose() }
   }
   $canvas.Save((Join-Path $assetDir "game-overview-$state.png"),[System.Drawing.Imaging.ImageFormat]::Png)
  } finally { $g.Dispose();$canvas.Dispose() }
 }
} finally { $font.Dispose(); $title.Dispose() }
