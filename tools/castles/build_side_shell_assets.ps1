Add-Type -AssemblyName System.Drawing

$assetDir = Join-Path $PSScriptRoot '..\..\Resources\res\castle_exterior'
$files = Get-ChildItem -LiteralPath $assetDir -Filter 'castle_??_wall_stage_?.png'

foreach ($file in $files) {
    $source = [System.Drawing.Bitmap]::FromFile($file.FullName)
    try {
        if ($source.Width -eq 640 -and $source.Height -eq 128) {
            continue
        }
        if ($source.Width -ne 512 -or $source.Height -ne 128) {
            throw "Unexpected wall size $($source.Width)x$($source.Height): $($file.Name)"
        }

        $output = New-Object System.Drawing.Bitmap 640, 128, ([System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
        try {
            $graphics = [System.Drawing.Graphics]::FromImage($output)
            try {
                $graphics.Clear([System.Drawing.Color]::Transparent)
                $graphics.CompositingMode = [System.Drawing.Drawing2D.CompositingMode]::SourceCopy
                $graphics.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor

                # Keep only straight, fixed-width side columns.  The authored
                # room aperture x=64..575 remains completely transparent.
                $leftDst = New-Object System.Drawing.Rectangle 0, 0, 64, 128
                $leftSrc = New-Object System.Drawing.Rectangle 0, 0, 64, 128
                $rightDst = New-Object System.Drawing.Rectangle 576, 0, 64, 128
                $rightSrc = New-Object System.Drawing.Rectangle 448, 0, 64, 128
                $graphics.DrawImage($source, $leftDst, $leftSrc, [System.Drawing.GraphicsUnit]::Pixel)
                $graphics.DrawImage($source, $rightDst, $rightSrc, [System.Drawing.GraphicsUnit]::Pixel)
            }
            finally {
                $graphics.Dispose()
            }

            $tempPath = "$($file.FullName).tmp.png"
            $output.Save($tempPath, [System.Drawing.Imaging.ImageFormat]::Png)
        }
        finally {
            $output.Dispose()
        }
    }
    finally {
        $source.Dispose()
    }

    Move-Item -LiteralPath $tempPath -Destination $file.FullName -Force
}

Write-Host "Converted $($files.Count) wall assets to 640x128 side shells."
