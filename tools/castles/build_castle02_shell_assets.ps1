param([string]$Sheet="C:\Users\polyp\.codex\generated_images\01a0de43-6120-72f2-9314-8e5fb074b287\exec-ba5411ab-5bc0-47fb-af91-225cb1ca773a.png")
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System.Drawing; using System.Drawing.Drawing2D; using System.Drawing.Imaging;
public static class Castle02ShellBuilder {
 static Rectangle B(Bitmap b,Rectangle c){int a=c.Right,d=c.Bottom,e=c.Left,f=c.Top;for(int y=c.Top;y<c.Bottom;y++)for(int x=c.Left;x<c.Right;x++){if(b.GetPixel(x,y).A<8)continue;if(x<a)a=x;if(y<d)d=y;if(x>e)e=x;if(y>f)f=y;}return Rectangle.FromLTRB(a,d,e+1,f+1);}
 public static void Run(string p,string o){using(var s=new Bitmap(p)){int cw=s.Width/6,ch=s.Height/2;for(int row=0;row<2;row++)for(int i=0;i<6;i++){var c=new Rectangle(i*cw,row*ch,i==5?s.Width-i*cw:cw,row==1?s.Height-row*ch:ch);var q=B(s,c);int w=512,h=row==0?128:192;string part=row==0?"wall":"roof";using(var d=new Bitmap(w,h,PixelFormat.Format32bppArgb))using(var g=Graphics.FromImage(d)){g.Clear(Color.Transparent);g.CompositingMode=CompositingMode.SourceCopy;g.InterpolationMode=InterpolationMode.HighQualityBicubic;g.DrawImage(s,new Rectangle(0,0,w,h),q,GraphicsUnit.Pixel);d.Save(System.IO.Path.Combine(o,string.Format("castle_02_{0}_stage_{1}.png",part,i)),ImageFormat.Png);}}}}
}
'@
$out=Join-Path $PSScriptRoot "..\..\Resources\res\castle_exterior";New-Item -ItemType Directory -Force $out|Out-Null
[Castle02ShellBuilder]::Run($Sheet,$out)
