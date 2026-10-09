$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$outDir = Join-Path $root 'Resources/res/castle_mobility'
foreach ($castle in 7..10) {
    $number = '{0:D2}' -f $castle
    $sheetPath = Join-Path $PSScriptRoot "concepts/castle_${number}_wheel_sheet.png"
    $sheet = [Drawing.Bitmap]::FromFile($sheetPath)
    try {
        if ($sheet.Width -ne 2172 -or $sheet.Height -ne 724) {
            throw "Unexpected wheel sheet size: $sheetPath"
        }
        foreach ($stage in 0..5) {
            $wheel = New-Object Drawing.Bitmap 128,128,([Drawing.Imaging.PixelFormat]::Format32bppArgb)
            try {
                $g = [Drawing.Graphics]::FromImage($wheel)
                try {
                    $g.Clear([Drawing.Color]::Transparent)
                    $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
                    $g.PixelOffsetMode = [Drawing.Drawing2D.PixelOffsetMode]::HighQuality
                    # The authored wheels touch the edge of each sheet cell.
                    # Leave room inside the 128px runtime texture for the
                    # outer rim and for rotation at every angle.
                    $dest = New-Object Drawing.Rectangle 10,10,108,108
                    $source = New-Object Drawing.Rectangle ($stage * 362),181,362,362
                    $g.DrawImage($sheet,$dest,$source,[Drawing.GraphicsUnit]::Pixel)
                } finally { $g.Dispose() }
                $path = Join-Path $outDir "castle_${number}_wheel_stage_${stage}.png"
                $wheel.Save($path,[Drawing.Imaging.ImageFormat]::Png)
            } finally { $wheel.Dispose() }
        }
    } finally { $sheet.Dispose() }
}
Write-Host 'Built 24 themed 128x128 wheel sprites for castles 7-10.'
