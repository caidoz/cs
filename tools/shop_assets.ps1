Add-Type -AssemblyName System.Drawing

$repo = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
if (-not (Test-Path (Join-Path $repo 'Resources\res\i6.png'))) {
    $repo = Split-Path -Parent $PSScriptRoot
}
$res = Join-Path $repo 'Resources\res'
$generated = 'C:\Users\polyp\.codex\generated_images\01a02fa8-ec36-71d2-8c60-d0940e68b2b3'
$goldSheet = Join-Path $generated 'exec-cb2ad090-6e30-4d5b-80d0-18d306bddc9d.png'
$heartSheet = Join-Path $generated 'exec-a0da0d71-eda9-470c-8b55-6f2c98cc38d1.png'
$boxBackdrop = Join-Path $generated 'exec-29688510-05b1-416a-916d-ca9abfb9a723.png'

function Save-Cells($sourcePath, $prefix) {
    $source = [System.Drawing.Bitmap]::FromFile($sourcePath)
    try {
        $cellW = [int]($source.Width / 3)
		$cellH = [int]($source.Height / 2)
		for ($i = 0; $i -lt 6; $i++) {
			$row = [int][Math]::Floor($i / 3.0)
			$srcRect = [System.Drawing.Rectangle]::new(($i % 3) * $cellW, $row * $cellH, $cellW, $cellH)
			$out = $source.Clone($srcRect, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
			try {
				$out.Save((Join-Path $res ("{0}_{1}.png" -f $prefix, $i)), [System.Drawing.Imaging.ImageFormat]::Png)
            }
            finally { $out.Dispose() }
        }
    }
    finally { $source.Dispose() }
}

function Hue-ToRgb([double]$p, [double]$q, [double]$t) {
    if ($t -lt 0) { $t += 1 }
    if ($t -gt 1) { $t -= 1 }
    if ($t -lt (1.0 / 6.0)) { return $p + ($q - $p) * 6 * $t }
    if ($t -lt 0.5) { return $q }
    if ($t -lt (2.0 / 3.0)) { return $p + ($q - $p) * ((2.0 / 3.0) - $t) * 6 }
    return $p
}

function Rainbow-Color([System.Drawing.Color]$color, [double]$hue) {
    if ($color.A -eq 0) { return $color }
    $max = [Math]::Max($color.R, [Math]::Max($color.G, $color.B)) / 255.0
    $min = [Math]::Min($color.R, [Math]::Min($color.G, $color.B)) / 255.0
    $light = ($max + $min) / 2.0
    if ($light -lt 0.13) { return [System.Drawing.Color]::FromArgb($color.A, $color.R, $color.G, $color.B) }
    $sat = [Math]::Min(1.0, 0.72 + ($max - $min) * 0.35)
    $q = if ($light -lt 0.5) { $light * (1 + $sat) } else { $light + $sat - $light * $sat }
    $p = 2 * $light - $q
    $r = [int](255 * (Hue-ToRgb $p $q ($hue + 1.0 / 3.0)))
    $g = [int](255 * (Hue-ToRgb $p $q $hue))
    $b = [int](255 * (Hue-ToRgb $p $q ($hue - 1.0 / 3.0)))
    return [System.Drawing.Color]::FromArgb($color.A, $r, $g, $b)
}

Save-Cells $goldSheet 'coin'
Save-Cells $heartSheet 'heart'

# 상자 카드 뒤 장식판.
$back = [System.Drawing.Bitmap]::FromFile($boxBackdrop)
try {
    $out = New-Object System.Drawing.Bitmap 512, 512, ([System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
    try {
        $g = [System.Drawing.Graphics]::FromImage($out)
        try {
            $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            $g.DrawImage($back, [System.Drawing.Rectangle]::new(0, 0, 512, 512))
        }
        finally { $g.Dispose() }
        $out.Save((Join-Path $res 'shop_card_box.png'), [System.Drawing.Imaging.ImageFormat]::Png)
    }
    finally { $out.Dispose() }
}
finally { $back.Dispose() }

# i6.png 좌상단: 첫 줄 8개 + 둘째 줄 2개가 금화 회전 10프레임이다.
$icons = [System.Drawing.Bitmap]::FromFile((Join-Path $res 'i6.png'))
try {
    $cash = New-Object System.Drawing.Bitmap 320, 32, ([System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
    try {
        for ($frame = 0; $frame -lt 10; $frame++) {
            $col = if ($frame -lt 8) { $frame } else { $frame - 8 }
            $row = if ($frame -lt 8) { 0 } else { 1 }
            for ($py = 0; $py -lt 32; $py++) {
                for ($px = 0; $px -lt 32; $px++) {
                    $src = $icons.GetPixel(1 + $col * 33 + $px, 1 + $row * 33 + $py)
                    $hue = (($frame * 0.085) + ($px + $py) / 150.0) % 1.0
                    $cash.SetPixel($frame * 32 + $px, $py, (Rainbow-Color $src $hue))
                }
            }
        }
        $cash.Save((Join-Path $res 'shop_cash_coin.png'), [System.Drawing.Imaging.ImageFormat]::Png)
    }
    finally { $cash.Dispose() }
}
finally { $icons.Dispose() }

Write-Output 'shop product assets generated'
