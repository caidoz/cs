param(
    [string]$Sheet = "C:\Users\polyp\.codex\generated_images\01a0de43-6120-72f2-9314-8e5fb074b287\exec-b94ea089-c3b0-484f-8738-3129e1119847.png"
)

Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;

public static class BalconyBuilder {
    static Rectangle Bounds(Bitmap src, Rectangle cell) {
        int minX=cell.Right,minY=cell.Bottom,maxX=cell.Left,maxY=cell.Top;
        for(int y=cell.Top;y<cell.Bottom;y++) for(int x=cell.Left;x<cell.Right;x++) {
            if(src.GetPixel(x,y).A<8) continue;
            if(x<minX)minX=x;if(x>maxX)maxX=x;if(y<minY)minY=y;if(y>maxY)maxY=y;
        }
        return Rectangle.FromLTRB(minX,minY,maxX+1,maxY+1);
    }
    public static void Build(string sheet,string output) {
        using(var src=new Bitmap(sheet)) {
            int cellW=src.Width/6;
            for(int i=0;i<6;i++) {
                var cell=new Rectangle(i*cellW,0,i==5?src.Width-i*cellW:cellW,src.Height);
                var crop=Bounds(src,cell);
                using(var dst=new Bitmap(192,128,PixelFormat.Format32bppArgb))
                using(var g=Graphics.FromImage(dst)) {
                    g.Clear(Color.Transparent);
                    g.CompositingMode=CompositingMode.SourceCopy;
                    g.InterpolationMode=InterpolationMode.HighQualityBicubic;
                    g.PixelOffsetMode=PixelOffsetMode.HighQuality;
                    g.DrawImage(src,new Rectangle(0,0,192,128),crop,GraphicsUnit.Pixel);
                    dst.Save(System.IO.Path.Combine(output,string.Format("castle_01_balcony_stage_{0}.png",i)),ImageFormat.Png);
                }
            }
        }
    }
}
'@

$out = Join-Path $PSScriptRoot "..\..\Resources\res\castle_exterior"
New-Item -ItemType Directory -Force -Path $out | Out-Null
[BalconyBuilder]::Build($Sheet,$out)
