$ErrorActionPreference='Stop'
Add-Type -AssemblyName System.Drawing
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$res=Join-Path $root 'Resources/res/castle_exterior'
$out=Join-Path $PSScriptRoot 'preview_spires_02_10.png'
$sheet=[Drawing.Bitmap]::new(660,1710)
$g=[Drawing.Graphics]::FromImage($sheet)
try {
    $g.Clear([Drawing.Color]::FromArgb(23,38,45))
    $font=[Drawing.Font]::new('Arial',10)
    try {
        foreach($castle in 2..10) {
            $n='{0:D2}' -f $castle
            $row=($castle-2)*190
            foreach($stage in @(0,5)) {
                $image=[Drawing.Bitmap]::FromFile((Join-Path $res "castle_${n}_roof_stage_${stage}.png"))
                try {
                    $column=if($stage -eq 0){0}else{330}
                    $w=320;$h=[int]($image.Height/2)
                    $g.DrawImage($image,[Drawing.Rectangle]::new($column+5,$row+174-$h,$w,$h))
                    $g.DrawString("$n / +$stage",$font,[Drawing.Brushes]::White,$column+6,$row+2)
                } finally { $image.Dispose() }
            }
        }
    } finally { $font.Dispose() }
} finally { $g.Dispose() }
try { $sheet.Save($out,[Drawing.Imaging.ImageFormat]::Png) } finally { $sheet.Dispose() }
Write-Host $out
