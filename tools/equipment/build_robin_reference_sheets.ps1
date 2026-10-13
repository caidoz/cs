param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

Add-Type -AssemblyName System.Drawing
$source = Join-Path $Root 'content\equipment\pixel_art\originals'
$output = Join-Path $Root 'content\equipment\pixel_art\robin'
New-Item -ItemType Directory -Path $output -Force | Out-Null

foreach ($kind in @('helm','armor','pants','boots','glove')) {
    $sheet = [System.Drawing.Bitmap]::new(1024, 128, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $graphics = [System.Drawing.Graphics]::FromImage($sheet)
    $graphics.Clear([System.Drawing.Color]::Transparent)
    $graphics.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
    $graphics.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
    try {
        for ($i = 0; $i -lt 8; $i++) {
            $relative = if ($kind -eq 'helm') { "inventory_helm\robin_$($i + 1).png" }
                        else { "item_${kind}_robin$i.png" }
            $image = [System.Drawing.Bitmap]::FromFile((Join-Path $source $relative))
            try {
                $graphics.DrawImage($image, [System.Drawing.Rectangle]::new($i * 128, 0, 128, 128),
                    [System.Drawing.Rectangle]::new(0, 0, $image.Width, $image.Height),
                    [System.Drawing.GraphicsUnit]::Pixel)
            } finally { $image.Dispose() }
        }
    } finally { $graphics.Dispose() }
    try { $sheet.Save((Join-Path $output "$kind-reference.png"), [System.Drawing.Imaging.ImageFormat]::Png) }
    finally { $sheet.Dispose() }
}
