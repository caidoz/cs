param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path,
    [string]$Sheet = 'C:\Users\polyp\.codex\generated_images\01a0ad19-e9c6-79c3-9634-d83b8c4e5d36\exec-ed24c8bc-72e1-4c46-b90f-ca8a661e48a8.png'
)
Add-Type -AssemblyName System.Drawing

function Get-AlphaBounds([System.Drawing.Bitmap]$image, [System.Drawing.Rectangle]$area) {
    $left=$area.Right; $top=$area.Bottom; $right=-1; $bottom=-1
    for($y=$area.Top;$y -lt $area.Bottom;$y++) {
        for($x=$area.Left;$x -lt $area.Right;$x++) {
            if($image.GetPixel($x,$y).A -gt 8) {
                if($x-lt$left){$left=$x}; if($x-gt$right){$right=$x}
                if($y-lt$top){$top=$y}; if($y-gt$bottom){$bottom=$y}
            }
        }
    }
    if($right-lt 0){throw 'Empty generated quadrant'}
    [System.Drawing.Rectangle]::new($left,$top,$right-$left+1,$bottom-$top+1)
}

$src=[System.Drawing.Bitmap]::FromFile($Sheet)
$halfW=[int]($src.Width/2); $halfH=[int]($src.Height/2)
# Generated sheet order: starter, frost, black/gold heavy, purple/gold.
$jobs=@(
    @{N=1;  Area=[Drawing.Rectangle]::new(0,0,$halfW,$halfH);             W=32; H=64; ArtH=64; MinArtW=22; GripY=.88; Flip=$false},
    @{N=14; Area=[Drawing.Rectangle]::new($halfW,0,$halfW,$halfH);        W=64; H=96; ArtH=76; MinArtW=44; GripY=.88; Flip=$true},
    @{N=22; Area=[Drawing.Rectangle]::new(0,$halfH,$halfW,$halfH);        W=64; H=96; ArtH=84; MinArtW=58; GripY=.84; Flip=$false},
    @{N=10; Area=[Drawing.Rectangle]::new($halfW,$halfH,$halfW,$halfH);   W=64; H=96; ArtH=72; MinArtW=40; GripY=.84; Flip=$true}
)
$headerPath=Join-Path $Root 'Classes\Data\DianaGunData.h'
$header=[IO.File]::ReadAllText($headerPath,[Text.Encoding]::UTF8)
foreach($job in $jobs) {
    $bounds=Get-AlphaBounds $src $job.Area
    $scale=[Math]::Min($job.ArtH/$bounds.Height,$job.W/$bounds.Width)
    $dw=[Math]::Max($job.MinArtW,[int][Math]::Round($bounds.Width*$scale))
    $dh=[Math]::Max(1,[int][Math]::Round($bounds.Height*$scale))
    $dx=[int][Math]::Floor(($job.W-$dw)/2); $dy=[int][Math]::Floor(($job.H-$dh)/2)
    $dest=[Drawing.Bitmap]::new($job.W,$job.H,[Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g=[Drawing.Graphics]::FromImage($dest); $g.Clear([Drawing.Color]::Transparent)
    $g.CompositingMode=[Drawing.Drawing2D.CompositingMode]::SourceCopy
    $g.InterpolationMode=[Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
    $g.PixelOffsetMode=[Drawing.Drawing2D.PixelOffsetMode]::HighQuality
    $g.DrawImage($src,[Drawing.Rectangle]::new($dx,$dy,$dw,$dh),$bounds,[Drawing.GraphicsUnit]::Pixel)
    $g.Dispose()
    if($job.Flip) { $dest.RotateFlip([Drawing.RotateFlipType]::RotateNoneFlipX) }
    $out=Join-Path $Root "Resources\res\w1_$($job.N).png"; $tmp="$out.tmp.png"
    $dest.Save($tmp,[Drawing.Imaging.ImageFormat]::Png); $dest.Dispose()
    Move-Item -LiteralPath $tmp -Destination $out -Force
    # Keep the hand inside the lower grip instead of anchoring at the image edge.
    # All source sprites face the same way: muzzle up, lower grip to the right.
    $gripX=[int][Math]::Round($dx+$dw*.72)
    $gripY=[int][Math]::Round($dy+$dh*$job.GripY)
    $pat='(?m)^\s*\{\s*\d+,\s*\d+,\s*\d+,\s*\d+\s*\},(\s*// w1_'+$job.N+'\b[^\r\n]*)'
    $header=[regex]::Replace($header,$pat,"    { $($job.W), $($job.H), $gripX, $gripY },`$1")
    Write-Host "w1_$($job.N): $($job.W)x$($job.H), art ${dw}x${dh}, grip $gripX,$gripY"
}
$src.Dispose()
[IO.File]::WriteAllText($headerPath,$header,[Text.UTF8Encoding]::new($false))
