param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

Add-Type -AssemblyName System.Drawing
$source = Join-Path $Root 'content\equipment\pixel_art\originals'
$base = Join-Path $Root 'content\equipment\pixel_art'
$armor = @{ diana='vest'; maxx='coat' }

foreach ($hero in @('diana','maxx')) {
    $output = Join-Path $base $hero
    New-Item -ItemType Directory -Path $output -Force | Out-Null
    foreach ($kind in @('helm','armor','pants','boots','glove')) {
        $sheet = [System.Drawing.Bitmap]::new(1024, 128, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [System.Drawing.Graphics]::FromImage($sheet)
        $g.Clear([System.Drawing.Color]::Transparent)
        $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
        $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
        try {
            for ($i=0; $i -lt 8; $i++) {
                $relative = if ($kind -eq 'helm') { "inventory_helm\${hero}_$($i+1).png" }
                            elseif ($kind -eq 'armor') { "item_$($armor[$hero])_${hero}$i.png" }
                            else { "item_${kind}_${hero}$i.png" }
                $item=[System.Drawing.Bitmap]::FromFile((Join-Path $source $relative))
                try { $g.DrawImage($item,[System.Drawing.Rectangle]::new($i*128,0,128,128)) }
                finally { $item.Dispose() }
            }
        } finally { $g.Dispose() }
        try { $sheet.Save((Join-Path $output "$kind-reference.png"),[System.Drawing.Imaging.ImageFormat]::Png) }
        finally { $sheet.Dispose() }
    }
}
