param([string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies 'System.Drawing.dll' -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;

public static class MaxxBoomerangImageProcessor
{
    static Rectangle AlphaBounds(Bitmap bitmap, Rectangle area)
    {
        int l=area.Right, t=area.Bottom, r=area.Left-1, b=area.Top-1;
        for (int y=area.Top; y<area.Bottom; ++y)
        for (int x=area.Left; x<area.Right; ++x) {
            if (bitmap.GetPixel(x,y).A <= 12) continue;
            l=Math.Min(l,x); r=Math.Max(r,x); t=Math.Min(t,y); b=Math.Max(b,y);
        }
        if (r<l || b<t) throw new InvalidOperationException("No visible pixels.");
        return Rectangle.FromLTRB(l,t,r+1,b+1);
    }

    public static void Fit(string sourcePath, string destinationPath, int width, int height,
                           bool useRightHalf, bool rotateClockwise)
    {
        using (var original = new Bitmap(sourcePath))
        using (var source = new Bitmap(original)) {
            Rectangle search = useRightHalf
                ? new Rectangle(source.Width/2, 0, source.Width-source.Width/2, source.Height)
                : new Rectangle(0,0,source.Width,source.Height);
            Rectangle bounds = AlphaBounds(source, search);
            using (var cropped = source.Clone(bounds, PixelFormat.Format32bppArgb)) {
                if (rotateClockwise) cropped.RotateFlip(RotateFlipType.Rotate90FlipNone);
                int margin=Math.Max(1,(int)Math.Round(Math.Min(width,height)*0.035));
                float scale=Math.Min((width-margin*2f)/cropped.Width,(height-margin*2f)/cropped.Height);
                int dw=Math.Max(1,(int)Math.Round(cropped.Width*scale));
                int dh=Math.Max(1,(int)Math.Round(cropped.Height*scale));
                using (var output=new Bitmap(width,height,PixelFormat.Format32bppArgb))
                using (var g=Graphics.FromImage(output)) {
                    g.Clear(Color.Transparent);
                    g.CompositingMode=CompositingMode.SourceCopy;
                    g.InterpolationMode=InterpolationMode.NearestNeighbor;
                    g.PixelOffsetMode=PixelOffsetMode.Half;
                    g.SmoothingMode=SmoothingMode.None;
                    g.DrawImage(cropped,new Rectangle((width-dw)/2,(height-dh)/2,dw,dh),
                        new Rectangle(0,0,cropped.Width,cropped.Height),GraphicsUnit.Pixel);
                    output.Save(destinationPath,ImageFormat.Png);
                }
            }
        }
    }
}
'@

$resourceDir=Join-Path $ProjectRoot 'Resources\res'
$workDir=Join-Path $ProjectRoot 'output\maxx-boomerangs'
$rawDir=Join-Path $workDir 'raw'
$originalDir=Join-Path $workDir 'originals'
New-Item -ItemType Directory -Force -Path $originalDir | Out-Null

1..8 | ForEach-Object {
    $backup=Join-Path $originalDir "old_w2_$_.png"
    if (!(Test-Path -LiteralPath $backup)) {
        Copy-Item -LiteralPath (Join-Path $resourceDir "w2_$_.png") -Destination $backup
    }
}

$anchorOldIndex=@{1=1;4=2;7=3;10=4;13=5;16=6;19=7;22=8}
$swordHeights=@(64,64,64,64,64,96,128,128,128,128,160,160,160,160,160,192,224,224,256,256,288,288,224,224,288,320,320,320,352,352,352,384,384,384,384)
$runningHeight=64
$records=@()

for($number=1;$number -le 35;++$number) {
    $runningHeight=[Math]::Max($runningHeight,$swordHeights[$number-1])
    $scale=$runningHeight/64.0
    $width=[int][Math]::Round(70*$scale)
    $height=[int][Math]::Round(78*$scale)
    if($anchorOldIndex.ContainsKey($number)) {
        $source=Join-Path $originalDir "old_w2_$($anchorOldIndex[$number]).png"
        $rightHalf=$true
        $rotate=$true
    } else {
        $source=Join-Path $rawDir "w2_$number.png"
        $rightHalf=$false
        $rotate=$false
    }
    if(!(Test-Path -LiteralPath $source)){throw ("Missing source for w2_" + $number + ": " + $source)}
    $destination=Join-Path $resourceDir "w2_$number.png"
    [MaxxBoomerangImageProcessor]::Fit($source,$destination,$width,$height,$rightHalf,$rotate)
    $records += [pscustomobject]@{Number=$number;Width=$width;Height=$height}
}

$records | Export-Csv -NoTypeInformation -Encoding UTF8 (Join-Path $workDir 'boomerang_dimensions.csv')
$records | Format-Table -AutoSize
