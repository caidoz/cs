$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$res = Join-Path $root 'Resources/res'
$out = Join-Path $root 'tools/castles/preview_castle_01_combat_parts.png'
$panelW=850; $panelH=720
$sheet=New-Object Drawing.Bitmap ($panelW*3),($panelH*2),([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g=[Drawing.Graphics]::FromImage($sheet)
function Draw-Part([string]$name,[int]$x,[int]$y) {
    $b=[Drawing.Bitmap]::FromFile((Join-Path $res $name))
    try { $g.DrawImageUnscaled($b,$x,$y) } finally { $b.Dispose() }
}
try {
    $g.Clear([Drawing.Color]::FromArgb(24,41,47))
    for($stage=0;$stage -lt 6;++$stage) {
        $ox=($stage%3)*$panelW; $oy=[int][Math]::Floor($stage/3)*$panelH
        $left=$ox+50; $roomTop=$oy+326-16; $bottom=$roomTop+128
        Draw-Part ("castle_exterior/castle_01_combat_deck_stage_{0}.png" -f $stage) $left $bottom
        Draw-Part ("castle_room_01_{0}.png" -f $stage) ($left+64) $roomTop
        Draw-Part ("castle_exterior/castle_01_wall_stage_{0}.png" -f $stage) $left $roomTop
        Draw-Part ("castle_exterior/castle_01_roof_stage_{0}.png" -f $stage) $left ($roomTop-256)
        Draw-Part ("castle_mobility/castle_01_wheel_stage_{0}.png" -f $stage) ($left+64+128-64) ($bottom+80)
        Draw-Part ("castle_mobility/castle_01_wheel_stage_{0}.png" -f $stage) ($left+64+384-64) ($bottom+80)
        Draw-Part ("castle_exterior/castle_01_cannon_stage_{0}.png" -f $stage) ($left+576) ($bottom-64)
    }
} finally { $g.Dispose() }
try { $sheet.Save($out,[Drawing.Imaging.ImageFormat]::Png) } finally { $sheet.Dispose() }
Write-Host $out
