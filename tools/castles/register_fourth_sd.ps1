param([ValidateRange(0,5)][int]$Stage=0)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$assetDir=Join-Path $root 'content/castles/fourth_modular_sd_v1'
if($Stage -gt 0) { $assetDir=Join-Path $assetDir "upgrade-$Stage" }
$source=Join-Path $assetDir 'generated-master.png'
$target=Join-Path $assetDir 'assembled-master.png'
if($Stage -ne 3) { Copy-Item -LiteralPath $source -Destination $target; return }
# The generated third upgrade sits 30px high; register its wheels to the others.
Add-Type -AssemblyName System.Drawing
$src=[System.Drawing.Image]::FromFile($source)
$dst=New-Object System.Drawing.Bitmap 1024,1536
$g=[System.Drawing.Graphics]::FromImage($dst)
try {
    $g.CompositingMode=[System.Drawing.Drawing2D.CompositingMode]::SourceCopy
    $g.DrawImageUnscaled($src,0,30)
    $dst.Save($target,[System.Drawing.Imaging.ImageFormat]::Png)
} finally { $g.Dispose(); $src.Dispose(); $dst.Dispose() }
'PASS fourth castle stage-3 wheel registration'
