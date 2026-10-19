param()
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
Add-Type -AssemblyName System.Drawing
$assetDir=Join-Path $root 'content/castles/eighth_modular_sd_v1'
$font=New-Object System.Drawing.Font 'Segoe UI',17
$title=New-Object System.Drawing.Font 'Segoe UI',22
try {
 foreach($state in 'closed','open') {
  $canvas=New-Object System.Drawing.Bitmap 1200,2000
  $g=[System.Drawing.Graphics]::FromImage($canvas)
  try {
   $g.Clear([System.Drawing.Color]::FromArgb(24,34,49))
   $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
   $g.DrawString("CASTLE 08 / WHITE MARBLE EAGLE / $state",$title,[System.Drawing.Brushes]::White,22,12)
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
 $canvas=New-Object System.Drawing.Bitmap 3040,1300
 $g=[System.Drawing.Graphics]::FromImage($canvas)
 try {
  $g.Clear([System.Drawing.Color]::FromArgb(24,34,49))
  $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
  $g.DrawString('CASTLES 01 - 08 / SAME WIDTH / SHARED GROUND',$title,[System.Drawing.Brushes]::White,20,14)
  $dirs=@('starter_modular_sd_v1','second_modular_sd_v1','third_modular_sd_v1','fourth_modular_sd_v1','fifth_modular_sd_v1','sixth_modular_sd_v1','seventh_modular_sd_v1','eighth_modular_sd_v1')
  $meta=Get-Content (Join-Path $root 'Classes/Data/EighthSdParts.h') -Raw
  $eighthGround=[int]([regex]::Match($meta,'GroundY=(\d+)').Groups[1].Value)
  $grounds=@(990,1163,1321,1472,1688,999,995,$eighthGround)
  $labels=@('01 / WOOD / 1 ROOM','02 / SANDSTONE / 2 ROOMS','03 / GRANITE / 3 ROOMS','04 / BASALT / 4 ROOMS','05 / IRON / 5 ROOMS','06 / SILVER / 6 ROOMS','07 / BLACK MARBLE / 7 ROOMS','08 / WHITE MARBLE / 8 ROOMS')
  foreach($i in 0..7) {
   $im=[System.Drawing.Image]::FromFile((Join-Path $root "content/castles/$($dirs[$i])/reassembled-game-closed.png"))
   try {
    $unit=350.0/$im.Width; $x=15+$i*380; $y=1200-$grounds[$i]*$unit
    $g.DrawImage($im,[System.Drawing.RectangleF]::new($x,$y,350,$im.Height*$unit))
    $g.DrawString($labels[$i],$font,[System.Drawing.Brushes]::White,[single]$x,1250)
   } finally { $im.Dispose() }
  }
  $g.DrawLine([System.Drawing.Pens]::SlateGray,10,1200,3030,1200)
  $canvas.Save((Join-Path $assetDir 'castle-01-08-comparison.png'),[System.Drawing.Imaging.ImageFormat]::Png)
 } finally { $g.Dispose(); $canvas.Dispose() }
 foreach($state in 'closed','open') {
  $review=Join-Path $root 'output/eighth-upgrades-review'
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
