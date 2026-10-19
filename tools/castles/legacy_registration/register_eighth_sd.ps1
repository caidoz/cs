param([ValidateRange(0,5)][int]$Stage=0)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$assetDir=Join-Path $root 'content/castles/eighth_modular_sd_v1'
if($Stage -gt 0) { $assetDir=Join-Path $assetDir "upgrade-$Stage" }
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
public static class EighthSdRegister {
 public static Bitmap Exterior(Bitmap original) {
  int bottom=0,extent=0;
  for(int y=0;y<1024;y++) for(int x=0;x<1536;x++) if(original.GetPixel(x,y).A>=224) {
   bottom=Math.Max(bottom,y);extent=Math.Max(extent,x);
  }
  // At the contact line only the two load-bearing wheel rims remain.
  var centers=new List<int>(); int start=-1,row=bottom-8;
  for(int x=0;x<=extent+1;x++) {
   bool on=x<=extent && original.GetPixel(x,row).A>=224;
   if(on&&start<0) start=x;
   if(!on&&start>=0) { if(x-start>8) centers.Add((start+x-1)/2);start=-1; }
  }
  if(centers.Count!=2) throw new Exception("Expected two wheel contact runs, got "+centers.Count);
  int[] cx=centers.ToArray(); int minY=1024,maxY=0;
  foreach(int center in cx) for(int y=880;y<=bottom;y++) for(int x=center-45;x<=center+45;x++) {
   Color c=original.GetPixel(x,y);
   if(c.A>=224&&c.B>70&&c.B>c.R*1.20&&c.B>c.G*1.05) { minY=Math.Min(minY,y);maxY=Math.Max(maxY,y); }
  }
  if(minY>=maxY) throw new Exception("No blue wheel spokes found");
  int cy=(minY+maxY)/2, radius=bottom-cy;
  if(radius<30||radius>90) throw new Exception("Unexpected wheel radius "+radius);
  int[] sx={0,cx[0],cx[1],extent+10},dx={20,100,240,360};
  // Register the clear hero terrace surface as well as the wheel axles.
  // The actor origin is eight authored pixels below the visible sole line.
  int floorX=cx[1]+(305-240)*(extent+10-cx[1])/(360-240);
  int deckY=-1,run=-1;
  for(int y=825;y<=921;y++) {
   bool on=y<=920&&original.GetPixel(floorX,y).A>=224;
   if(on&&run<0) run=y;
   if(!on&&run>=0) { if(y-run>=18) { deckY=run;break; } run=-1; }
  }
  if(deckY<0||deckY>=cy) throw new Exception("Hero terrace surface not found");
  int[] sy={0,deckY,cy-radius,cy,cy+radius,1024},dy={0,892,915,955,995,1024};
  using(var body=new Bitmap(original)) using(var canvas=new Bitmap(380,1024,PixelFormat.Format32bppArgb)) {
   using(var g=Graphics.FromImage(body)) {
    g.CompositingMode=CompositingMode.SourceCopy;
    foreach(int x in cx) g.FillEllipse(Brushes.Transparent,x-radius-1,cy-radius-1,2*radius+2,2*radius+2);
   }
   using(var g=Graphics.FromImage(canvas)) {
    g.CompositingMode=CompositingMode.SourceCopy;g.InterpolationMode=InterpolationMode.HighQualityBicubic;
    for(int x=0;x<3;x++) for(int y=0;y<5;y++)
     g.DrawImage(body,new Rectangle(dx[x],dy[y],dx[x+1]-dx[x],dy[y+1]-dy[y]),
      new Rectangle(sx[x],sy[y],sx[x+1]-sx[x],sy[y+1]-sy[y]),GraphicsUnit.Pixel);
    for(int i=0;i<2;i++) using(var clip=new GraphicsPath()) {
     int targetX=i==0?100:240;clip.AddEllipse(targetX-40,915,80,80);g.SetClip(clip);
     g.DrawImage(original,new Rectangle(targetX-40,915,80,80),
      new Rectangle(cx[i]-radius,cy-radius,2*radius,2*radius),GraphicsUnit.Pixel);g.ResetClip();
    }
   }
   Console.WriteLine("Source wheel rig "+cx[0]+","+cx[1]+" / y="+cy+" / r="+radius+" / right="+extent+" / deck="+deckY);
   return canvas.Clone(new Rectangle(20,0,340,1024),PixelFormat.Format32bppArgb);
  }
 }
}
'@
foreach($pair in @(@('generated-master.png','assembled-master.png'),@('generated-interior.png','interior-source.png'))) {
 $src=[System.Drawing.Bitmap]::FromFile((Join-Path $assetDir $pair[0]))
 try {
  if($src.Width -ne 1536 -or $src.Height -ne 1024) { throw 'Expected 1536x1024 layout master' }
  if($pair[0] -eq 'generated-master.png') { $dst=[EighthSdRegister]::Exterior($src) }
  else { $dst=$src.Clone([System.Drawing.Rectangle]::new(0,0,1536,1024),[System.Drawing.Imaging.PixelFormat]::Format32bppArgb) }
  try { $dst.Save((Join-Path $assetDir $pair[1]),[System.Drawing.Imaging.ImageFormat]::Png) }
  finally { $dst.Dispose() }
 } finally { $src.Dispose() }
}
"PASS eighth stage ${Stage}: registered 340x1024 assembly, fixed circular wheel anchors"

