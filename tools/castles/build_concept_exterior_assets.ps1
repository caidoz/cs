Add-Type -AssemblyName System.Drawing

$atlasDir = Join-Path $PSScriptRoot 'source_atlases'
$outDir = Join-Path $PSScriptRoot '..\..\Resources\res\castle_exterior'

Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;

public static class ConceptExteriorAtlas {
    static Rectangle AlphaBounds(Bitmap source, Rectangle area) {
        int x0 = area.Right, y0 = area.Bottom, x1 = area.Left - 1, y1 = area.Top - 1;
        for (int y = area.Top; y < area.Bottom; ++y)
            for (int x = area.Left; x < area.Right; ++x)
                if (source.GetPixel(x, y).A > 8) {
                    x0 = Math.Min(x0, x); y0 = Math.Min(y0, y);
                    x1 = Math.Max(x1, x); y1 = Math.Max(y1, y);
                }
        return x1 < x0 ? Rectangle.Empty : Rectangle.FromLTRB(x0, y0, x1 + 1, y1 + 1);
    }

    static void DrawScaled(Graphics g, Bitmap source, Rectangle sourceRect, Rectangle destination) {
        g.DrawImage(source, destination, sourceRect, GraphicsUnit.Pixel);
    }

    public static void Build(string atlasPath, string outputDir, int castle) {
        using (var source = new Bitmap(atlasPath)) {
            float cellW = source.Width / 6.0f;
            float cellH = source.Height / 2.0f;
            for (int stage = 0; stage < 6; ++stage) {
                int x0 = (int)Math.Round(stage * cellW);
                int x1 = (int)Math.Round((stage + 1) * cellW);
                int split = (x0 + x1) / 2;
                int rowSplit = (int)Math.Round(cellH);

                Rectangle leftArea = Rectangle.FromLTRB(x0, 0, split, rowSplit);
                Rectangle rightArea = Rectangle.FromLTRB(split, 0, x1, rowSplit);
                Rectangle left = AlphaBounds(source, leftArea);
                Rectangle right = AlphaBounds(source, rightArea);
                if (left.IsEmpty || right.IsEmpty)
                    throw new InvalidDataException("Missing side armor in " + atlasPath + " stage " + stage);

                // Use the straight middle body.  Spires and foot projections belong
                // to the crown/base; repeating them at every floor makes a saw edge.
                left.Y += (int)(left.Height * 0.22f); left.Height = (int)(left.Height * 0.70f);
                right.Y += (int)(right.Height * 0.22f); right.Height = (int)(right.Height * 0.70f);

                string wallPath = Path.Combine(outputDir,
                    String.Format("castle_{0:00}_wall_stage_{1}.png", castle, stage));
                using (var wall = new Bitmap(640, 128, PixelFormat.Format32bppArgb))
                using (var g = Graphics.FromImage(wall)) {
                    g.Clear(Color.Transparent);
                    g.CompositingMode = CompositingMode.SourceCopy;
                    g.InterpolationMode = InterpolationMode.HighQualityBicubic;
                    g.PixelOffsetMode = PixelOffsetMode.HighQuality;
                    // Two authored pixels tuck under the room's own outer frame.
                    // This hides texture-filter seams at arbitrary camera zooms
                    // without covering any usable interior artwork.
                    DrawScaled(g, source, left, new Rectangle(0, 0, 66, 128));
                    DrawScaled(g, source, right, new Rectangle(574, 0, 66, 128));
                    wall.Save(wallPath, ImageFormat.Png);
                }

                Rectangle roofArea = Rectangle.FromLTRB(x0, rowSplit, x1, source.Height);
                Rectangle roofBounds = AlphaBounds(source, roofArea);
                if (roofBounds.IsEmpty)
                    throw new InvalidDataException("Missing crown in " + atlasPath + " stage " + stage);

                string roofPath = Path.Combine(outputDir,
                    String.Format("castle_{0:00}_roof_stage_{1}.png", castle, stage));
                using (var roof = new Bitmap(640, 192, PixelFormat.Format32bppArgb))
                using (var g = Graphics.FromImage(roof)) {
                    g.Clear(Color.Transparent);
                    g.CompositingMode = CompositingMode.SourceCopy;
                    g.InterpolationMode = InterpolationMode.HighQualityBicubic;
                    g.PixelOffsetMode = PixelOffsetMode.HighQuality;
                    // The crown must read as the cap of the 512px room stack.
                    // Every generated silhouette therefore owns exactly that
                    // width instead of shrinking to fit its variable source ratio.
                    DrawScaled(g, source, roofBounds, new Rectangle(64, 4, 512, 188));
                    // Atlas generators occasionally leave a sliver from the
                    // neighboring cell on the exact top boundary.  Real crowns
                    // are padded below it, so clear that boundary deterministically.
                    using (var clear = new SolidBrush(Color.Transparent))
                        g.FillRectangle(clear, 0, 0, 640, 10);
                    roof.Save(roofPath, ImageFormat.Png);
                }
            }
        }
    }
}
'@

for ($castle = 1; $castle -le 10; ++$castle) {
    $atlas = Join-Path $atlasDir ('castle_{0:d2}_exterior_atlas.png' -f $castle)
    if (!(Test-Path -LiteralPath $atlas)) { throw "Missing atlas: $atlas" }
    [ConceptExteriorAtlas]::Build($atlas, $outDir, $castle)
}

Write-Host 'Built 60 side shells (640x128) and 60 crowns (640x192).'
