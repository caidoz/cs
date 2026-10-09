$ErrorActionPreference='Stop'
Add-Type -AssemblyName System.Drawing
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$res=Join-Path $root 'Resources/res/castle_exterior'
$out=Join-Path $PSScriptRoot 'preview_commands_02_10.png'
$sheet=[Drawing.Bitmap]::new(620,1890)
$g=[Drawing.Graphics]::FromImage($sheet)
try {
    $g.Clear([Drawing.Color]::FromArgb(23,38,45))
    $font=[Drawing.Font]::new('Arial',10)
    try {
        foreach($castle in 2..10) {
            $n='{0:D2}' -f $castle
            $row=($castle-2)*210
            foreach($stage in @(0,5)) {
                $part=[Drawing.Bitmap]::FromFile((Join-Path $res "castle_${n}_balcony_stage_${stage}.png"))
                try {
                    $column=if($stage -eq 0){0}else{310}
                    $g.DrawImage($part,[Drawing.Rectangle]::new($column+10,$row+16,288,192))
                    $g.DrawString("$n / +$stage",$font,[Drawing.Brushes]::White,$column+10,$row+1)
                } finally { $part.Dispose() }
            }
        }
    } finally { $font.Dispose() }
} finally { $g.Dispose() }
try { $sheet.Save($out,[Drawing.Imaging.ImageFormat]::Png) } finally { $sheet.Dispose() }
Write-Host $out
