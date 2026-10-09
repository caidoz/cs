$ErrorActionPreference='Stop'
Add-Type -AssemblyName System.Drawing
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$source=Join-Path $root 'tools/castles/concepts'
$output=Join-Path $root 'Resources/res/castle_mobility'
foreach($castle in 1,6) {
    foreach($stage in 0..5) {
        $name=('castle_{0:00}_wheel_stage_{1}.png' -f $castle,$stage)
        $src=[Drawing.Bitmap]::new((Join-Path $source $name))
        $dst=[Drawing.Bitmap]::new(128,128,[Drawing.Imaging.PixelFormat]::Format32bppArgb)
        try {
            $g=[Drawing.Graphics]::FromImage($dst)
            try {
                $g.Clear([Drawing.Color]::Transparent)
                $g.InterpolationMode=[Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
                $g.DrawImage($src,[Drawing.Rectangle]::new(6,6,116,116))
            } finally { $g.Dispose() }
            $dst.Save((Join-Path $output $name),[Drawing.Imaging.ImageFormat]::Png)
        } finally { $src.Dispose();$dst.Dispose() }
    }
}
Write-Host 'Padded castle 1 and 6 wheel sprites.'
