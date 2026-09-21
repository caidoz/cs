param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path
)

Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies 'System.Drawing.dll' -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;

public static class DianaGunImageProcessor
{
    public static Rectangle AlphaBounds(Bitmap bitmap, Rectangle area)
    {
        int left = area.Right, top = area.Bottom, right = area.Left - 1, bottom = area.Top - 1;
        for (int y = area.Top; y < area.Bottom; ++y)
        for (int x = area.Left; x < area.Right; ++x)
        {
            if (bitmap.GetPixel(x, y).A <= 12) continue;
            if (x < left) left = x;
            if (x > right) right = x;
            if (y < top) top = y;
            if (y > bottom) bottom = y;
        }
        if (right < left || bottom < top) throw new InvalidOperationException("No visible pixels in source image.");
        return Rectangle.FromLTRB(left, top, right + 1, bottom + 1);
    }

    public static void Fit(string sourcePath, string destinationPath, int width, int height, bool useRightHalf)
    {
        using (var source = new Bitmap(sourcePath))
        {
            var search = useRightHalf
                ? new Rectangle(source.Width / 2, 0, source.Width - source.Width / 2, source.Height)
                : new Rectangle(0, 0, source.Width, source.Height);
            var bounds = AlphaBounds(source, search);
            int margin = Math.Max(1, (int)Math.Round(Math.Min(width, height) * 0.035));
            float scale = Math.Min((width - margin * 2f) / bounds.Width, (height - margin * 2f) / bounds.Height);
            int drawWidth = Math.Max(1, (int)Math.Round(bounds.Width * scale));
            int drawHeight = Math.Max(1, (int)Math.Round(bounds.Height * scale));
            int drawX = (width - drawWidth) / 2;
            int drawY = (height - drawHeight) / 2;

            using (var output = new Bitmap(width, height, PixelFormat.Format32bppArgb))
            using (var graphics = Graphics.FromImage(output))
            {
                graphics.Clear(Color.Transparent);
                graphics.CompositingMode = CompositingMode.SourceCopy;
                graphics.CompositingQuality = CompositingQuality.HighSpeed;
                graphics.InterpolationMode = InterpolationMode.NearestNeighbor;
                graphics.PixelOffsetMode = PixelOffsetMode.Half;
                graphics.SmoothingMode = SmoothingMode.None;
                graphics.DrawImage(source,
                    new Rectangle(drawX, drawY, drawWidth, drawHeight),
                    bounds, GraphicsUnit.Pixel);
                output.Save(destinationPath, ImageFormat.Png);
            }
        }
    }

    public static void RotateClockwise(string path)
    {
        using (var source = new Bitmap(path))
        {
            source.RotateFlip(RotateFlipType.Rotate90FlipNone);
            source.Save(path + ".rotated.png", ImageFormat.Png);
        }
        System.IO.File.Delete(path);
        System.IO.File.Move(path + ".rotated.png", path);
    }
}
'@

$resourceDir = Join-Path $ProjectRoot 'Resources\res'
$workDir = Join-Path $ProjectRoot 'output\diana-guns'
$rawDir = Join-Path $workDir 'raw'
$originalDir = Join-Path $workDir 'originals'
New-Item -ItemType Directory -Force -Path $originalDir | Out-Null

1..8 | ForEach-Object {
    $backup = Join-Path $originalDir "old_w1_$_.png"
    if (!(Test-Path -LiteralPath $backup)) {
        Copy-Item -LiteralPath (Join-Path $resourceDir "w1_$_.png") -Destination $backup
    }
}

$anchorOldIndex = @{ 1=1; 4=2; 7=3; 10=4; 13=5; 16=6; 19=7; 22=8 }
$swordHeights = @(64,64,64,64,64,96,128,128,128,128,160,160,160,160,160,192,224,224,256,256,288,288,224,224,288,320,320,320,352,352,352,384,384,384,384)
$runningHeight = 64
$records = @()

for ($number = 1; $number -le 35; ++$number) {
    $runningHeight = [Math]::Max($runningHeight, $swordHeights[$number - 1])
    $scale = $runningHeight / 64.0
    $width = [int][Math]::Round(64 * $scale)
    $height = [int][Math]::Round(28 * $scale)

    if ($anchorOldIndex.ContainsKey($number)) {
        $oldNumber = $anchorOldIndex[$number]
        $source = Join-Path $originalDir "old_w1_$oldNumber.png"
        $rightHalf = $true
    } else {
        $source = Join-Path $rawDir "w1_$number.png"
        $rightHalf = $false
    }
    if (!(Test-Path -LiteralPath $source)) { throw "Missing source for w1_${number}: $source" }

    $destination = Join-Path $resourceDir "w1_$number.png"
    [DianaGunImageProcessor]::Fit($source, $destination, $width, $height, $rightHalf)
    [DianaGunImageProcessor]::RotateClockwise($destination)

    $horizontalGripX = [int][Math]::Round($width * 0.82)
    $horizontalGripY = [int][Math]::Round($height * 0.72)
    $gripX = $height - 1 - $horizontalGripY
    $gripY = $horizontalGripX
    $records += [pscustomobject]@{ Number=$number; Width=$height; Height=$width; GripX=$gripX; GripY=$gripY }
}

$records | Export-Csv -NoTypeInformation -Encoding UTF8 (Join-Path $workDir 'gun_dimensions.csv')
$records | Format-Table -AutoSize
