param([string]$Root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path)

Add-Type -AssemblyName System.Drawing
$base=Join-Path $Root 'content\equipment\pixel_art'
$boomShapes=Get-Content -Raw (Join-Path $Root 'Resources\res\inventory_boomerang\manifest.json') | ConvertFrom-Json

function Keep-LargestComponent([System.Drawing.Bitmap]$bitmap) {
    $w=$bitmap.Width;$h=$bitmap.Height
    $visited=[bool[]]::new($w*$h)
    $largest=[System.Collections.Generic.List[int]]::new()
    for($y=0;$y -lt $h;$y++) {
        for($x=0;$x -lt $w;$x++) {
            $start=$y*$w+$x
            if($visited[$start] -or $bitmap.GetPixel($x,$y).A -le 16){continue}
            $queue=[System.Collections.Generic.Queue[int]]::new()
            $part=[System.Collections.Generic.List[int]]::new()
            $queue.Enqueue($start);$visited[$start]=$true
            while($queue.Count) {
                $p=$queue.Dequeue();$part.Add($p)
                $px=$p%$w;$py=[int][Math]::Floor($p/$w)
                for($dy=-1;$dy -le 1;$dy++) {
                    for($dx=-1;$dx -le 1;$dx++) {
                        $nx=$px+$dx;$ny=$py+$dy
                        if($nx -lt 0 -or $nx -ge $w -or $ny -lt 0 -or $ny -ge $h){continue}
                        $next=$ny*$w+$nx
                        if($visited[$next] -or $bitmap.GetPixel($nx,$ny).A -le 16){continue}
                        $visited[$next]=$true;$queue.Enqueue($next)
                    }
                }
            }
            if($part.Count -gt $largest.Count){$largest=$part}
        }
    }
    $keep=[bool[]]::new($w*$h)
    foreach($p in $largest){$keep[$p]=$true}
    for($y=0;$y -lt $h;$y++) {
        for($x=0;$x -lt $w;$x++) {
            if(-not $keep[$y*$w+$x]){$bitmap.SetPixel($x,$y,[System.Drawing.Color]::Transparent)}
        }
    }
}

foreach($weapon in @('gun','boomerang')) {
    $dir=Join-Path $base "inventory_$weapon"
    $output=Join-Path $dir "native_sources\inventory_$weapon"
    New-Item -ItemType Directory -Path $output -Force | Out-Null
    for($group=0;$group -lt 5;$group++) {
        $sheet=[System.Drawing.Bitmap]::FromFile((Join-Path $dir "group$group-pixel-sheet.png"))
        try {
            for($slot=0;$slot -lt 7;$slot++) {
                $n=$group*7+$slot+1
                $original=[System.Drawing.Bitmap]::FromFile((Join-Path $base "originals\inventory_$weapon\$n.png"))
                try {
                    $left=[int][Math]::Round($slot*$sheet.Width/7.0)
                    $right=[int][Math]::Round(($slot+1)*$sheet.Width/7.0)
                    $minX=$right;$minY=$sheet.Height;$maxX=-1;$maxY=-1
                    for($y=0;$y -lt $sheet.Height;$y++) {
                        for($x=$left;$x -lt $right;$x++) {
                            if($sheet.GetPixel($x,$y).A -ge 64) {
                                $minX=[Math]::Min($minX,$x);$maxX=[Math]::Max($maxX,$x)
                                $minY=[Math]::Min($minY,$y);$maxY=[Math]::Max($maxY,$y)
                            }
                        }
                    }
                    if($maxX -lt $minX){throw "Missing $weapon image $n"}
                    $workW=[int]($original.Width/2);$workH=[int]($original.Height/2)
                    $small=[System.Drawing.Bitmap]::new($workW,$workH,[System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
                    $g=[System.Drawing.Graphics]::FromImage($small)
                    try {
                        $g.Clear([System.Drawing.Color]::Transparent)
                        $g.InterpolationMode=[System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
                        $g.PixelOffsetMode=[System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality
                        $g.DrawImage($sheet,[System.Drawing.Rectangle]::new(1,1,$workW-2,$workH-2),
                            [System.Drawing.Rectangle]::new($minX,$minY,$maxX-$minX+1,$maxY-$minY+1),
                            [System.Drawing.GraphicsUnit]::Pixel)
                    } finally {$g.Dispose()}
                    $native=[System.Drawing.Bitmap]::new($original.Width,$original.Height,[System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
                    try {
                        for($y=0;$y -lt $native.Height;$y++) {
                            for($x=0;$x -lt $native.Width;$x++) {
                                $color=$small.GetPixel([int][Math]::Floor($x/2),[int][Math]::Floor($y/2))
                                if($color.A -lt 80){continue}
                                if($weapon -eq 'boomerang') {
                                    $shape=$boomShapes[$n-1]
                                    $col=[int][Math]::Floor($x/32)
                                    $rowFromBottom=$shape.rows-1-[int][Math]::Floor($y/32)
                                    $bit=1 -shl ($rowFromBottom*4+$col)
                                    if(($shape.cells -band $bit) -eq 0){continue}
                                }
                                $native.SetPixel($x,$y,[System.Drawing.Color]::FromArgb(255,$color.R,$color.G,$color.B))
                            }
                        }
                        if($weapon -eq 'boomerang'){Keep-LargestComponent $native}
                        $native.Save((Join-Path $output "$n.png"),[System.Drawing.Imaging.ImageFormat]::Png)
                    } finally {$native.Dispose();$small.Dispose()}
                } finally {$original.Dispose()}
            }
        } finally {$sheet.Dispose()}
    }
}
Write-Output 'Extracted 70 inventory weapon pixel-art sources'
