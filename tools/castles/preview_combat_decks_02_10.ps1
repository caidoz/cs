$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$res = Join-Path $root 'Resources/res'
$out = Join-Path $PSScriptRoot 'preview_combat_decks_02_10.png'
$sheet = New-Object Drawing.Bitmap 1520,3240,([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [Drawing.Graphics]::FromImage($sheet)
try {
    $g.Clear([Drawing.Color]::FromArgb(24,41,47))
    foreach ($castle in 2..10) {
        $n = '{0:D2}' -f $castle
        foreach ($stage in @(0,5)) {
            $column = if ($stage -eq 5) { 760 } else { 0 }
            $row = ($castle-2)*360
            $deck = [Drawing.Bitmap]::FromFile((Join-Path $res "castle_exterior/castle_${n}_combat_deck_stage_${stage}.png"))
            $room = [Drawing.Bitmap]::FromFile((Join-Path $res 'castle_room_01_5.png'))
            $shell = [Drawing.Bitmap]::FromFile((Join-Path $res "castle_exterior/castle_${n}_hollow_stage_${stage}.png"))
            $wheel = [Drawing.Bitmap]::FromFile((Join-Path $res "castle_mobility/castle_${n}_wheel_stage_${stage}.png"))
            try {
                $g.DrawImageUnscaled($deck,$column,$row+128)
                $g.DrawImageUnscaled($room,$column+112,$row)
                $dst = New-Object Drawing.Rectangle ($column+48),($row),640,128
                $src = New-Object Drawing.Rectangle 0,($shell.Height-128),640,128
                $g.DrawImage($shell,$dst,$src,[Drawing.GraphicsUnit]::Pixel)
                $g.DrawImageUnscaled($wheel,$column+176,$row+208)
                $g.DrawImageUnscaled($wheel,$column+432,$row+208)
            } finally {
                $wheel.Dispose(); $shell.Dispose(); $room.Dispose(); $deck.Dispose()
            }
        }
    }
} finally { $g.Dispose() }
try { $sheet.Save($out,[Drawing.Imaging.ImageFormat]::Png) } finally { $sheet.Dispose() }
Write-Host $out
