Add-Type -AssemblyName System.Drawing

$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$sourcePath = Join-Path $root 'tools/castles/source_shells/castle_01_full.png'
$outDir = Join-Path $root 'Resources/res/castle_mobility'
$source = [Drawing.Bitmap]::FromFile($sourcePath)
try {
    # The left wheel is seen face-on. Keep the outer iron rim and spokes,
    # while masking out the wagon body immediately behind the circular edge.
    $wheel = New-Object Drawing.Bitmap 128, 128, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g = [Drawing.Graphics]::FromImage($wheel)
    try {
        $g.Clear([Drawing.Color]::Transparent)
        $g.SmoothingMode = [Drawing.Drawing2D.SmoothingMode]::AntiAlias
        $g.InterpolationMode = [Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $clip = New-Object Drawing.Drawing2D.GraphicsPath
        try {
            $clip.AddEllipse((New-Object Drawing.Rectangle 2, 2, 124, 124))
            $g.SetClip($clip)
            $g.DrawImage($source, (New-Object Drawing.Rectangle 2, 2, 124, 124),
                260, 657, 216, 228, [Drawing.GraphicsUnit]::Pixel)
        } finally { $clip.Dispose() }
    } finally { $g.Dispose() }
    try {
        for ($stage = 0; $stage -lt 6; ++$stage) {
            $wheel.Save((Join-Path $outDir ('castle_01_wheel_stage_{0}.png' -f $stage)),
                [Drawing.Imaging.ImageFormat]::Png)
        }
    } finally { $wheel.Dispose() }
} finally { $source.Dispose() }

foreach ($stage in 0..5) {
    $path = Join-Path $outDir ('castle_01_wheel_stage_{0}.png' -f $stage)
    $img = [Drawing.Bitmap]::FromFile($path)
    try {
        if ($img.Width -ne 128 -or $img.Height -ne 128) { throw "Bad wheel size: $path" }
        if ($img.GetPixel(64, 64).A -eq 0) { throw "Empty wheel hub: $path" }
        if ($img.GetPixel(0, 0).A -ne 0) { throw "Wheel corner not transparent: $path" }
    } finally { $img.Dispose() }
}
Write-Host 'Replaced six castle 1 wheel resources from the matching timber wagon artwork.'
