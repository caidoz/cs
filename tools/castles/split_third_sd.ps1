param([string]$Source='content/castles/third_modular_sd_v1/assembled-master.png', [string]$Interior='content/castles/third_modular_sd_v1/interior-source.png', [ValidateRange(0,5)][int]$Stage=0)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.IO;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
public static class ThirdSdSplit {
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
  if((x-274)*(x-274)+(y-1222)*(y-1222)<=99*99) return 7;
  if((x-724)*(x-724)+(y-1222)*(y-1222)<=99*99) return 8;
  if(x>=810 && y<850) return 3;
  if(x>=810 && y<1040) return 4;
  if(y<490) return 0;
  if(y>=510 && y<1040 && x>=280 && x<750) return 1;
  if(y<1050) return 2;
  if(y<1135) return 5;
  return 6;
 }
 public static void Run(string root,string master,string interior,int stage) {
  string outDir=Path.Combine(root,"content/castles/third_modular_sd_v1");
  if(stage>0) outDir=Path.Combine(outDir,"upgrade-"+stage);
  Directory.CreateDirectory(outDir);
  string backup=Path.Combine(outDir,"original-resources"); Directory.CreateDirectory(backup);
  string[] names={"castle_exterior/castle_03_roof_stage_0.png","castle_exterior/castle_03_wall_stage_0.png",
   "castle_exterior/castle_03_hollow_stage_0.png","castle_exterior/castle_03_heavy_cannon_stage_0.png",
   "castle_exterior/castle_03_command_platform_stage_0.png","castle_exterior/castle_03_combat_deck_stage_0.png",
   "castle_mobility/castle_03_base_stage_0.png","castle_mobility/castle_03_wheel_stage_0.png"};
  for(int i=0;i<names.Length;i++) names[i]=names[i].Replace("_stage_0","_stage_"+stage);
  foreach(string n in names) { string dst=Path.Combine(backup,n); Directory.CreateDirectory(Path.GetDirectoryName(dst)); if(!File.Exists(dst)) File.Copy(Path.Combine(root,"Resources/res",n),dst); }
  string roomName="castle_room_03_"+stage+".png";
  if(!File.Exists(Path.Combine(backup,roomName))) File.Copy(Path.Combine(root,"Resources/res",roomName),Path.Combine(backup,roomName));
  foreach(string n in names) { string dst=Path.Combine(root,"Resources/res/castle_sd_third_legacy",n); Directory.CreateDirectory(Path.GetDirectoryName(dst)); File.Copy(Path.Combine(backup,n),dst,true); }
  File.Copy(Path.Combine(backup,roomName),Path.Combine(root,"Resources/res/castle_sd_third_legacy",roomName),true);
  using(var src=new Bitmap(master)) using(var inside=new Bitmap(interior)) {
   if(src.Width!=1133||src.Height!=1388||inside.Width!=1133||inside.Height!=1388) throw new Exception("Expected 1133x1388 aligned masters");
   int w=src.Width,h=src.Height; byte[] raw=Read(src), roomRaw=Read(inside);
   // Register each furnished room independently to the three fixed floors.
   // Keep the asymmetric tower and diagonal buttress outside the aperture.
   using(var fitted=new Bitmap(470,530,PixelFormat.Format32bppArgb)) {
    int[] sourceEdges=stage==5 ? new int[]{480,665,875,1040} : new int[]{510,695,895,1040};
    int[] targetEdges={0,177,353,530};
    using(var g=Graphics.FromImage(fitted)) {
     g.CompositingMode=System.Drawing.Drawing2D.CompositingMode.SourceCopy;
     g.InterpolationMode=System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
     for(int i=0;i<3;i++) g.DrawImage(inside,
      new Rectangle(0,targetEdges[i],470,targetEdges[i+1]-targetEdges[i]),
      new Rectangle(280,sourceEdges[i],470,sourceEdges[i+1]-sourceEdges[i]),GraphicsUnit.Pixel);
    }
    byte[] mapped=Read(fitted);
    for(int y=0;y<530;y++) Buffer.BlockCopy(mapped,y*470*4,roomRaw,((510+y)*w+280)*4,470*4);
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
   var ns=stage==0?"ThirdSdParts":"ThirdSdPartsStage"+stage;
   var header=new StringBuilder("#pragma once\nnamespace "+ns+" {\n");
   header.Append("using Piece=StarterSdParts::Piece;\n");
   header.Append("static const int Width=1133,Height=1388;\nstatic const Piece Pieces[9]={\n");
   var manifest=new StringBuilder("{\"masterWidth\":1133,\"masterHeight\":1388,\"visiblePixelMismatches\":0,\"parts\":[");
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
   var aperture=new Rectangle(280,510,470,530); var room=new byte[470*530*4];
   for(int y=0;y<530;y++) Buffer.BlockCopy(roomRaw,((510+y)*w+280)*4,room,y*470*4,470*4);
   using(var b=Make(room,470,530)) b.Save(Path.Combine(root,"Resources/res",roomName),ImageFormat.Png);
   int launchX=1095,launchY=770;
   header.Append("};\nstatic const Piece Room={280,510,470,530,0,0};\nstatic const int FloorY=1027,DeckY=1082,HeroX=960,HeroY=1082,DeckX=70,DeckW=720,GroundY=1321,WheelRadius=99;\nstatic const float RoomFloorGap=530.0f/3.0f;\n");
   header.AppendFormat("static const int StoneX={0},StoneY={1};\n}}\n",launchX,launchY);
   File.WriteAllText(Path.Combine(root,"Classes/Data/"+ns+".h"),header.ToString(),new UTF8Encoding(false));
   manifest.Append("]}"); File.WriteAllText(Path.Combine(outDir,"parts.json"),manifest.ToString(),new UTF8Encoding(false));
   // Open-state reconstruction uses identical exterior pixels and only swaps the room aperture.
   for(int y=510;y<1040;y++) for(int x=280;x<750;x++) Buffer.BlockCopy(roomRaw,(y*w+x)*4,assembled,(y*w+x)*4,4);
   using(var re=Make(assembled,w,h)) re.Save(Path.Combine(outDir,"reassembled-open.png"),ImageFormat.Png);
   // Source and renderer share the authored right-facing rocket pose.
   foreach(bool opened in new bool[]{false,true}) {
    var game=new byte[raw.Length]; Buffer.BlockCopy(raw,0,game,0,raw.Length);
    if(opened) for(int y=510;y<1040;y++) for(int x=280;x<750;x++)
     Buffer.BlockCopy(roomRaw,(y*w+x)*4,game,(y*w+x)*4,4);
    using(var re=Make(game,w,h)) re.Save(Path.Combine(outDir,"reassembled-game-"+(opened?"open":"closed")+".png"),ImageFormat.Png);
   }
   File.WriteAllText(Path.Combine(outDir,"partition-check.txt"),"PASS exact exterior partition: "+visible+" visible pixels; 0 RGBA mismatches; no overlapping ownership.\nRoom aperture 280,510,470,530; all other exterior pixels unchanged.\n");
   Console.WriteLine("PASS exact partition, "+visible+" visible pixels, nine exterior pieces plus room, existing resource names retained");
  }
 }
}
'@
[ThirdSdSplit]::Run($root,(Join-Path $root $Source),(Join-Path $root $Interior),$Stage)
