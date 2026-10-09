Add-Type -AssemblyName System.Drawing

$root = (Resolve-Path (Join-Path $PSScriptRoot '../../..')).Path
$res = Join-Path $root 'Resources/res'
$out = Join-Path $PSScriptRoot 'castle_01_full_upgrade_sheet.png'
$panelW = 850; $panelH = 650
$sheet = New-Object Drawing.Bitmap ($panelW * 3), ($panelH * 2), ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$g = [Drawing.Graphics]::FromImage($sheet)
$g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic

function Draw-Asset([string]$name, [int]$x, [int]$y, [int]$w = 0, [int]$h = 0) {
    $bmp = [Drawing.Bitmap]::FromFile((Join-Path $res $name))
    try {
        if ($w -gt 0) { $g.DrawImage($bmp, (New-Object Drawing.Rectangle $x,$y,$w,$h)) }
        else { $g.DrawImageUnscaled($bmp, $x, $y) }
    } finally { $bmp.Dispose() }
}

try {
    $g.Clear([Drawing.Color]::FromArgb(24, 41, 47))
    for ($stage = 0; $stage -lt 6; $stage++) {
        $ox = ($stage % 3) * $panelW
        $oy = [Math]::Floor($stage / 3) * $panelH
        $gold = [Drawing.Color]::FromArgb(203, 157, 81)
        $label = if ($stage -eq 0) { 'BASIC' } else { "UPGRADE $stage" }
        $font = New-Object Drawing.Font 'Arial', 24, ([Drawing.FontStyle]::Bold)
        $brush = New-Object Drawing.SolidBrush $gold
        try { $g.DrawString($label, $font, $brush, ($ox + 32), ($oy + 22)) }
        finally { $font.Dispose(); $brush.Dispose() }

        # Fixed 512x128 authored room, without stretching or repainting.
        Draw-Asset ("castle_room_01_{0}.png" -f $stage) ($ox + 174) ($oy + 355)
        # Exterior frame has a transparent aperture over exactly the room area.
        Draw-Asset ("castle_exterior/castle_01_wall_stage_{0}.png" -f $stage) ($ox + 110) ($oy + 355)
        Draw-Asset ("castle_exterior/castle_01_roof_stage_{0}.png" -f $stage) ($ox + 174) ($oy + 13)
        Draw-Asset ("castle_mobility/castle_01_base_stage_{0}.png" -f $stage) ($ox + 174) ($oy + 483)
        Draw-Asset ("castle_exterior/castle_01_balcony_stage_{0}.png" -f $stage) ($ox + 654) ($oy + 355)

        # The existing wheel files are identical. A concept-only overlay gives
        # the six visible states distinct rims and hubs without changing the
        # runtime resources or obstructing the room's front passage.
        foreach ($cx in @(302, 558)) {
            Draw-Asset 'castle_mobility/castle_01_wheel_stage_0.png' ($ox + $cx - 52) ($oy + 500) 104 104
            if ($stage -gt 0) {
                $rim = if ($stage -lt 3) { [Drawing.Color]::FromArgb(134, 139, 139) }
                       elseif ($stage -lt 5) { [Drawing.Color]::FromArgb(195, 147, 64) }
                       else { [Drawing.Color]::FromArgb(235, 188, 81) }
                $pen = New-Object Drawing.Pen $rim, ([float](1 + $stage * 0.65))
                try { $g.DrawEllipse($pen, ($ox + $cx - 45), ($oy + 507), 90, 90) }
                finally { $pen.Dispose() }
                if ($stage -ge 3) {
                    $hub = New-Object Drawing.SolidBrush $rim
                    try { $g.FillEllipse($hub, ($ox + $cx - 9), ($oy + 543), 18, 18) }
                    finally { $hub.Dispose() }
                }
            }
        }
        $divider = New-Object Drawing.Pen ([Drawing.Color]::FromArgb(82, 105, 110)), 2
        try { $g.DrawRectangle($divider, ($ox + 8), ($oy + 8), ($panelW - 16), ($panelH - 16)) }
        finally { $divider.Dispose() }
    }
} finally { $g.Dispose() }
try { $sheet.Save($out, [Drawing.Imaging.ImageFormat]::Png) }
finally { $sheet.Dispose() }
Write-Host $out
