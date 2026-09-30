Add-Type -AssemblyName System.Drawing

Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;

public static class CastleExteriorFinal {
    static readonly Color[] Dark = {
        Color.FromArgb(69,39,22), Color.FromArgb(57,55,53),
        Color.FromArgb(91,34,28), Color.FromArgb(78,76,72),
        Color.FromArgb(31,86,77), Color.FromArgb(29,27,33),
        Color.FromArgb(83,135,177), Color.FromArgb(49,23,78),
        Color.FromArgb(27,23,29), Color.FromArgb(117,106,70)
    };
    static readonly Color[] Light = {
        Color.FromArgb(189,130,67), Color.FromArgb(167,166,158),
        Color.FromArgb(194,95,66), Color.FromArgb(224,219,201),
        Color.FromArgb(87,183,151), Color.FromArgb(150,59,47),
        Color.FromArgb(214,243,255), Color.FromArgb(169,82,224),
        Color.FromArgb(173,59,47), Color.FromArgb(252,239,187)
    };
    static readonly Color[] Trim = {
        Color.FromArgb(151,100,47), Color.FromArgb(120,119,116),
        Color.FromArgb(171,72,42), Color.FromArgb(54,113,204),
        Color.FromArgb(185,140,54), Color.FromArgb(148,43,32),
        Color.FromArgb(42,174,243), Color.FromArgb(151,56,224),
        Color.FromArgb(188,52,31), Color.FromArgb(211,175,72)
    };
    static Rectangle Bounds(Bitmap b, Rectangle area) {
        int l=area.Right,t=area.Bottom,r=area.Left-1,bt=area.Top-1;
        for(int y=area.Top;y<area.Bottom;y++)
            for(int x=area.Left;x<area.Right;x++)
                if(b.GetPixel(x,y).A>16) {l=Math.Min(l,x);t=Math.Min(t,y);r=Math.Max(r,x);bt=Math.Max(bt,y);}
        if(r<l) throw new InvalidDataException("Empty atlas cell");
        return Rectangle.FromLTRB(l,t,r+1,bt+1);
    }
    static void Setup(Graphics g) {
        g.Clear(Color.Transparent);
        g.InterpolationMode=InterpolationMode.HighQualityBicubic;
        g.PixelOffsetMode=PixelOffsetMode.HighQuality;
        g.CompositingMode=CompositingMode.SourceOver;
    }
    static void DrawStage(Graphics g,Bitmap source,Rectangle from,Rectangle to,int stage) {
        using(var attrs=new ImageAttributes()) {
            float strength=0.76f+stage*0.048f;
            var m=new ColorMatrix(new float[][] {
                new float[]{strength,0,0,0,0},new float[]{0,strength,0,0,0},
                new float[]{0,0,strength,0,0},new float[]{0,0,0,1,0},
                new float[]{0,0,0,0,1}});
            attrs.SetColorMatrix(m);
            g.DrawImage(source,to,from.X,from.Y,from.Width,from.Height,GraphicsUnit.Pixel,attrs);
        }
    }
    static Color Mix(Color a,Color b,float v) {
        return Color.FromArgb((int)(a.R+(b.R-a.R)*v),(int)(a.G+(b.G-a.G)*v),(int)(a.B+(b.B-a.B)*v));
    }
    static void DrawTintedSide(Graphics g,Bitmap atlas,Rectangle source,Rectangle destination,int castle) {
        using(var strip=new Bitmap(destination.Width,destination.Height,PixelFormat.Format32bppArgb)) {
            using(var sg=Graphics.FromImage(strip)) {
                Setup(sg);
                sg.DrawImage(atlas,new Rectangle(0,0,strip.Width,strip.Height),source,GraphicsUnit.Pixel);
            }
            for(int y=0;y<strip.Height;y++) for(int x=0;x<strip.Width;x++) {
                Color p=strip.GetPixel(x,y);
                if(p.A<8) continue;
                float lum=(p.R*.25f+p.G*.60f+p.B*.15f-25.0f)/205.0f;
                lum=Math.Max(0.0f,Math.Min(1.0f,lum));
                Color tint=Mix(Dark[castle],Light[castle],lum);
                strip.SetPixel(x,y,Color.FromArgb(p.A,tint.R,tint.G,tint.B));
            }
            g.DrawImageUnscaled(strip,destination.X,destination.Y);
        }
    }
    static Bitmap MakeWall(Bitmap atlas,int castle,int stage) {
        var wall=new Bitmap(640,128,PixelFormat.Format32bppArgb);
        int x0=(int)Math.Round(stage*atlas.Width/6.0), x1=(int)Math.Round((stage+1)*atlas.Width/6.0);
        int split=(x0+x1)/2, row=(int)Math.Round(atlas.Height/2.0);
        Rectangle lb=Bounds(atlas,Rectangle.FromLTRB(x0,0,split,row));
        Rectangle rb=Bounds(atlas,Rectangle.FromLTRB(split,0,x1,row));
        lb.Y+=(int)(lb.Height*.23f);lb.Height=(int)(lb.Height*.65f);
        rb.Y+=(int)(rb.Height*.23f);rb.Height=(int)(rb.Height*.65f);
        using(var g=Graphics.FromImage(wall)) {
            Setup(g);
            using(var body=new SolidBrush(Dark[castle])) {
                g.FillRectangle(body,0,0,70,128);
                g.FillRectangle(body,570,0,70,128);
            }
            // Textured armor is continuous from one floor to the next.
            DrawTintedSide(g,atlas,lb,new Rectangle(3,0,65,128),castle);
            DrawTintedSide(g,atlas,rb,new Rectangle(572,0,65,128),castle);
            using(var edge=new SolidBrush(Light[castle])) {
                g.FillRectangle(edge,61,0,5,128);
                g.FillRectangle(edge,574,0,5,128);
            }
            using(var rail=new SolidBrush(Dark[castle]))
                using(var accent=new SolidBrush(Trim[castle]))
                using(var shine=new SolidBrush(Light[castle])) {
                    // Top and lower lintels join both side walls to the room frame.
                    // Only the room's existing outermost 8px are covered.
                    g.FillRectangle(rail,61,0,518,8);
                    g.FillRectangle(accent,63,1,514,3);
                    g.FillRectangle(shine,63,4,514,1);
                    g.FillRectangle(rail,61,120,518,8);
                    g.FillRectangle(accent,63,122,514,3);
                    g.FillRectangle(shine,63,125,514,1);
                    for(int x=64;x<576;x+=64) {
                        g.FillRectangle(rail,x-3,0,6,8);
                        g.FillRectangle(rail,x-3,120,6,8);
                    }
                }
        }
        return wall;
    }
    public static void Build(string atlasPath,string roofPath,string balconyPath,string output,int castle) {
        using(var atlas=new Bitmap(atlasPath))
        using(var roofSource=new Bitmap(roofPath))
        using(var balconySource=new Bitmap(balconyPath)) {
            var roofBounds=Bounds(roofSource,new Rectangle(0,0,roofSource.Width,roofSource.Height));
            var balconyBounds=Bounds(balconySource,new Rectangle(0,0,balconySource.Width,balconySource.Height));
            for(int stage=0;stage<6;stage++) {
                using(var wall=MakeWall(atlas,castle-1,stage))
                    wall.Save(Path.Combine(output,String.Format("castle_{0:00}_wall_stage_{1}.png",castle,stage)),ImageFormat.Png);
                using(var roof=new Bitmap(512,342,PixelFormat.Format32bppArgb))
                using(var g=Graphics.FromImage(roof)) {
                    Setup(g);
                    // One uniform scale in both directions.  Tall towers retain height.
                    float s=Math.Min(512.0f/roofBounds.Width,342.0f/roofBounds.Height);
                    int w=(int)Math.Round(roofBounds.Width*s),h=(int)Math.Round(roofBounds.Height*s);
                    DrawStage(g,roofSource,roofBounds,new Rectangle((512-w)/2,342-h,w,h),stage);
                    // A continuous sill joins the lowest painted roof pixels
                    // to the upper room frame, including irregular overhangs.
                    using(var sill=new SolidBrush(Dark[castle-1]))
                    using(var accent=new SolidBrush(Trim[castle-1])) {
                        g.FillRectangle(sill,0,326,512,16);
                        g.FillRectangle(accent,0,328,512,4);
                        for(int i=0;i<stage;i++)
                            g.FillRectangle(accent,68+i*94,321,8,5);
                    }
                    roof.Save(Path.Combine(output,String.Format("castle_{0:00}_roof_stage_{1}.png",castle,stage)),ImageFormat.Png);
                }
                using(var balcony=new Bitmap(192,128,PixelFormat.Format32bppArgb))
                using(var g=Graphics.FromImage(balcony)) {
                    Setup(g);
                    float s=Math.Min(192.0f/balconyBounds.Width,128.0f/balconyBounds.Height);
                    int w=(int)Math.Round(balconyBounds.Width*s),h=(int)Math.Round(balconyBounds.Height*s);
                    DrawStage(g,balconySource,balconyBounds,new Rectangle(0,128-h,w,h),stage);
                    balcony.Save(Path.Combine(output,String.Format("castle_{0:00}_balcony_stage_{1}.png",castle,stage)),ImageFormat.Png);
                }
            }
        }
    }
}
'@

$root = $PSScriptRoot
$out = Join-Path $root '..\..\Resources\res\castle_exterior'
for ($castle=1; $castle -le 10; ++$castle) {
    $id = '{0:d2}' -f $castle
    [CastleExteriorFinal]::Build(
        (Join-Path $root "source_atlases\castle_${id}_exterior_atlas.png"),
        (Join-Path $root "source_roofs\castle_${id}_roof.png"),
        (Join-Path $root "source_balconies\castle_${id}_balcony.png"),
        $out, $castle)
}
Write-Host 'Built 60 connected walls 640x128, 60 proportional crowns 512x342, and 60 bottom commander decks 192x128.'
