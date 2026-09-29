param(
    [string]$Castle7Sheet = "C:\Users\polyp\.codex\generated_images\01a0de43-6120-72f2-9314-8e5fb074b287\exec-e1805dc5-f49b-40fa-9991-76b1ab04a9d9.png",
    [string]$Castle8Sheet = "C:\Users\polyp\.codex\generated_images\01a0de43-6120-72f2-9314-8e5fb074b287\exec-71d7c8c3-270e-4175-8f09-82332d7207af.png",
    [string]$Castle10Sheet = "C:\Users\polyp\.codex\generated_images\01a0de43-6120-72f2-9314-8e5fb074b287\exec-83f08647-465f-4f08-8075-b7c2ea4adc33.png"
)

Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;

public static class FlightbaseBuilder {
    static Rectangle AlphaBounds(Bitmap src, Rectangle cell) {
        int minX=cell.Right, minY=cell.Bottom, maxX=cell.Left, maxY=cell.Top;
        for(int y=cell.Top;y<cell.Bottom;y++) for(int x=cell.Left;x<cell.Right;x++) {
            if(src.GetPixel(x,y).A < 8) continue;
            if(x<minX) minX=x; if(x>maxX) maxX=x;
            if(y<minY) minY=y; if(y>maxY) maxY=y;
        }
        return maxX<minX ? cell : Rectangle.FromLTRB(minX,minY,maxX+1,maxY+1);
    }
    static Color Theme(Color c, int castle) {
        if(c.A==0 || castle<9) return c;
        if(castle==9) {
            int lum=(c.R+c.G+c.B)/3;
            return Color.FromArgb(c.A, Math.Min(255,(int)(c.R*.50+c.B*.72)), Math.Min(255,(int)(c.G*.28)), Math.Min(255,(int)(c.B*.76+lum*.55)));
        }
        return Color.FromArgb(c.A, Math.Min(255,(int)(c.R*1.12+c.G*.20)), Math.Min(255,(int)(c.G*1.04+c.B*.08)), Math.Min(255,(int)(c.B*1.12)));
    }
    public static void Build(string sheetPath, string outputDir, int castle) {
        using(var src=new Bitmap(sheetPath)) {
            int cellW=src.Width/6;
            for(int stage=0;stage<6;stage++) {
                var cell=new Rectangle(stage*cellW,0,stage==5?src.Width-stage*cellW:cellW,src.Height);
                var bounds=AlphaBounds(src,cell);
                using(var dst=new Bitmap(512,128,PixelFormat.Format32bppArgb)) {
                    using(var g=Graphics.FromImage(dst)) {
                        g.Clear(Color.Transparent);
                        g.CompositingMode=CompositingMode.SourceCopy;
                        g.InterpolationMode=InterpolationMode.HighQualityBicubic;
                        g.PixelOffsetMode=PixelOffsetMode.HighQuality;
                        // Fill the authored 4:1 slot.  One transparent pixel at the
                        // top is deliberately removed so the room and hull share a seam.
                        g.DrawImage(src,new Rectangle(0,0,512,128),bounds,GraphicsUnit.Pixel);
                    }
                    if(castle>=9) for(int y=0;y<128;y++) for(int x=0;x<512;x++) dst.SetPixel(x,y,Theme(dst.GetPixel(x,y),castle));
                    dst.Save(System.IO.Path.Combine(outputDir,String.Format("castle_{0:00}_flightbase_stage_{1}.png",castle,stage)),ImageFormat.Png);
                }
            }
        }
    }
}
'@

$out = Join-Path $PSScriptRoot "..\..\Resources\res\castle_mobility"
[FlightbaseBuilder]::Build($Castle7Sheet, $out, 7)
[FlightbaseBuilder]::Build($Castle8Sheet, $out, 8)
[FlightbaseBuilder]::Build($Castle7Sheet, $out, 9)
[FlightbaseBuilder]::Build($Castle10Sheet, $out, 10)
