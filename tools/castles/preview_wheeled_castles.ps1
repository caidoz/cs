$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$res = Join-Path $root 'Resources/res'
$out = Join-Path $PSScriptRoot 'preview_wheeled_castles_02_10.png'
$sheet = New-Object Drawing.Bitmap 1280,2070,([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [Drawing.Graphics]::FromImage($sheet)
try {
    $g.Clear([Drawing.Color]::FromArgb(24,41,47))
    foreach ($castle in 2..10) {
        $n = '{0:D2}' -f $castle
        foreach ($stage in @(0,5)) {
            $x = 0
            if ($stage -eq 5) { $x = 640 }
            $y = ($castle-2)*230
            $base = [Drawing.Bitmap]::FromFile((Join-Path $res "castle_mobility/castle_${n}_base_stage_${stage}.png"))
            $room = [Drawing.Bitmap]::FromFile((Join-Path $res 'castle_room_01_5.png'))
            $shell = [Drawing.Bitmap]::FromFile((Join-Path $res "castle_exterior/castle_${n}_hollow_stage_${stage}.png"))
            $wheel = [Drawing.Bitmap]::FromFile((Join-Path $res "castle_mobility/castle_${n}_wheel_stage_${stage}.png"))
            try {
                $g.DrawImageUnscaled($base,$x+64,$y+112)
                $g.DrawImageUnscaled($room,$x+64,$y)
                $dst = New-Object Drawing.Rectangle ($x),($y),640,128
                $src = New-Object Drawing.Rectangle 0,($shell.Height-128),640,128
                $g.DrawImage($shell,$dst,$src,[Drawing.GraphicsUnit]::Pixel)
                $g.DrawImageUnscaled($wheel,$x+128,$y+112)
                $g.DrawImageUnscaled($wheel,$x+384,$y+112)
            } finally {
                $wheel.Dispose(); $shell.Dispose(); $room.Dispose(); $base.Dispose()
            }
        }
    }
} finally { $g.Dispose() }
try { $sheet.Save($out,[Drawing.Imaging.ImageFormat]::Png) } finally { $sheet.Dispose() }
Write-Host $out
