$root="C:\Users\polyp\.codex\generated_images\01a0de43-6120-72f2-9314-8e5fb074b287"
$sheets=@{
 3='exec-24bfc08c-dfc3-47b7-9c6a-4d6f936ed93c.png';4='exec-0c70b95c-a3c3-4214-87c5-85279d4e1d03.png';5='exec-b2943954-ed60-4348-8127-33f6df8e15c5.png';6='exec-082fb0a2-f8fe-4fd3-a71f-9920808fbed5.png';7='exec-7f5f5a46-3586-4269-82ce-1515f54cc91c.png';8='exec-d01f6ce2-b0f9-41ef-a626-197bc2a5881f.png';9='exec-bced5326-0016-40ae-9314-b37caae91fda.png';10='exec-9519a4c0-b765-43ca-b5ea-9c3ebfd97ebf.png'
}
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System.Drawing; using System.Drawing.Drawing2D; using System.Drawing.Imaging;
public static class ExteriorBatch {
 static Rectangle B(Bitmap b,Rectangle c){int x0=c.Right,y0=c.Bottom,x1=c.Left,y1=c.Top;for(int y=c.Top;y<c.Bottom;y++)for(int x=c.Left;x<c.Right;x++){if(b.GetPixel(x,y).A<8)continue;if(x<x0)x0=x;if(y<y0)y0=y;if(x>x1)x1=x;if(y>y1)y1=y;}return Rectangle.FromLTRB(x0,y0,x1+1,y1+1);}
 static void Save(Bitmap s,Rectangle cell,string path,int w,int h){var q=B(s,cell);using(var d=new Bitmap(w,h,PixelFormat.Format32bppArgb))using(var g=Graphics.FromImage(d)){g.Clear(Color.Transparent);g.CompositingMode=CompositingMode.SourceCopy;g.InterpolationMode=InterpolationMode.HighQualityBicubic;g.PixelOffsetMode=PixelOffsetMode.HighQuality;g.DrawImage(s,new Rectangle(0,0,w,h),q,GraphicsUnit.Pixel);d.Save(path,ImageFormat.Png);}}
 public static void Grid(string path,string output,int castle){using(var s=new Bitmap(path)){int cw=s.Width/6,ch=s.Height/3;string[] part={"wall","balcony","roof"};int[] w={512,192,512},h={128,128,192};for(int row=0;row<3;row++)for(int i=0;i<6;i++){var c=new Rectangle(i*cw,row*ch,i==5?s.Width-i*cw:cw,row==2?s.Height-row*ch:ch);Save(s,c,System.IO.Path.Combine(output,string.Format("castle_{0:00}_{1}_stage_{2}.png",castle,part[row],i)),w[row],h[row]);}}}
 public static void Balcony(string path,string output){using(var s=new Bitmap(path)){int cw=s.Width/6;for(int i=0;i<6;i++){var c=new Rectangle(i*cw,0,i==5?s.Width-i*cw:cw,s.Height);Save(s,c,System.IO.Path.Combine(output,string.Format("castle_02_balcony_stage_{0}.png",i)),192,128);}}}
}
'@
$out=Join-Path $PSScriptRoot "..\..\Resources\res\castle_exterior";New-Item -ItemType Directory -Force $out|Out-Null
[ExteriorBatch]::Balcony((Join-Path $root 'exec-414ee4e0-0101-41ba-9e71-f0f440a6e27a.png'),$out)
foreach($castle in 3..10){[ExteriorBatch]::Grid((Join-Path $root $sheets[$castle]),$out,$castle)}
