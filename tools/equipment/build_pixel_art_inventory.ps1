param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

# Restyle only the newly produced inventory sprites. Native dimensions and
# transparency stay intact so every existing bag-cell mask remains valid.
Add-Type -AssemblyName System.Drawing
Add-Type -ReferencedAssemblies System.Drawing @'
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;

public static class InventoryPixelArt {
    struct Sample { public byte R, G, B, A; }
    public static void Convert(string source, string destination, int paletteSize) {
        using (var image = new Bitmap(source)) {
            int w = image.Width, h = image.Height;
            var pixels = new Sample[w * h];
            var buckets = new Dictionary<int, int>();
            for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
                Color c = image.GetPixel(x, y);
                int i = y * w + x;
                pixels[i] = new Sample { R=c.R, G=c.G, B=c.B, A=c.A };
                if (c.A < 24) continue;
                int key = (c.R / 24 << 8) | (c.G / 24 << 4) | (c.B / 24);
                int count;
                buckets.TryGetValue(key, out count);
                buckets[key] = count + 1;
            }
            var seeds = buckets.OrderByDescending(p => p.Value).Take(paletteSize).ToArray();
            if (seeds.Length == 0) { image.Save(destination, ImageFormat.Png); return; }
            var colors = new double[seeds.Length, 3];
            for (int i = 0; i < seeds.Length; ++i) {
                colors[i,0] = Math.Min(255, ((seeds[i].Key >> 8) & 15) * 24 + 12);
                colors[i,1] = Math.Min(255, ((seeds[i].Key >> 4) & 15) * 24 + 12);
                colors[i,2] = Math.Min(255, (seeds[i].Key & 15) * 24 + 12);
            }
            // A compact palette creates deliberately stepped highlights while
            // retaining the source design, hue progression and transparent shape.
            for (int pass = 0; pass < 5; ++pass) {
                var sums = new double[seeds.Length, 4];
                foreach (var p in pixels) {
                    if (p.A < 24) continue;
                    int index = Nearest(p, colors);
                    double weight = p.A / 255.0;
                    sums[index,0] += p.R * weight;
                    sums[index,1] += p.G * weight;
                    sums[index,2] += p.B * weight;
                    sums[index,3] += weight;
                }
                for (int i = 0; i < seeds.Length; ++i) if (sums[i,3] > 0) {
                    colors[i,0] = sums[i,0] / sums[i,3];
                    colors[i,1] = sums[i,1] / sums[i,3];
                    colors[i,2] = sums[i,2] / sums[i,3];
                }
            }
            var indices = new int[pixels.Length];
            for (int i = 0; i < pixels.Length; ++i)
                indices[i] = pixels[i].A == 0 ? -1 : Nearest(pixels[i], colors);
            using (var output = new Bitmap(w, h, PixelFormat.Format32bppArgb)) {
                for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
                    int i = y * w + x;
                    var p = pixels[i];
                    if (indices[i] < 0) continue;
                    int choice = indices[i];
                    // Cluster color into 2x2 pixel blocks where the source is
                    // fully opaque; leave silhouette edges and narrow details alone.
                    if (w >= 64 && h >= 64) {
                        int bx = x & ~1, by = y & ~1;
                        int a = by*w+bx, b = a+1, c = a+w, d = c+1;
                        if (bx+1 < w && by+1 < h && pixels[a].A > 224 &&
                            pixels[b].A > 224 && pixels[c].A > 224 && pixels[d].A > 224) {
                            choice = indices[a];
                        }
                    }
                    output.SetPixel(x, y, Color.FromArgb(p.A,
                        (int)Math.Round(colors[choice,0]),
                        (int)Math.Round(colors[choice,1]),
                        (int)Math.Round(colors[choice,2])));
                }
                output.Save(destination, ImageFormat.Png);
            }
        }
    }
    static int Nearest(Sample p, double[,] colors) {
        int best = 0; double bestDistance = double.MaxValue;
        for (int i = 0; i < colors.GetLength(0); ++i) {
            double dr = p.R - colors[i,0], dg = p.G - colors[i,1], db = p.B - colors[i,2];
            double distance = dr*dr*0.30 + dg*dg*0.59 + db*db*0.11;
            if (distance < bestDistance) { bestDistance = distance; best = i; }
        }
        return best;
    }
}
'@

$res = Join-Path $Root 'Resources\res'
$originals = Join-Path $Root 'content\equipment\pixel_art\originals'
$heroSources = @(
    (Join-Path $Root 'content\equipment\pixel_art\robin\native_sources'),
    (Join-Path $Root 'content\equipment\pixel_art\diana\native_sources'),
    (Join-Path $Root 'content\equipment\pixel_art\maxx\native_sources'),
    (Join-Path $Root 'content\equipment\pixel_art\inventory_gun\native_sources'),
    (Join-Path $Root 'content\equipment\pixel_art\inventory_boomerang\native_sources'),
    (Join-Path $Root 'content\swords\remodel\pixel_overrides')
)
$files = [System.Collections.Generic.List[string]]::new()
for ($n=2; $n -le 34; $n++) { $files.Add("w0_$n.png") }
for ($n=1; $n -le 35; $n++) {
    $files.Add("inventory_gun\$n.png")
    $files.Add("inventory_boomerang\$n.png")
}
foreach ($hero in @('robin','diana','maxx')) {
    for ($n=1; $n -le 8; $n++) { $files.Add("inventory_helm\${hero}_$n.png") }
    $armor = switch ($hero) { 'robin' {'armor'} 'diana' {'vest'} 'maxx' {'coat'} }
    for ($n=0; $n -le 7; $n++) {
        $files.Add("item_${armor}_${hero}$n.png")
        foreach ($kind in @('pants','boots','glove')) { $files.Add("item_${kind}_${hero}$n.png") }
    }
}

$changed = 0
foreach ($relative in $files) {
    $target = Join-Path $res $relative
    if (-not (Test-Path -LiteralPath $target)) { throw "Missing inventory sprite: $relative" }
    $original = Join-Path $originals $relative
    New-Item -ItemType Directory -Path (Split-Path $original) -Force | Out-Null
    if (-not (Test-Path -LiteralPath $original)) { Copy-Item -LiteralPath $target -Destination $original }
    $temp = "$target.pixel-tmp.png"
    try {
        $palette = if ($relative -match '^(inventory_gun|inventory_boomerang)') { 32 } else { 28 }
        $source = $original
        foreach ($heroSourceDir in $heroSources) {
            $candidate = Join-Path $heroSourceDir $relative
            if (Test-Path -LiteralPath $candidate) { $source = $candidate; break }
        }
        [InventoryPixelArt]::Convert($source, $temp, $palette)
        Move-Item -LiteralPath $temp -Destination $target -Force
        $changed++
    } finally {
        if (Test-Path -LiteralPath $temp) { Remove-Item -LiteralPath $temp }
    }
}
Write-Output "Built $changed pixel-art inventory sprites"
