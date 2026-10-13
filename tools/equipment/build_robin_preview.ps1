param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path,
    [ValidateSet('robin','diana','maxx')][string]$Hero = 'robin'
)

Add-Type -AssemblyName System.Drawing
$res=Join-Path $Root 'Resources\res'
$destination=Join-Path $Root "content\equipment\pixel_art\$Hero\final-preview.png"
$armor=@{robin='armor';diana='vest';maxx='coat'}
$preview=[System.Drawing.Bitmap]::new(1024,640,[System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g=[System.Drawing.Graphics]::FromImage($preview)
$g.Clear([System.Drawing.Color]::FromArgb(22,31,43))
$g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
$g.PixelOffsetMode=[System.Drawing.Drawing2D.PixelOffsetMode]::Half
try {
    $row=0
    foreach($kind in @('helm','armor','pants','boots','glove')) {
        for($i=0;$i -lt 8;$i++) {
            $name=if($kind -eq 'helm'){"inventory_helm\${Hero}_$($i+1).png"}
                  elseif($kind -eq 'armor'){"item_$($armor[$Hero])_${Hero}$i.png"}
                  else{"item_${kind}_${Hero}$i.png"}
            $item=[System.Drawing.Bitmap]::FromFile((Join-Path $res $name))
            try {
                $drawW=if($kind -eq 'helm' -or $kind -eq 'boots'){128}else{64}
                $drawH=if($kind -eq 'armor' -and $i -ge 6){96}else{$drawW}
                $scale=[Math]::Min(112.0/$drawW,112.0/$drawH)
                $destW=[int][Math]::Round($drawW*$scale)
                $destH=[int][Math]::Round($drawH*$scale)
                $dx=$i*128+[int][Math]::Floor((128-$destW)/2)
                $dy=$row*128+[int][Math]::Floor((128-$destH)/2)
                $g.DrawImage($item,[System.Drawing.Rectangle]::new($dx,$dy,$destW,$destH))
            }
            finally {$item.Dispose()}
        }
        $row++
    }
} finally {$g.Dispose()}
try {$preview.Save($destination,[System.Drawing.Imaging.ImageFormat]::Png)}
finally {$preview.Dispose()}
Write-Output $destination
