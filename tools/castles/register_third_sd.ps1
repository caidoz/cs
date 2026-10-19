param([ValidateRange(0,5)][int]$Stage=0)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
Add-Type -AssemblyName System.Drawing
$assetDir=Join-Path $root 'content/castles/third_modular_sd_v1'
if($Stage -gt 0) { $assetDir=Join-Path $assetDir "upgrade-$Stage" }
$source=Join-Path $assetDir 'generated-master.png'
$target=Join-Path $assetDir 'assembled-master.png'
if(!(Test-Path -LiteralPath $source)) { Copy-Item -LiteralPath $target -Destination $source }
# Register wheel hubs and deck across generated variants, without repainting.
$scaleX=1.0; $scaleY=1.0; $offsetX=0.0; $offsetY=0.0
if($Stage -eq 2) { $scaleX=450.0/456.0; $offsetX=274.0-279.0*$scaleX; $offsetY=-1.0 }
if($Stage -eq 3) { $scaleX=450.0/438.0; $offsetX=274.0-261.0*$scaleX; $offsetY=-30.0 }
$src=[System.Drawing.Image]::FromFile($source)
$dst=New-Object System.Drawing.Bitmap 1133,1388
$g=[System.Drawing.Graphics]::FromImage($dst)
try {
    $g.CompositingMode=[System.Drawing.Drawing2D.CompositingMode]::SourceCopy
    $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
    $rect=[System.Drawing.RectangleF]::new($offsetX,$offsetY,$src.Width*$scaleX,$src.Height*$scaleY)
    $g.DrawImage($src,$rect,[System.Drawing.RectangleF]::new(0,0,$src.Width,$src.Height),[System.Drawing.GraphicsUnit]::Pixel)
    $dst.Save($target,[System.Drawing.Imaging.ImageFormat]::Png)
} finally { $g.Dispose(); $src.Dispose(); $dst.Dispose() }
"PASS stage $Stage canvas and wheel-hub registration"
