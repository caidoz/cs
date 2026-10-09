# Bake continuous, castle-height exterior flanks from the generated concept pairs.
# The two sides attach to the exact 512px room edges. Castles 9-10 split above
# 1024px so no runtime texture exceeds the requested height.
$ErrorActionPreference='Stop'
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;

public static class CastleWallPairBake {
    static Rectangle Bounds(Bitmap src, Rectangle area, bool leftSide) {
        int l=area.Right,t=area.Bottom,r=area.Left-1,b=area.Top-1;
        var innerEdges=new System.Collections.Generic.List<int>();
        for(int y=area.Top;y<area.Bottom;y+=2)
            for(int x=area.Left;x<area.Right;x+=2) {
                if(src.GetPixel(x,y).A<160) continue;
                l=Math.Min(l,x);t=Math.Min(t,y);r=Math.Max(r,x);b=Math.Max(b,y);
            }
        if(r<l) throw new Exception("Empty wall side in "+area);
        // An isolated antialiased ornament must not widen the crop at the
        // room-facing edge. That used to leave a broad transparent strip
        // between the wall and the 512px room after scaling.
        for(int y=area.Top;y<area.Bottom;y+=2) {
            if(leftSide) {
                for(int x=area.Right-1;x>=area.Left;x--) {
                    if(src.GetPixel(x,y).A<160) continue;
                    innerEdges.Add(x);break;
                }
            } else {
                for(int x=area.Left;x<area.Right;x++) {
                    if(src.GetPixel(x,y).A<160) continue;
                    innerEdges.Add(x);break;
                }
            }
        }
        innerEdges.Sort();
        if(innerEdges.Count>0) {
            int ix=leftSide?(int)(innerEdges.Count*.95):(int)(innerEdges.Count*.05);
            int edge=innerEdges[Math.Min(innerEdges.Count-1,ix)];
            if(leftSide) r=Math.Min(r,edge); else l=Math.Max(l,edge);
        }
        return Rectangle.FromLTRB(Math.Max(area.Left,l-2),Math.Max(area.Top,t-2),
            Math.Min(area.Right,r+3),Math.Min(area.Bottom,b+3));
    }
    static Bitmap RenderSide(Bitmap src,Rectangle crop,int width,int height) {
        var dst=new Bitmap(width,height,PixelFormat.Format32bppArgb);
        using(var g=Graphics.FromImage(dst)) {
            g.Clear(Color.Transparent);
            g.InterpolationMode=InterpolationMode.HighQualityBicubic;
            g.PixelOffsetMode=PixelOffsetMode.HighQuality;
            g.DrawImage(src,new Rectangle(0,0,width,height),
                crop.X,crop.Y,crop.Width,crop.Height,GraphicsUnit.Pixel);
        }
        return dst;
    }
    static void WriteSegment(Bitmap full,string path,int y,int height) {
        using(var segment=new Bitmap(full.Width,height,PixelFormat.Format32bppArgb)) {
            using(var g=Graphics.FromImage(segment)) {
                g.Clear(Color.Transparent);
                g.DrawImage(full,new Rectangle(0,0,full.Width,height),
                    new Rectangle(0,y,full.Width,height),GraphicsUnit.Pixel);
            }
            segment.Save(path,ImageFormat.Png);
        }
    }
    public static void Run(string root) {
        string concepts=Path.Combine(root,"tools","castles","concepts");
        string output=Path.Combine(root,"Resources","res","castle_exterior");
        for(int castle=2;castle<=10;castle++) {
            int wallH=castle*128;
            int leftW=140+12*castle;
            int rightW=110+10*castle;
            string name=String.Format("castle_{0:00}",castle);
            int lower=Math.Min(1024,wallH);
            int upper=wallH-lower;
            for(int stage=0;stage<6;stage++) {
                string source=Path.Combine(concepts,name+"_wall_pair"+
                    (stage==5?"":String.Format("_stage_{0}",stage))+".png");
                using(var src=new Bitmap(source)) {
                if(src.Width!=1024||src.Height!=1536)
                    throw new Exception("Expected portrait 1024x1536: "+source);
                // A short castle uses the lower part of the original tall
                // illustration, where its animal head and structural feet are.
                // Castle 2's animal relief is drawn above the lowest 512px
                // of the concept. Include it at every grade instead of
                // cropping the upgraded identity off the wall.
                int sourceH=Math.Min(src.Height,Math.Max(castle==2?1024:0,wallH*2));
                int sourceY=src.Height-sourceH;
                var left=Bounds(src,new Rectangle(0,sourceY,480,sourceH),true);
                var right=Bounds(src,new Rectangle(544,sourceY,480,sourceH),false);
                    using(var side=RenderSide(src,left,leftW,wallH)) {
                        WriteSegment(side,Path.Combine(output,String.Format(
                            "{0}_wall_left_stage_{1}_lower.png",name,stage)),upper,lower);
                        if(upper>0) WriteSegment(side,Path.Combine(output,String.Format(
                            "{0}_wall_left_stage_{1}_upper.png",name,stage)),0,upper);
                    }
                    using(var side=RenderSide(src,right,rightW,wallH)) {
                        WriteSegment(side,Path.Combine(output,String.Format(
                            "{0}_wall_right_stage_{1}_lower.png",name,stage)),upper,lower);
                        if(upper>0) WriteSegment(side,Path.Combine(output,String.Format(
                            "{0}_wall_right_stage_{1}_upper.png",name,stage)),0,upper);
                    }
                }
            }
            Console.WriteLine(name+" wall "+wallH+"px; sides "+leftW+"/"+rightW);
        }
        string names=Path.Combine(root,"Classes","CastleWallPairNames.inc");
        using(var writer=new StreamWriter(names,false,System.Text.Encoding.UTF8)) {
            writer.WriteLine("// Generated by tools/castles/build_castle02_10_wall_pairs.ps1.");
            for(int castle=2;castle<=10;castle++)
                for(int stage=0;stage<6;stage++)
                    foreach(string side in new[]{"left","right"})
                        writer.WriteLine(String.Format(
                            "\t\"castle_exterior/castle_{0:00}_wall_{1}_stage_{2}_lower\",",
                            castle,side,stage));
            for(int castle=9;castle<=10;castle++)
                for(int stage=0;stage<6;stage++)
                    foreach(string side in new[]{"left","right"})
                        writer.WriteLine(String.Format(
                            "\t\"castle_exterior/castle_{0:00}_wall_{1}_stage_{2}_upper\",",
                            castle,side,stage));
        }
    }
}
'@
[CastleWallPairBake]::Run((Resolve-Path .).Path)
