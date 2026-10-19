param([Parameter(Mandatory=$true)][string]$EditedSource,[ValidateRange(0,5)][int]$Stage=0)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.IO;
public static class StarterRockPatch {
 public static void Run(string edited,string master,string output) {
  using(var src=new Bitmap(edited)) using(var dst=new Bitmap(master)) {
   if(src.Width!=1536||src.Height!=1024||dst.Size!=src.Size) throw new Exception("Registered 1536x1024 edit required");
   // Extract the imagegen rock only; retain all other authored castle pixels.
   int ox=1536,oy=1024,orr=0,ob=0;
   for(int y=225;y<350;y++) for(int x=1330;x<1515;x++) {
    var c=dst.GetPixel(x,y);
    if(c.A>128 && c.R>80 && Math.Abs(c.R-c.G)<30 && Math.Abs(c.G-c.B)<30) {
     ox=Math.Min(ox,x); oy=Math.Min(oy,y); orr=Math.Max(orr,x); ob=Math.Max(ob,y);
    }
   }
   int ax=1536,ay=1024,bx=0,by=0;
   for(int y=170;y<350;y++) for(int x=1300;x<1525;x++) {
    var c=src.GetPixel(x,y);
    if(c.A>128 && c.R>80 && Math.Abs(c.R-c.G)<30 && Math.Abs(c.G-c.B)<30) {
     ax=Math.Min(ax,x); ay=Math.Min(ay,y); bx=Math.Max(bx,x); by=Math.Max(by,y);
    }
   }
   if(bx<=ax||by<=ay) throw new Exception("Rock silhouette not found");
   using(var rock=new Bitmap(bx-ax+1,by-ay+1,PixelFormat.Format32bppArgb)) {
    for(int y=ay;y<=by;y++) for(int x=ax;x<=bx;x++) {
     var c=src.GetPixel(x,y);
     if(c.A>0 && Math.Abs(c.R-c.G)<40 && Math.Abs(c.G-c.B)<40) rock.SetPixel(x-ax,y-ay,c);
    }
    using(var g=Graphics.FromImage(dst)) {
     g.InterpolationMode=InterpolationMode.HighQualityBicubic;
     g.DrawImage(rock,new RectangleF((ox+orr+1)*.5f-(orr-ox+1)*.75f,ob+1-(ob-oy+1)*1.5f,(orr-ox+1)*1.5f,(ob-oy+1)*1.5f));
    }
   }
   // Bake the requested left-loaded orientation into the source itself.
   int gx=1536,gy=550,gr=0,gb=0;
   using(var weapon=new Bitmap(1536,1024,PixelFormat.Format32bppArgb)) {
    for(int y=0;y<550;y++) for(int x=1100;x<1536;x++) if((y<415||x>=1140) && dst.GetPixel(x,y).A!=0) {
     weapon.SetPixel(x,y,dst.GetPixel(x,y)); dst.SetPixel(x,y,Color.FromArgb(0,0,0,0));
     gx=Math.Min(gx,x); gy=Math.Min(gy,y); gr=Math.Max(gr,x); gb=Math.Max(gb,y);
    }
   using(var gun=weapon.Clone(new Rectangle(gx,gy,gr-gx+1,gb-gy+1),PixelFormat.Format32bppArgb)) {
    gun.RotateFlip(RotateFlipType.RotateNoneFlipX);
    for(int y=0;y<gun.Height;y++) for(int x=0;x<gun.Width;x++) if(gun.GetPixel(x,y).A!=0) dst.SetPixel(gx+x,gy+y,gun.GetPixel(x,y));
   }
   }
   for(int y=0;y<dst.Height;y++) for(int x=0;x<dst.Width;x++) if(dst.GetPixel(x,y).A==0) dst.SetPixel(x,y,Color.FromArgb(0,0,0,0));
   dst.Save(output,ImageFormat.Png);
  }
 }
}
'@
$dir=Join-Path $root 'content/castles/starter_modular_sd_v1'
if($Stage -gt 0) { $dir=Join-Path $dir "upgrade-$Stage" }
$master=Join-Path $dir 'assembled-master.png'
$backup=Join-Path $dir 'before-large-rock.png'
if(!(Test-Path $backup)) { Copy-Item -LiteralPath $master -Destination $backup }
$updated=Join-Path $dir 'large-rock-master.png'
[StarterRockPatch]::Run($EditedSource,$backup,$updated)
Copy-Item -LiteralPath $updated -Destination $master -Force
"Enlarged rock and baked left-loaded catapult orientation, stage $Stage."
