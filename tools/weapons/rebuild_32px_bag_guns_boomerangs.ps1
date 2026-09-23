param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)
Add-Type -AssemblyName System.Drawing

function Read-GitBytes([string]$relativePath) {
    $psi = [System.Diagnostics.ProcessStartInfo]::new()
    $psi.FileName = 'git.exe'
    $psi.Arguments = "show HEAD:$relativePath"
    $psi.WorkingDirectory = $Root
    $psi.UseShellExecute = $false
    $psi.RedirectStandardOutput = $true
    $process = [System.Diagnostics.Process]::Start($psi)
    $stream = [System.IO.MemoryStream]::new()
    $process.StandardOutput.BaseStream.CopyTo($stream)
    $process.WaitForExit()
    if ($process.ExitCode -ne 0) { throw "Cannot read $relativePath" }
    $process.Dispose()
    $stream.Position = 0
    return $stream
}

function Get-AlphaBounds([System.Drawing.Bitmap]$bitmap) {
    $left = $bitmap.Width; $top = $bitmap.Height; $right = -1; $bottom = -1
    for ($y = 0; $y -lt $bitmap.Height; $y++) {
        for ($x = 0; $x -lt $bitmap.Width; $x++) {
            if ($bitmap.GetPixel($x, $y).A -gt 8) {
                if ($x -lt $left) { $left = $x }
                if ($x -gt $right) { $right = $x }
                if ($y -lt $top) { $top = $y }
                if ($y -gt $bottom) { $bottom = $y }
            }
        }
    }
    if ($right -lt 0) { throw 'Weapon has no visible pixels' }
    return [System.Drawing.Rectangle]::new($left, $top, $right - $left + 1, $bottom - $top + 1)
}

$res = Join-Path $Root 'Resources\res'
$gunHeader = Join-Path $Root 'Classes\Data\DianaGunData.h'
$gunData = [System.IO.File]::ReadAllText($gunHeader, [System.Text.Encoding]::UTF8)
$originalHeaderStream = Read-GitBytes 'Classes/Data/DianaGunData.h'
$originalHeader = [System.Text.Encoding]::UTF8.GetString($originalHeaderStream.ToArray())
$originalHeaderStream.Dispose()

for ($series = 1; $series -le 2; $series++) {
    for ($n = 1; $n -le 35; $n++) {
        $sourceStream = Read-GitBytes "Resources/res/w${series}_${n}.png"
        $source = [System.Drawing.Bitmap]::FromStream($sourceStream)
        $sourceW = $source.Width; $sourceH = $source.Height
        $bounds = Get-AlphaBounds $source
        if ($series -eq 1) {
            $cols = if ($n -le 5 -and $bounds.Width -le $bounds.Height / 2.0) { 1 } else { 2 }
            $rows = if ($n -le 5) { 2 } else { 3 }
        } else {
            $cols = if ($n -le 9) { 3 } else { 4 }
            $rows = $cols
        }
        $canvasW = 32 * $cols; $canvasH = 32 * $rows
        # Original canvases encode tier growth (up to 6x), so fitting each
        # one to its slot erased that growth. Grow visible gun art 64..96 px
        # and boomerang art 96..128 px using the alpha bounds.
        $targetArtH = if ($series -eq 1) {
            64 + 32 * ($n - 1) / 34.0
        } else {
            96 + 32 * ($n - 1) / 34.0
        }
        $factor = [Math]::Min($targetArtH / $bounds.Height, [Math]::Min($canvasW / $bounds.Width, $canvasH / $bounds.Height))
        $drawW = [Math]::Max(1, [int][Math]::Round($bounds.Width * $factor))
        $drawH = [Math]::Max(1, [int][Math]::Round($bounds.Height * $factor))
        $padX = [int][Math]::Floor(($canvasW - $drawW) / 2)
        $padY = [int][Math]::Floor(($canvasH - $drawH) / 2)
        $dest = [System.Drawing.Bitmap]::new($canvasW, $canvasH, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $g = [System.Drawing.Graphics]::FromImage($dest)
        $g.Clear([System.Drawing.Color]::Transparent)
        $g.CompositingMode = [System.Drawing.Drawing2D.CompositingMode]::SourceCopy
        $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality
        $g.DrawImage($source, [System.Drawing.Rectangle]::new($padX, $padY, $drawW, $drawH), $bounds, [System.Drawing.GraphicsUnit]::Pixel)
        $g.Dispose(); $source.Dispose(); $sourceStream.Dispose()
        $path = Join-Path $res "w${series}_${n}.png"
        $tmp = "$path.tmp.png"
        $dest.Save($tmp, [System.Drawing.Imaging.ImageFormat]::Png)
        $dest.Dispose()
        Move-Item -LiteralPath $tmp -Destination $path -Force

        if ($series -eq 1) {
            $pattern = '(?m)^    \{\s*\d+,\s*\d+,\s*(\d+),\s*(\d+) \},( // w1_' + $n + '\b[^\r\n]*)'
            $original = [regex]::Match($originalHeader, $pattern)
            if (-not $original.Success) { throw "Missing grip for w1_$n" }
            $gripX = [int][Math]::Round(([int]$original.Groups[1].Value - $bounds.X) * $factor + $padX)
            $gripY = [int][Math]::Round(([int]$original.Groups[2].Value - $bounds.Y) * $factor + $padY)
            $originalComment = $original.Groups[3].Value
            $gunData = [regex]::Replace($gunData, $pattern, {
                param($m)
                "    { $canvasW, $canvasH, $gripX, $gripY },$originalComment"
            })
        }
        Write-Host "w${series}_${n}: ${sourceW}x${sourceH} -> ${canvasW}x${canvasH}"
    }
}
[System.IO.File]::WriteAllText($gunHeader, $gunData, [System.Text.UTF8Encoding]::new($false))
