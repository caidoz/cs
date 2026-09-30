Add-Type -AssemblyName System.Drawing
$res = Join-Path $PSScriptRoot '..\..\Resources\res'
foreach ($castle in @(1,3,10)) {
    $stage = if ($castle -eq 10) { 5 } else { 0 }
    $width = 736
    $height = 342 + 128*$castle + 172
    $preview = New-Object Drawing.Bitmap $width,$height,([Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g = [Drawing.Graphics]::FromImage($preview)
    try {
        $g.Clear([Drawing.Color]::FromArgb(25,42,47))
        $roofPath = Join-Path $res ('castle_exterior\castle_{0:d2}_roof_stage_{1}.png' -f $castle,$stage)
        $roof = [Drawing.Bitmap]::FromFile($roofPath)
        try { $g.DrawImageUnscaled($roof,64,0) } finally { $roof.Dispose() }
        for ($floor=1; $floor -le $castle; ++$floor) {
            $floorStage = if ($floor -eq $castle) { $stage } else { 5 }
            $roomPath = Join-Path $res ('castle_room_{0:d2}_{1}.png' -f $floor,$floorStage)
            $wallPath = Join-Path $res ('castle_exterior\castle_{0:d2}_wall_stage_{1}.png' -f $castle,$floorStage)
            $room = [Drawing.Bitmap]::FromFile($roomPath)
            $wall = [Drawing.Bitmap]::FromFile($wallPath)
            try {
                $y = 342 + ($castle-$floor)*128
                $g.DrawImageUnscaled($room,64,$y)
                $g.DrawImageUnscaled($wall,0,$y)
            } finally { $room.Dispose(); $wall.Dispose() }
        }
        $balcony = [Drawing.Bitmap]::FromFile((Join-Path $res ('castle_exterior\castle_{0:d2}_balcony_stage_{1}.png' -f $castle,$stage)))
        try { $g.DrawImageUnscaled($balcony,544,342+($castle-1)*128) } finally { $balcony.Dispose() }
        $baseName = if ($castle -ge 7) { 'castle_{0:d2}_flightbase_stage_{1}.png' -f $castle,$stage } else { 'castle_{0:d2}_base_stage_{1}.png' -f $castle,$stage }
        $base = [Drawing.Bitmap]::FromFile((Join-Path $res "castle_mobility\$baseName"))
        try { $g.DrawImageUnscaled($base,64,342+$castle*128) } finally { $base.Dispose() }
    } finally { $g.Dispose() }
    $path = Join-Path $PSScriptRoot ('preview_final_castle_{0:d2}.png' -f $castle)
    try { $preview.Save($path,[Drawing.Imaging.ImageFormat]::Png) } finally { $preview.Dispose() }
    Write-Host $path
}
