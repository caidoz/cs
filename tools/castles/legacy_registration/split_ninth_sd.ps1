param([string]$Source='', [string]$Interior='', [ValidateRange(0,5)][int]$Stage=0)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$stageDir='content/castles/ninth_modular_sd_v1'
if($Stage -gt 0) { $stageDir+='/upgrade-'+$Stage }
if(!$Source) { $Source=$stageDir+'/assembled-master.png' }
if(!$Interior) { $Interior=$stageDir+'/interior-source.png' }
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.IO;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
public static class NinthSdSplit {
 static byte[] Read(Bitmap b) {
  var d=b.LockBits(new Rectangle(0,0,b.Width,b.Height),ImageLockMode.ReadOnly,PixelFormat.Format32bppArgb);
  var a=new byte[b.Width*b.Height*4];
  for(int y=0;y<b.Height;y++) Marshal.Copy(IntPtr.Add(d.Scan0,y*d.Stride),a,y*b.Width*4,b.Width*4);
  b.UnlockBits(d); return a;
 }
 static Bitmap Make(byte[] a,int w,int h) {
  var b=new Bitmap(w,h,PixelFormat.Format32bppArgb);
  var d=b.LockBits(new Rectangle(0,0,w,h),ImageLockMode.WriteOnly,PixelFormat.Format32bppArgb);
  for(int y=0;y<h;y++) Marshal.Copy(a,y*w*4,IntPtr.Add(d.Scan0,y*d.Stride),w*4);
  b.UnlockBits(d); return b;
 }
 static int Group(int x,int y) {
  if((x-70)*(x-70)+(y-959)*(y-959)<=36*36) return 7;
  if((x-195)*(x-195)+(y-959)*(y-959)<=36*36) return 8;
  if(x>=205 && y>=360 && y<740) return 3;
  if(x>=205 && y>=740 && y<900) return 4;
  if(y<180) return 0;
  if(y>=180 && y<900 && x>=95 && x<195) return 1;
  if(y<900) return 2;
  if(y<935) return 5;
  return 6;
 }
 public static void Run(string root,string master,string interior,int stage) {
  string outDir=Path.Combine(root,"content/castles/ninth_modular_sd_v1");
  if(stage>0) outDir=Path.Combine(outDir,"upgrade-"+stage);
  Directory.CreateDirectory(outDir);
  string backup=Path.Combine(outDir,"original-resources"); Directory.CreateDirectory(backup);
  string[] names={"castle_exterior/castle_09_roof_stage_0.png","castle_exterior/castle_09_wall_stage_0.png",
   "castle_exterior/castle_09_hollow_stage_0.png","castle_exterior/castle_09_heavy_cannon_stage_0.png",
   "castle_exterior/castle_09_command_platform_stage_0.png","castle_exterior/castle_09_combat_deck_stage_0.png",
   "castle_mobility/castle_09_base_stage_0.png","castle_mobility/castle_09_wheel_stage_0.png"};
  for(int i=0;i<names.Length;i++) names[i]=names[i].Replace("_stage_0","_stage_"+stage);
  foreach(string n in names) { string dst=Path.Combine(backup,n); Directory.CreateDirectory(Path.GetDirectoryName(dst)); if(!File.Exists(dst)) File.Copy(Path.Combine(root,"Resources/res",n),dst); }
  string roomName="castle_room_09_"+stage+".png";
  if(!File.Exists(Path.Combine(backup,roomName))) File.Copy(Path.Combine(root,"Resources/res",roomName),Path.Combine(backup,roomName));
  foreach(string n in names) { string dst=Path.Combine(root,"Resources/res/castle_sd_ninth_legacy",n); Directory.CreateDirectory(Path.GetDirectoryName(dst)); File.Copy(Path.Combine(backup,n),dst,true); }
  File.Copy(Path.Combine(backup,roomName),Path.Combine(root,"Resources/res/castle_sd_ninth_legacy",roomName),true);
  using(var src=new Bitmap(master)) using(var inside=new Bitmap(interior)) {
   if(src.Width!=300||src.Height!=1024||inside.Width!=1536||inside.Height!=1024) throw new Exception("Expected 300x1024 exterior and 1536x1024 interior source");
   int w=src.Width,h=src.Height; byte[] raw=Read(src), roomRaw=new byte[w*h*4];
   // Register each furnished room independently to the nine fixed floors.
   // Keep the faceted violet crystal slabs and silver ribs outside the aperture.
   using(var fitted=new Bitmap(100,720,PixelFormat.Format32bppArgb)) {
    int[] sourceEdges={0,163,268,377,478,588,688,799,899,1010};
    int[] targetEdges={0,80,160,240,320,400,480,560,640,720};
    using(var g=Graphics.FromImage(fitted)) {
     g.CompositingMode=System.Drawing.Drawing2D.CompositingMode.SourceCopy;
     g.InterpolationMode=System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
     for(int i=0;i<9;i++) g.DrawImage(inside,
      new Rectangle(0,targetEdges[i],100,targetEdges[i+1]-targetEdges[i]),
      new Rectangle(500,sourceEdges[i],540,sourceEdges[i+1]-sourceEdges[i]),GraphicsUnit.Pixel);
    }
    byte[] mapped=Read(fitted);
    for(int y=0;y<720;y++) Buffer.BlockCopy(mapped,y*100*4,roomRaw,((180+y)*w+95)*4,100*4);
   }
   // Match any gaps at the upper keep silhouette; no interior can leak outside the shell.
   for(int y=180;y<900;y++) for(int x=95;x<195;x++) {
    int p=(y*w+x)*4;roomRaw[p+3]=Math.Min(roomRaw[p+3],raw[p+3]);
   }
   byte[][] groups=new byte[9][]; var boxes=new Rectangle[9];
   for(int i=0;i<9;i++) { groups[i]=new byte[raw.Length]; boxes[i]=new Rectangle(w,h,0,0); }
   int[] minX=new int[9],minY=new int[9],maxX=new int[9],maxY=new int[9];
   for(int i=0;i<9;i++) { minX[i]=w; minY[i]=h; maxX[i]=maxY[i]=-1; }
   for(int y=0;y<h;y++) for(int x=0;x<w;x++) {
    int p=(y*w+x)*4, g=Group(x,y); if(raw[p+3]==0) continue;
    Buffer.BlockCopy(raw,p,groups[g],p,4);
    minX[g]=Math.Min(minX[g],x); minY[g]=Math.Min(minY[g],y); maxX[g]=Math.Max(maxX[g],x); maxY[g]=Math.Max(maxY[g],y);
   }
   // Exterior partition verification compares RGBA values of every visible pixel.
   int mismatches=0,visible=0; byte[] assembled=new byte[raw.Length];
   for(int p=0;p<raw.Length;p+=4) {
    int owners=0; for(int g=0;g<9;g++) if(groups[g][p+3]!=0) { owners++; Buffer.BlockCopy(groups[g],p,assembled,p,4); }
    if(raw[p+3]!=0) { visible++; if(owners!=1) mismatches++; for(int k=0;k<4;k++) if(assembled[p+k]!=raw[p+k]) mismatches++; }
   }
   if(mismatches!=0) throw new Exception("Exterior reconstruction mismatch: "+mismatches);
   using(var re=Make(assembled,w,h)) re.Save(Path.Combine(outDir,"reassembled-closed.png"),ImageFormat.Png);
   var ns=stage==0?"NinthSdParts":"NinthSdPartsStage"+stage;
   var header=new StringBuilder("#pragma once\nnamespace "+ns+" {\n");
   header.Append("using Piece=StarterSdParts::Piece;\n");
   header.Append("static const int Width=300,Height=1024;\nstatic const Piece Pieces[9]={\n");
   var manifest=new StringBuilder("{\"masterWidth\":300,\"masterHeight\":1024,\"visiblePixelMismatches\":0,\"parts\":[");
   byte[][] crops=new byte[9][];
   for(int i=0;i<9;i++) {
    boxes[i]=new Rectangle(minX[i],minY[i],maxX[i]-minX[i]+1,maxY[i]-minY[i]+1);
    var r=boxes[i]; crops[i]=new byte[r.Width*r.Height*4];
    for(int y=0;y<r.Height;y++) Buffer.BlockCopy(groups[i],((r.Y+y)*w+r.X)*4,crops[i],y*r.Width*4,r.Width*4);
   }
   int wheelWidth=boxes[7].Width+boxes[8].Width,wheelHeight=Math.Max(boxes[7].Height,boxes[8].Height);
   var wheel=new byte[wheelWidth*wheelHeight*4];
   for(int i=0;i<9;i++) {
    var r=boxes[i]; int sx=i==8?boxes[7].Width:0;
    string name=names[Math.Min(i,7)];
    if(i<7) using(var b=Make(crops[i],r.Width,r.Height)) b.Save(Path.Combine(root,"Resources/res",name),ImageFormat.Png);
    else for(int y=0;y<r.Height;y++) Buffer.BlockCopy(crops[i],y*r.Width*4,wheel,(y*wheelWidth+sx)*4,r.Width*4);
    header.AppendFormat(" {{{0},{1},{2},{3},{4},0}},\n",r.X,r.Y,r.Width,r.Height,sx);
    if(i!=0) manifest.Append(',');
    manifest.AppendFormat("{{\"name\":\"{0}\",\"x\":{1},\"y\":{2},\"w\":{3},\"h\":{4},\"sx\":{5}}}",name,r.X,r.Y,r.Width,r.Height,sx);
   }
   using(var b=Make(wheel,wheelWidth,wheelHeight)) b.Save(Path.Combine(root,"Resources/res",names[7]),ImageFormat.Png);
   // Independently reload the saved PNGs, not the in-memory partition buffers.
   var diskRebuild=new byte[raw.Length];
   for(int i=0;i<9;i++) using(var png=new Bitmap(Path.Combine(root,"Resources/res",names[Math.Min(i,7)]))) {
    byte[] bytes=Read(png); var r=boxes[i]; int sourceX=i==8?boxes[7].Width:0;
    for(int y=0;y<r.Height;y++) for(int x=0;x<r.Width;x++) {
     int s=(y*png.Width+sourceX+x)*4, d=((r.Y+y)*w+r.X+x)*4;
     if(bytes[s+3]!=0) Buffer.BlockCopy(bytes,s,diskRebuild,d,4);
    }
   }
   for(int p=0;p<raw.Length;p+=4) if(raw[p+3]!=0)
    for(int k=0;k<4;k++) if(raw[p+k]!=diskRebuild[p+k]) throw new Exception("Saved PNG reconstruction mismatch at byte "+(p+k));
   // The room occupies the same exact aperture. No AI exterior pixels are reused.
   var aperture=new Rectangle(95,180,100,720); var room=new byte[100*720*4];
   for(int y=0;y<720;y++) Buffer.BlockCopy(roomRaw,((180+y)*w+95)*4,room,y*100*4,100*4);
   using(var b=Make(room,100,720)) b.Save(Path.Combine(root,"Resources/res",roomName),ImageFormat.Png);
   for(int x=55;x<=240;x+=5) if(raw[(893*w+x)*4+3]<192)
    throw new Exception("Companion walking floor has a gap at "+x);
   if(raw[(893*w+260)*4+3]<192) throw new Exception("Hero walking floor missing");
   int launchX=0,launchY=610,visibleTop=h;
   for(int y=300;y<740;y++) for(int x=220;x<w;x++)
    if(raw[(y*w+x)*4+3]>=224) launchX=Math.Max(launchX,x);
   int lensTop=740,lensBottom=300;
   for(int y=300;y<740;y++) if(raw[(y*w+launchX-3)*4+3]>=224) {
    lensTop=Math.Min(lensTop,y);lensBottom=Math.Max(lensBottom,y);
   }
   if(lensTop>=lensBottom) throw new Exception("No solid coil cannon muzzle found");
   launchY=(lensTop+lensBottom)/2;launchX+=2;
   Console.WriteLine("Coil muzzle "+launchX+","+launchY+" / visible lens height "+(lensBottom-lensTop));
   for(int y=0;y<h;y++) for(int x=0;x<w;x++)
    if(raw[(y*w+x)*4+3]>=192) visibleTop=Math.Min(visibleTop,y);
   header.Append("};\nstatic const Piece Room={95,180,100,720,0,0};\nstatic const int FloorY=888,DeckY=900,HeroX=260,HeroY=900,DeckX=55,DeckW=185,GroundY=995,WheelRadius=36;\nstatic const float RoomFloorGap=80.0f;\n");
   header.AppendFormat("static const int StoneX={0},StoneY={1},TopVisibleY={2};\n}}\n",launchX,launchY,visibleTop);
   File.WriteAllText(Path.Combine(root,"Classes/Data/"+ns+".h"),header.ToString(),new UTF8Encoding(false));
   manifest.Append("]}"); File.WriteAllText(Path.Combine(outDir,"parts.json"),manifest.ToString(),new UTF8Encoding(false));
   // Open-state reconstruction uses identical exterior pixels and only swaps the room aperture.
   for(int y=180;y<900;y++) for(int x=95;x<195;x++) Buffer.BlockCopy(roomRaw,(y*w+x)*4,assembled,(y*w+x)*4,4);
   using(var re=Make(assembled,w,h)) re.Save(Path.Combine(outDir,"reassembled-open.png"),ImageFormat.Png);
   // Source and renderer share the authored right-facing electric coil cannon pose.
   foreach(bool opened in new bool[]{false,true}) {
    var game=new byte[raw.Length]; Buffer.BlockCopy(diskRebuild,0,game,0,raw.Length);
    if(opened) for(int y=180;y<900;y++) for(int x=95;x<195;x++)
     Buffer.BlockCopy(roomRaw,(y*w+x)*4,game,(y*w+x)*4,4);
    using(var re=Make(game,w,h)) re.Save(Path.Combine(outDir,"reassembled-game-"+(opened?"open":"closed")+".png"),ImageFormat.Png);
   }
   File.WriteAllText(Path.Combine(outDir,"partition-check.txt"),"PASS exact exterior partition: "+visible+" visible pixels; 0 RGBA mismatches; no overlapping ownership.\nRoom aperture 95,180,100,720; all other exterior pixels unchanged.\n");
   Console.WriteLine("PASS exact partition, "+visible+" visible pixels, nine exterior pieces plus room, existing resource names retained");
  }
 }
}
'@
[NinthSdSplit]::Run($root,(Join-Path $root $Source),(Join-Path $root $Interior),$Stage)
