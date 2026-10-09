# Bake each castle's six command balcony + growing cannon concepts to 192x128.
# A common per-castle scale preserves the visible increase in cannon size.
$ErrorActionPreference='Stop'
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;

public static class CastleCommandBake {
    static void RemoveTinyIslands(Bitmap image) {
        int w=image.Width,h=image.Height;
        var seen=new bool[w*h];
        var queue=new int[w*h];
        for(int start=0;start<w*h;start++) {
            if(seen[start]) continue;
            seen[start]=true;
            if(image.GetPixel(start%w,start/w).A<24) continue;
            int head=0,count=0;queue[count++]=start;
            while(head<count) {
                int p=queue[head++],x=p%w,y=p/w;
                for(int dy=-1;dy<=1;dy++) for(int dx=-1;dx<=1;dx++) {
                    int xx=x+dx,yy=y+dy;
                    if(xx<0||xx>=w||yy<0||yy>=h) continue;
                    int next=yy*w+xx;
                    if(seen[next]) continue;
                    seen[next]=true;
                    if(image.GetPixel(xx,yy).A>=24) queue[count++]=next;
                }
            }
            if(count<12) for(int i=0;i<count;i++)
                image.SetPixel(queue[i]%w,queue[i]/w,Color.Transparent);
        }
    }
    static Rectangle AlphaBounds(Bitmap image,Rectangle cell) {
        int minX=cell.Right,minY=cell.Bottom,maxX=cell.Left-1,maxY=cell.Top-1;
        for(int y=cell.Top;y<cell.Bottom;y++) for(int x=cell.Left;x<cell.Right;x++) {
            if(image.GetPixel(x,y).A<24) continue;
            minX=Math.Min(minX,x);minY=Math.Min(minY,y);
            maxX=Math.Max(maxX,x);maxY=Math.Max(maxY,y);
        }
        if(maxX<minX) throw new Exception("Empty command cell: "+cell);
        return Rectangle.FromLTRB(minX,minY,maxX+1,maxY+1);
    }
    static int RowCut(Bitmap image,int from,int to,int expected) {
        int best=expected,bestCount=int.MaxValue;
        for(int y=from;y<to;y++) {
            int count=0;
            for(int x=0;x<image.Width;x+=4)
                if(image.GetPixel(x,y).A>=24) count++;
            if(count<bestCount || (count==bestCount &&
                Math.Abs(y-expected)<Math.Abs(best-expected))) {
                bestCount=count;best=y;
            }
        }
        return best;
    }
    public static void Run(string root) {
        string concepts=Path.Combine(root,"tools","castles","concepts");
        string exterior=Path.Combine(root,"Resources","res","castle_exterior");
        for(int castle=2;castle<=10;castle++) {
            string sheetPath=Path.Combine(concepts,
                String.Format("castle_{0:00}_command_sheet.png",castle));
            using(var sheet=new Bitmap(sheetPath)) {
                if(sheet.Width!=1536 || sheet.Height!=1024)
                    throw new Exception("Unexpected command source dimensions: "+sheetPath);
                int cut1=RowCut(sheet,250,410,341);
                int cut2=RowCut(sheet,590,760,683);
                int[] edges={0,cut1,cut2,sheet.Height};
                var bounds=new Rectangle[6];
                int maxW=0,maxH=0;
                for(int stage=0;stage<6;stage++) {
                    int col=stage%2,row=stage/2;
                    var cell=Rectangle.FromLTRB(col*sheet.Width/2,edges[row],
                        (col+1)*sheet.Width/2,edges[row+1]);
                    bounds[stage]=AlphaBounds(sheet,cell);
                    maxW=Math.Max(maxW,bounds[stage].Width);
                    maxH=Math.Max(maxH,bounds[stage].Height);
                }
                // All stages have the same scale. Growth is in the authored
                // gun, not in an accidental per-cell resize. Keep the floor
                // near y=64, matching the old hero anchor on the balcony.
                double scale=Math.Min(192.0/maxW,96.0/maxH);
                for(int stage=0;stage<6;stage++) {
                    using(var part=new Bitmap(192,128,PixelFormat.Format32bppArgb)) {
                      using(var g=Graphics.FromImage(part)) {
                        g.Clear(Color.Transparent);
                        g.InterpolationMode=InterpolationMode.HighQualityBicubic;
                        g.PixelOffsetMode=PixelOffsetMode.HighQuality;
                        // The authored left pillar itself is the connector;
                        // its first 32 pixels overlap the existing shell.
                        int w=(int)Math.Round(bounds[stage].Width*scale);
                        int h=(int)Math.Round(bounds[stage].Height*scale);
                        g.DrawImage(sheet,new Rectangle(0,96-h,w,h),
                            bounds[stage],GraphicsUnit.Pixel);
                        // Some generated sheets let a finial from the row
                        // above enter the next cell's transparent upper-left
                        // gutter. This area is empty in every command post.
                        g.CompositingMode=CompositingMode.SourceCopy;
                        using(var clear=new SolidBrush(Color.Transparent))
                            g.FillRectangle(clear,0,0,64,12);
                        if(castle==7 && stage==5)
                            using(var clear=new SolidBrush(Color.Transparent))
                                g.FillRectangle(clear,0,20,10,30);
                      }
                        RemoveTinyIslands(part);
                        string output=Path.Combine(exterior,
                            String.Format("castle_{0:00}_balcony_stage_{1}.png",castle,stage));
                        part.Save(output,ImageFormat.Png);
                    }
                }
                Console.WriteLine("castle {0}: command row cuts {1}, {2}; scale {3:F3}",
                    castle,cut1,cut2,scale);
            }
        }
    }
}
'@
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
[CastleCommandBake]::Run($root)
Write-Host 'Built 54 command-post/cannon sprites at exactly 192x128.'
