# Bake the approved castle-1 concept into room-sized modular sprites.
# The 512x128 room PNGs are intentionally never opened or rewritten here.
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;

public static class Castle01CombatBake {
    static Bitmap Crop(Bitmap sheet, int stage, Rectangle source, int width, int height) {
        using (var cell = new Bitmap(source.Width, source.Height, PixelFormat.Format32bppArgb))
        using (var g = Graphics.FromImage(cell)) {
            g.Clear(Color.Transparent);
            g.DrawImage(sheet, new Rectangle(0, 0, source.Width, source.Height),
                new Rectangle((int)Math.Round((stage % 3) * sheet.Width / 3.0) + source.X,
                              (int)Math.Round((stage / 3) * sheet.Height / 2.0) + source.Y,
                              source.Width, source.Height), GraphicsUnit.Pixel);
            // The generated sheet has a dark teal presentation background.
            // Remove that background before resizing so edge pixels retain alpha.
            for (int y=0; y<cell.Height; ++y) for (int x=0; x<cell.Width; ++x) {
                Color c=cell.GetPixel(x,y);
                bool label=(source.Y+y<50 && source.X+x<185);
                bool topBorder=(source.Y+y<20 && c.R<160 && c.G<170 && c.B<180);
                bool backdrop=c.R<69 && c.G<94 && c.B<116 && c.B>c.R*1.08;
                if (label || topBorder || backdrop) cell.SetPixel(x,y,Color.Transparent);
            }
            var result=new Bitmap(width,height,PixelFormat.Format32bppArgb);
            using(var dst=Graphics.FromImage(result)) {
                dst.Clear(Color.Transparent);
                dst.InterpolationMode=InterpolationMode.HighQualityBicubic;
                dst.PixelOffsetMode=PixelOffsetMode.HighQuality;
                dst.DrawImage(cell,new Rectangle(0,0,width,height));
            }
            return result;
        }
    }
    static void Save(Bitmap b,string path) { b.Save(path,ImageFormat.Png); b.Dispose(); }
    static Bitmap MakeWheel(Bitmap wagon,int stage) {
        var wheel=new Bitmap(128,128,PixelFormat.Format32bppArgb);
        using(var g=Graphics.FromImage(wheel)) {
            g.Clear(Color.Transparent);
            g.SmoothingMode=SmoothingMode.AntiAlias;
            g.InterpolationMode=InterpolationMode.HighQualityBicubic;
            using(var clip=new GraphicsPath()) {
                clip.AddEllipse(new Rectangle(2,2,124,124));
                g.SetClip(clip);
                g.DrawImage(wagon,new Rectangle(2,2,124,124),
                    new Rectangle(260,657,216,228),GraphicsUnit.Pixel);
                g.ResetClip();
            }
            Color rim=stage<2?Color.FromArgb(148,91,48):
                stage==2?Color.FromArgb(177,103,49):
                stage==3?Color.FromArgb(70,76,82):
                stage==4?Color.FromArgb(188,128,58):Color.FromArgb(52,56,61);
            if(stage>0) {
                using(var p=new Pen(rim,stage>=4?6:stage>=2?4:2))
                    g.DrawEllipse(p,6,6,116,116);
                using(var p=new Pen(stage>=4?Color.FromArgb(229,176,73):rim,3))
                    g.DrawEllipse(p,51,51,26,26);
                if(stage>=3) {
                    using(var b=new SolidBrush(stage==5?Color.FromArgb(235,186,68):rim))
                        for(int i=0;i<8;++i) {
                            double a=i*Math.PI/4.0;
                            g.FillEllipse(b,(float)(64+51*Math.Cos(a)-3),
                                (float)(64+51*Math.Sin(a)-3),6,6);
                        }
                }
            }
        }
        return wheel;
    }
    public static void Run(string sheetPath,string res,string wagonPath) {
        Directory.CreateDirectory(Path.Combine(res,"castle_exterior"));
        Directory.CreateDirectory(Path.Combine(res,"castle_mobility"));
        using(var sheet=new Bitmap(sheetPath)) using(var wagon=new Bitmap(wagonPath)) {
            if(sheet.Width<1700 || sheet.Width>1800 || sheet.Height<870 || sheet.Height>920)
                throw new Exception("Unexpected concept sheet size: "+sheet.Size);
            for(int s=0;s<6;++s) {
                var roof=Crop(sheet,s,new Rectangle(28,0,546,190),736,256);
                Save(roof,Path.Combine(res,"castle_exterior",String.Format("castle_01_roof_stage_{0}.png",s)));

                var wall=Crop(sheet,s,new Rectangle(28,190,546,95),736,128);
                // Exact transparent 512x128 room aperture; no room art is baked in.
                using(var g=Graphics.FromImage(wall)) {
                    g.CompositingMode=CompositingMode.SourceCopy;
                    using(var clear=new SolidBrush(Color.Transparent))
                        g.FillRectangle(clear,64,0,512,128);
                }
                Save(wall,Path.Combine(res,"castle_exterior",String.Format("castle_01_wall_stage_{0}.png",s)));

                // Crop only the open combat space. The lower fascia comes from
                // a wheel-free 512x64 authored base, so no fixed wheel fragment
                // can remain under the two independently rotating sprites.
                var deck=new Bitmap(736,144,PixelFormat.Format32bppArgb);
                using(var open=Crop(sheet,s,new Rectangle(28,285,546,71),736,96))
                using(var baseImg=new Bitmap(Path.Combine(res,"castle_mobility",
                    String.Format("castle_01_base_stage_{0}.png",s))))
                using(var g=Graphics.FromImage(deck)) {
                    g.Clear(Color.Transparent);
                    g.DrawImageUnscaled(open,0,0);
                    g.CompositingMode=CompositingMode.SourceCopy;
                    using(var clear=new SolidBrush(Color.Transparent))
                        g.FillRectangle(clear,576,0,160,96);
                    g.CompositingMode=CompositingMode.SourceOver;
                    // Sink the chassis top 16px behind the combat-floor art.
                    // Several stages have transparent pixels at this seam.
                    g.DrawImageUnscaled(baseImg,64,80);
                }
                Save(deck,Path.Combine(res,"castle_exterior",String.Format("castle_01_combat_deck_stage_{0}.png",s)));

                var cannon=Crop(sheet,s,new Rectangle(455,239,119,95),160,128);
                Save(cannon,Path.Combine(res,"castle_exterior",String.Format("castle_01_cannon_stage_{0}.png",s)));

                var wheel=MakeWheel(wagon,s);
                Save(wheel,Path.Combine(res,"castle_mobility",String.Format("castle_01_wheel_stage_{0}.png",s)));
            }
        }
    }
}
'@
$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
[Castle01CombatBake]::Run(
    (Join-Path $root 'tools/castles/concepts/castle_01_battle_deck_50_percent_taller.png'),
    (Join-Path $root 'Resources/res'),
    (Join-Path $root 'tools/castles/source_shells/castle_01_full.png'))
Write-Host 'Built 6 stages of castle-1 roof 736x256, wall 736x128, deck 736x144, cannon 160x128, wheel 128x128.'
