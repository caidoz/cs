# Bake six visibly different roof crowns for castles 2-10.
# A single scale per castle preserves the relative growth of all six stages;
# the original hollow shell supplies the exact full-width lower joint.
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;

public static class CastleSpireBake {
    static readonly int[] Heights={0,0,220,197,340,300,320,320,320,320,330};
    static Rectangle AlphaBounds(Bitmap image,Rectangle cell) {
        int minX=cell.Right,minY=cell.Bottom,maxX=cell.Left-1,maxY=cell.Top-1;
        for(int y=cell.Top;y<cell.Bottom;y++) for(int x=cell.Left;x<cell.Right;x++) {
            if(image.GetPixel(x,y).A<24) continue;
            minX=Math.Min(minX,x);minY=Math.Min(minY,y);
            maxX=Math.Max(maxX,x);maxY=Math.Max(maxY,y);
        }
        if(maxX<minX) throw new Exception("Empty spire cell "+cell);
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
            int height=Heights[castle];
            string sheetPath=Path.Combine(concepts,String.Format("castle_{0:00}_spire_sheet.png",castle));
            string shellPath=Path.Combine(exterior,String.Format("castle_{0:00}_hollow_stage_0.png",castle));
            using(var sheet=new Bitmap(sheetPath))
            using(var shell=new Bitmap(shellPath)) {
                if(sheet.Width!=1536 || sheet.Height!=1024)
                    throw new Exception("Expected 1536x1024 sheet: "+sheetPath);
                if(shell.Width!=640 || shell.Height<height)
                    throw new Exception("Bad hollow shell: "+shellPath);
                var bounds=new Rectangle[6];
                int maxW=0,maxH=0;
                // Generated rows have intentionally different crown heights.
                // Equal thirds can capture the next row's flag finial; use
                // the transparent gutters instead of a nominal 1024/3 cut.
                int cut1=RowCut(sheet,240,410,341);
                int cut2=RowCut(sheet,590,760,683);
                Console.WriteLine("castle {0}: sheet row cuts {1}, {2}",castle,cut1,cut2);
                int[] edges={0,cut1,cut2,sheet.Height};
                for(int stage=0;stage<6;stage++) {
                    int col=stage%2,row=stage/2;
                    var cell=Rectangle.FromLTRB(col*sheet.Width/2,edges[row],
                        (col+1)*sheet.Width/2,edges[row+1]);
                    bounds[stage]=AlphaBounds(sheet,cell);
                    maxW=Math.Max(maxW,bounds[stage].Width);
                    maxH=Math.Max(maxH,bounds[stage].Height);
                }
                // Identical uniform scale across the whole upgrade series:
                // no tower is stretched and the simpler stages stay smaller.
                double scale=Math.Min(640.0/maxW,height/(double)maxH);
                for(int stage=0;stage<6;stage++) {
                    using(var outImage=new Bitmap(640,height,PixelFormat.Format32bppArgb))
                    using(var g=Graphics.FromImage(outImage)) {
                        g.Clear(Color.Transparent);
                        g.InterpolationMode=InterpolationMode.HighQualityBicubic;
                        g.PixelOffsetMode=PixelOffsetMode.HighQuality;
                        // The shared lower rail is the exact last 48 pixels
                        // of the already-aligned hollow crown. It preserves
                        // the join to 64px side walls at any camera zoom.
                        g.DrawImage(shell,new Rectangle(0,height-48,640,48),
                            new Rectangle(0,height-48,640,48),GraphicsUnit.Pixel);
                        int w=(int)Math.Round(bounds[stage].Width*scale);
                        int h=(int)Math.Round(bounds[stage].Height*scale);
                        g.DrawImage(sheet,new Rectangle((640-w)/2,height-h,w,h),
                            bounds[stage],GraphicsUnit.Pixel);
                        string output=Path.Combine(exterior,
                            String.Format("castle_{0:00}_roof_stage_{1}.png",castle,stage));
                        outImage.Save(output,ImageFormat.Png);
                    }
                }
            }
        }
    }
}
'@
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
[CastleSpireBake]::Run($root)
Write-Host 'Built 54 independent roof crowns at exact castle-specific heights.'
