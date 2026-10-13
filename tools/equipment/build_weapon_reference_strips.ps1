param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

Add-Type -AssemblyName System.Drawing
$source=Join-Path $Root 'content\equipment\pixel_art\originals'
$base=Join-Path $Root 'content\equipment\pixel_art'
foreach($weapon in @('gun','boomerang')) {
    $dir=Join-Path $base "inventory_$weapon"
    New-Item -ItemType Directory -Path $dir -Force | Out-Null
    for($group=0;$group -lt 5;$group++) {
        $sheet=[System.Drawing.Bitmap]::new(896,128,[System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g=[System.Drawing.Graphics]::FromImage($sheet)
        $g.Clear([System.Drawing.Color]::Transparent)
        $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
        try {
            for($i=0;$i -lt 7;$i++) {
                $n=$group*7+$i+1
                $item=[System.Drawing.Bitmap]::FromFile((Join-Path $source "inventory_$weapon\$n.png"))
                try {
                    $x=$i*128+[int][Math]::Floor((128-$item.Width)/2)
                    $y=[int][Math]::Floor((128-$item.Height)/2)
                    $g.DrawImageUnscaled($item,$x,$y)
                } finally {$item.Dispose()}
            }
        } finally {$g.Dispose()}
        try {$sheet.Save((Join-Path $dir "group$group-reference.png"),[System.Drawing.Imaging.ImageFormat]::Png)}
        finally {$sheet.Dispose()}
    }
}
