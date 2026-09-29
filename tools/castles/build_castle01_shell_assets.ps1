param(
 [string]$WallSheet="C:\Users\polyp\.codex\generated_images\01a0de43-6120-72f2-9314-8e5fb074b287\exec-0af0faf6-0b2d-4958-90a4-adbcd3a14787.png",
 [string]$RoofSheet="C:\Users\polyp\.codex\generated_images\01a0de43-6120-72f2-9314-8e5fb074b287\exec-500bef63-4d4e-4df8-9453-6f6760d5d0ee.png"
)
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
public static class CastleShellBuilder {
 static Rectangle Bounds(Bitmap b,Rectangle c){int x0=c.Right,y0=c.Bottom,x1=c.Left,y1=c.Top;for(int y=c.Top;y<c.Bottom;y++)for(int x=c.Left;x<c.Right;x++){if(b.GetPixel(x,y).A<8)continue;if(x<x0)x0=x;if(x>x1)x1=x;if(y<y0)y0=y;if(y>y1)y1=y;}return Rectangle.FromLTRB(x0,y0,x1+1,y1+1);}
 public static void Build(string sheet,string output,string stem,int outW,int outH){using(var src=new Bitmap(sheet)){int cw=src.Width/3,ch=src.Height/2;for(int i=0;i<6;i++){int col=i%3,row=i/3;var cell=new Rectangle(col*cw,row*ch,col==2?src.Width-col*cw:cw,row==1?src.Height-row*ch:ch);var crop=Bounds(src,cell);using(var dst=new Bitmap(outW,outH,PixelFormat.Format32bppArgb))using(var g=Graphics.FromImage(dst)){g.Clear(Color.Transparent);g.CompositingMode=CompositingMode.SourceCopy;g.InterpolationMode=InterpolationMode.HighQualityBicubic;g.PixelOffsetMode=PixelOffsetMode.HighQuality;g.DrawImage(src,new Rectangle(0,0,outW,outH),crop,GraphicsUnit.Pixel);dst.Save(System.IO.Path.Combine(output,string.Format(stem,i)),ImageFormat.Png);}}}}
}
'@
$out=Join-Path $PSScriptRoot "..\..\Resources\res\castle_exterior"
New-Item -ItemType Directory -Force -Path $out|Out-Null
[CastleShellBuilder]::Build($WallSheet,$out,"castle_01_wall_stage_{0}.png",512,128)
[CastleShellBuilder]::Build($RoofSheet,$out,"castle_01_roof_stage_{0}.png",512,192)
