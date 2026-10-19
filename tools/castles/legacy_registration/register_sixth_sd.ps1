param([ValidateRange(0,5)][int]$Stage=0)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$assetDir=Join-Path $root 'content/castles/sixth_modular_sd_v1'
if($Stage -gt 0) { $assetDir=Join-Path $assetDir "upgrade-$Stage" }
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
public static class SixthSdRegister {
 public static Bitmap Exterior(Bitmap original,int stage) {
  if(stage==0) return original.Clone(new Rectangle(20,0,450,1024),PixelFormat.Format32bppArgb);
  // Curate increasing barrel mass: source variants 1,5,3,2,4.
  stage=new int[]{0,1,5,3,2,4}[stage];
  // Generated upgrades vary in wheel spacing and weapon overhang. Register
  // the assembly to fixed rig anchors; preserve the original generated PNG.
  int[] left={125,128,130,136,150,128},right={322,335,340,373,405,337};
  int[] cy={949,952,953,960,952,953},radius={50,55,53,59,60,54};
  int[] extent={462,507,569,560,592,556};
  int[] sx={20,left[stage],right[stage],extent[stage]+10};
  int[] dx={20,125,322,470};
  int[] sy={0,884,cy[stage],1024},dy={0,884,949,1024};
  using(var body=new Bitmap(original)) using(var canvas=new Bitmap(490,1024,PixelFormat.Format32bppArgb)) {
   using(var g=Graphics.FromImage(body)) {
    g.CompositingMode=CompositingMode.SourceCopy;
    foreach(int x in new int[]{left[stage],right[stage]})
     g.FillEllipse(Brushes.Transparent,x-radius[stage]-1,cy[stage]-radius[stage]-1,2*radius[stage]+2,2*radius[stage]+2);
   }
   using(var g=Graphics.FromImage(canvas)) {
    g.CompositingMode=CompositingMode.SourceCopy;
    g.InterpolationMode=InterpolationMode.HighQualityBicubic;
    for(int x=0;x<3;x++) for(int y=0;y<3;y++)
     g.DrawImage(body,new Rectangle(dx[x],dy[y],dx[x+1]-dx[x],dy[y+1]-dy[y]),
       new Rectangle(sx[x],sy[y],sx[x+1]-sx[x],sy[y+1]-sy[y]),GraphicsUnit.Pixel);
    for(int i=0;i<2;i++) {
     int sourceX=i==0?left[stage]:right[stage],targetX=i==0?125:322;
     using(var clip=new GraphicsPath()) {
      clip.AddEllipse(targetX-50,899,100,100);g.SetClip(clip);
      g.DrawImage(original,new Rectangle(targetX-50,899,100,100),
       new Rectangle(sourceX-radius[stage],cy[stage]-radius[stage],2*radius[stage],2*radius[stage]),GraphicsUnit.Pixel);
      g.ResetClip();
     }
    }
   }
   return canvas.Clone(new Rectangle(20,0,450,1024),PixelFormat.Format32bppArgb);
  }
 }
}
'@
foreach($pair in @(@('generated-master.png','assembled-master.png'),@('generated-interior.png','interior-source.png'))) {
 $src=[System.Drawing.Bitmap]::FromFile((Join-Path $assetDir $pair[0]))
 try {
  if($src.Width -ne 1536 -or $src.Height -ne 1024) { throw 'Expected 1536x1024 layout master' }
  if($pair[0] -eq 'generated-master.png') { $dst=[SixthSdRegister]::Exterior($src,$Stage) }
  else { $dst=$src.Clone([System.Drawing.Rectangle]::new(20,0,450,1024),[System.Drawing.Imaging.PixelFormat]::Format32bppArgb) }
  try { $dst.Save((Join-Path $assetDir $pair[1]),[System.Drawing.Imaging.ImageFormat]::Png) }
  finally { $dst.Dispose() }
 } finally { $src.Dispose() }
}
"PASS sixth stage ${Stage}: registered 450x1024 assembly, fixed circular wheel anchors"
