param([string]$Source='', [string]$Interior='', [ValidateRange(0,5)][int]$Stage=0)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$stageDir='content/castles/sixth_modular_sd_v1'
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
public static class SixthSdSplit {
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
  if((x-105)*(x-105)+(y-949)*(y-949)<=50*50) return 7;
  if((x-302)*(x-302)+(y-949)*(y-949)<=50*50) return 8;
  if(x>=295 && y>=580 && y<704) return 3;
  if(x>=295 && y>=704 && y<882) return 4;
  if(y<150) return 0;
  if(y>=150 && y<882 && x>=68 && x<228) return 1;
  if(y<884) return 2;
  if(y<925) return 5;
  return 6;
 }
 public static void Run(string root,string master,string interior,int stage) {
  string outDir=Path.Combine(root,"content/castles/sixth_modular_sd_v1");
  if(stage>0) outDir=Path.Combine(outDir,"upgrade-"+stage);
  Directory.CreateDirectory(outDir);
  string backup=Path.Combine(outDir,"original-resources"); Directory.CreateDirectory(backup);
  string[] names={"castle_exterior/castle_06_roof_stage_0.png","castle_exterior/castle_06_wall_stage_0.png",
   "castle_exterior/castle_06_hollow_stage_0.png","castle_exterior/castle_06_heavy_cannon_stage_0.png",
   "castle_exterior/castle_06_command_platform_stage_0.png","castle_exterior/castle_06_combat_deck_stage_0.png",
   "castle_mobility/castle_06_base_stage_0.png","castle_mobility/castle_06_wheel_stage_0.png"};
  for(int i=0;i<names.Length;i++) names[i]=names[i].Replace("_stage_0","_stage_"+stage);
  foreach(string n in names) { string dst=Path.Combine(backup,n); Directory.CreateDirectory(Path.GetDirectoryName(dst)); if(!File.Exists(dst)) File.Copy(Path.Combine(root,"Resources/res",n),dst); }
  string roomName="castle_room_06_"+stage+".png";
  if(!File.Exists(Path.Combine(backup,roomName))) File.Copy(Path.Combine(root,"Resources/res",roomName),Path.Combine(backup,roomName));
  foreach(string n in names) { string dst=Path.Combine(root,"Resources/res/castle_sd_sixth_legacy",n); Directory.CreateDirectory(Path.GetDirectoryName(dst)); File.Copy(Path.Combine(backup,n),dst,true); }
  File.Copy(Path.Combine(backup,roomName),Path.Combine(root,"Resources/res/castle_sd_sixth_legacy",roomName),true);
  using(var src=new Bitmap(master)) using(var inside=new Bitmap(interior)) {
   if(src.Width!=450||src.Height!=1024||inside.Width!=450||inside.Height!=1024) throw new Exception("Expected 450x1024 aligned masters");
   int w=src.Width,h=src.Height; byte[] raw=Read(src), roomRaw=Read(inside);
   // Register each furnished room independently to the six fixed floors.
   // Keep the sweeping silver shoulders and flat crenellated crown outside the aperture.
   using(var fitted=new Bitmap(160,732,PixelFormat.Format32bppArgb)) {
    int[] sourceEdges={140,250,375,493,610,735,860};
    int[] targetEdges={0,122,244,366,488,610,732};
    using(var g=Graphics.FromImage(fitted)) {
     g.CompositingMode=System.Drawing.Drawing2D.CompositingMode.SourceCopy;
     g.InterpolationMode=System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
     for(int i=0;i<6;i++) g.DrawImage(inside,
      new Rectangle(0,targetEdges[i],160,targetEdges[i+1]-targetEdges[i]),
      new Rectangle(105,sourceEdges[i],148,sourceEdges[i+1]-sourceEdges[i]),GraphicsUnit.Pixel);
    }
    byte[] mapped=Read(fitted);
    for(int y=0;y<732;y++) Buffer.BlockCopy(mapped,y*160*4,roomRaw,((150+y)*w+68)*4,160*4);
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
   var ns=stage==0?"SixthSdParts":"SixthSdPartsStage"+stage;
   var header=new StringBuilder("#pragma once\nnamespace "+ns+" {\n");
   header.Append("using Piece=StarterSdParts::Piece;\n");
   header.Append("static const int Width=450,Height=1024;\nstatic const Piece Pieces[9]={\n");
   var manifest=new StringBuilder("{\"masterWidth\":450,\"masterHeight\":1024,\"visiblePixelMismatches\":0,\"parts\":[");
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
   var aperture=new Rectangle(68,150,160,732); var room=new byte[160*732*4];
   for(int y=0;y<732;y++) Buffer.BlockCopy(roomRaw,((150+y)*w+68)*4,room,y*160*4,160*4);
   using(var b=Make(room,160,732)) b.Save(Path.Combine(root,"Resources/res",roomName),ImageFormat.Png);
   int launchX=441,launchY=635,visibleTop=h;
   for(int y=0;y<h;y++) for(int x=0;x<w;x++)
    if(raw[(y*w+x)*4+3]>=192) visibleTop=Math.Min(visibleTop,y);
   header.Append("};\nstatic const Piece Room={68,150,160,732,0,0};\nstatic const int FloorY=872,DeckY=884,HeroX=385,HeroY=884,DeckX=15,DeckW=280,GroundY=999,WheelRadius=50;\nstatic const float RoomFloorGap=122.0f;\n");
   header.AppendFormat("static const int StoneX={0},StoneY={1},TopVisibleY={2};\n}}\n",launchX,launchY,visibleTop);
   File.WriteAllText(Path.Combine(root,"Classes/Data/"+ns+".h"),header.ToString(),new UTF8Encoding(false));
   manifest.Append("]}"); File.WriteAllText(Path.Combine(outDir,"parts.json"),manifest.ToString(),new UTF8Encoding(false));
   // Open-state reconstruction uses identical exterior pixels and only swaps the room aperture.
   for(int y=150;y<882;y++) for(int x=68;x<228;x++) Buffer.BlockCopy(roomRaw,(y*w+x)*4,assembled,(y*w+x)*4,4);
   using(var re=Make(assembled,w,h)) re.Save(Path.Combine(outDir,"reassembled-open.png"),ImageFormat.Png);
   // Source and renderer share the authored right-facing heavy shell cannon pose.
   foreach(bool opened in new bool[]{false,true}) {
    var game=new byte[raw.Length]; Buffer.BlockCopy(diskRebuild,0,game,0,raw.Length);
    if(opened) for(int y=150;y<882;y++) for(int x=68;x<228;x++)
     Buffer.BlockCopy(roomRaw,(y*w+x)*4,game,(y*w+x)*4,4);
    using(var re=Make(game,w,h)) re.Save(Path.Combine(outDir,"reassembled-game-"+(opened?"open":"closed")+".png"),ImageFormat.Png);
   }
   File.WriteAllText(Path.Combine(outDir,"partition-check.txt"),"PASS exact exterior partition: "+visible+" visible pixels; 0 RGBA mismatches; no overlapping ownership.\nRoom aperture 68,150,160,732; all other exterior pixels unchanged.\n");
   Console.WriteLine("PASS exact partition, "+visible+" visible pixels, nine exterior pieces plus room, existing resource names retained");
  }
 }
}
'@
[SixthSdSplit]::Run($root,(Join-Path $root $Source),(Join-Path $root $Interior),$Stage)
