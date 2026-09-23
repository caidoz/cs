param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)
Add-Type -AssemblyName System.Drawing
$header = Join-Path $Root 'Classes\Data\SwordSprites.h'
$text = [System.IO.File]::ReadAllText($header, [System.Text.Encoding]::UTF8)
$res = Join-Path $Root 'Resources\res'
$headerProcess = [System.Diagnostics.ProcessStartInfo]::new()
$headerProcess.FileName = 'git.exe'
$headerProcess.Arguments = 'show HEAD:Classes/Data/SwordSprites.h'
$headerProcess.WorkingDirectory = $Root
$headerProcess.UseShellExecute = $false
$headerProcess.RedirectStandardOutput = $true
$headerReader = [System.Diagnostics.Process]::Start($headerProcess)
$originalHeader = $headerReader.StandardOutput.ReadToEnd()
$headerReader.WaitForExit()
if ($headerReader.ExitCode -ne 0) { throw 'Cannot read original SwordSprites.h' }
$headerReader.Dispose()

for ($n = 1; $n -le 35; $n++) {
    # Read committed full-resolution art, not the already reduced working PNG.
    $psi = [System.Diagnostics.ProcessStartInfo]::new()
    $psi.FileName = 'git.exe'
    $psi.Arguments = "show HEAD:Resources/res/w0_$n.png"
    $psi.WorkingDirectory = $Root
    $psi.UseShellExecute = $false
    $psi.RedirectStandardOutput = $true
    $process = [System.Diagnostics.Process]::Start($psi)
    $stream = [System.IO.MemoryStream]::new()
    $process.StandardOutput.BaseStream.CopyTo($stream)
    $process.WaitForExit()
    if ($process.ExitCode -ne 0) { throw "Cannot read original w0_$n.png" }
    $process.Dispose()
    $stream.Position = 0
    $source = [System.Drawing.Bitmap]::FromStream($stream)
    $oldW = $source.Width; $oldH = $source.Height
    $path = Join-Path $res "w0_$n.png"
    $targetH = if ($n -le 5) { 64 } else { [int][Math]::Round(64 + 64 * ($n - 1) / 34.0) }
    $factor = [Math]::Min(1.0, [Math]::Min($targetH / $oldH, 64.0 / $oldW))
    $drawW = [Math]::Max(1, [int][Math]::Round($oldW * $factor))
    $drawH = [Math]::Max(1, [int][Math]::Round($oldH * $factor))
    $cols = [Math]::Max([int][Math]::Ceiling($drawW / 32.0), $(if ($n -ge 18) { 2 } else { 1 }))
    $rows = [int][Math]::Ceiling($drawH / 32.0)
    $canvasW = $cols * 32; $canvasH = $rows * 32
    $padX = [int][Math]::Floor(($canvasW - $drawW) / 2)
    $padY = [int][Math]::Floor(($canvasH - $drawH) / 2)
    $dest = [System.Drawing.Bitmap]::new($canvasW, $canvasH, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g = [System.Drawing.Graphics]::FromImage($dest)
    $g.Clear([System.Drawing.Color]::Transparent)
    $g.CompositingMode = [System.Drawing.Drawing2D.CompositingMode]::SourceCopy
    $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
    $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality
    $g.DrawImage($source, [System.Drawing.Rectangle]::new($padX, $padY, $drawW, $drawH), [System.Drawing.Rectangle]::new(0, 0, $oldW, $oldH), [System.Drawing.GraphicsUnit]::Pixel)
    $g.Dispose(); $source.Dispose(); $stream.Dispose()
    $tmp = "$path.tmp.png"
    $dest.Save($tmp, [System.Drawing.Imaging.ImageFormat]::Png)
    $dest.Dispose()
    Move-Item -LiteralPath $tmp -Destination $path -Force

    $pattern = '(?m)^    \{swordTileSize\[(\d+)\], swordTileSize\[\d+\], \d+, \d+, ([\d.]+)f, ([\d.]+)f\}, // w0_' + $n + '(?=\r?$)'
    $originalMatch = [regex]::Match($originalHeader, $pattern)
    if (-not $originalMatch.Success) { throw "Missing source pivot for w0_$n" }
    $sourcePivotX = [double]::Parse($originalMatch.Groups[2].Value, [cultureinfo]::InvariantCulture)
    $sourcePivotY = [double]::Parse($originalMatch.Groups[3].Value, [cultureinfo]::InvariantCulture)
    $text = [regex]::Replace($text, $pattern, {
        param($m)
        $x = ($sourcePivotX * $drawW / $oldW + $padX).ToString('0.0', [cultureinfo]::InvariantCulture)
        $y = ($sourcePivotY * $drawH / $oldH + $padY).ToString('0.0', [cultureinfo]::InvariantCulture)
        "    {swordTileSize[$($m.Groups[1].Value)], swordTileSize[$([int]$m.Groups[1].Value + 1)], $canvasW, $canvasH, ${x}f, ${y}f}, // w0_$n"
    })
    $tilePattern = '(?m)^    \d+, \d+, //w0_' + $n + '(?=\r?$)'
    $text = [regex]::Replace($text, $tilePattern, "    $cols, $rows, //w0_$n")
    Write-Host "w0_$n $oldW x $oldH -> $canvasW x $canvasH ($drawW x $drawH art)"
}
[System.IO.File]::WriteAllText($header, $text, [System.Text.UTF8Encoding]::new($false))
