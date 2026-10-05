# 게임을 띄워 몇 번 눌러 보고 그 화면을 찍는다.
#
#     powershell -ExecutionPolicy Bypass -File tools/shot.ps1 -Clicks "0.25,0.62" -Out shot.png
#
# -Clicks 는 창 안의 비율 좌표다(왼쪽 위가 0,0). 쉼표로 x,y, 세미콜론으로
# 여러 번. 비율로 받는 것은 창 크기가 바뀌어도 같은 곳을 누르기 위해서다.
#
# GLFW 는 SendMessage 로 보낸 가짜 클릭을 무시한다. 그래서 진짜 커서를
# 옮겨 mouse_event 를 쏜다 - 그동안 사람이 마우스를 건드리면 어긋난다.
param(
    [string]$Clicks = "",
    [string]$Out = "shot.png",
    [int]$BootMs = 9000,
    [int]$ClickGapMs = 2500,
    [int]$SettleMs = 2500,
    [int]$W = 0,
    [int]$H = 0,
    [string]$Drag = "",
    [int]$DragSteps = 20,
    [int]$DragStepMs = 40
)

$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot
$exe = Join-Path $root "proj.win32\Debug.win32\cs.exe"

Add-Type @"
using System;
using System.Runtime.InteropServices;
public class Win {
    [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
    [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint x, uint y, uint d, IntPtr e);
    [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr h, ref POINT p);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
    [DllImport("user32.dll")] public static extern bool MoveWindow(IntPtr h, int x, int y, int w, int ht, bool repaint);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
    public struct RECT { public int Left, Top, Right, Bottom; }
    public struct POINT { public int X, Y; }
}
"@

[void][Win]::SetProcessDPIAware()

Get-Process cs -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Milliseconds 500

$p = Start-Process $exe -PassThru -WorkingDirectory (Split-Path $exe)
Start-Sleep -Milliseconds $BootMs
$p.Refresh()

$h = $p.MainWindowHandle
if ($h -eq [IntPtr]::Zero) { Write-Error "창을 못 찾았다"; exit 1 }

# 창 크기를 지정했으면 먼저 맞춘다. 화면 비율에 따라 달라지는 자리를
# 보려면 그 비율을 실제로 만들어야 한다. 테두리 두께만큼 더 키운다.
if ($W -gt 0 -and $H -gt 0) {
    $cr = New-Object Win+RECT
    $wr = New-Object Win+RECT
    [void][Win]::GetClientRect($h, [ref]$cr)
    [void][Win]::GetWindowRect($h, [ref]$wr)
    Write-Host ("크기 바꾸기 전: 안 {0}x{1}  밖 {2}x{3}" -f ($cr.Right-$cr.Left), ($cr.Bottom-$cr.Top), ($wr.Right-$wr.Left), ($wr.Bottom-$wr.Top))
    # 두 번 맞춘다. 한 번에 안 맞는 것은 테두리 두께를 미리 못 재서다 -
    # 재고 나서 모자란 만큼 한 번 더 민다.
    [void][Win]::MoveWindow($h, $wr.Left, $wr.Top, $W, $H, $true)
    Start-Sleep -Milliseconds 1200
    [void][Win]::GetClientRect($h, [ref]$cr)
    [void][Win]::GetWindowRect($h, [ref]$wr)
    $padW = ($wr.Right - $wr.Left) - ($cr.Right - $cr.Left)
    $padH = ($wr.Bottom - $wr.Top) - ($cr.Bottom - $cr.Top)
    [void][Win]::MoveWindow($h, $wr.Left, $wr.Top, $W + $padW, $H + $padH, $true)
    Start-Sleep -Milliseconds 1500
}

$r = New-Object Win+RECT
[void][Win]::GetClientRect($h, [ref]$r)
$o = New-Object Win+POINT
[void][Win]::ClientToScreen($h, [ref]$o)
$w = $r.Right - $r.Left
$ht = $r.Bottom - $r.Top
Write-Host ("창 {0}x{1} @ {2},{3}" -f $w, $ht, $o.X, $o.Y)

[void][Win]::SetForegroundWindow($h)
Start-Sleep -Milliseconds 600

if ($Clicks -ne "") {
    foreach ($c in $Clicks.Split(";")) {
        $xy = $c.Split(",")
        $cx = $o.X + [int]([double]$xy[0] * $w)
        $cy = $o.Y + [int]([double]$xy[1] * $ht)
        Write-Host ("누름 {0},{1}" -f $cx, $cy)
        [void][Win]::SetCursorPos($cx, $cy)
        Start-Sleep -Milliseconds 250
        [Win]::mouse_event(0x0002, 0, 0, 0, [IntPtr]::Zero)
        Start-Sleep -Milliseconds 90
        [Win]::mouse_event(0x0004, 0, 0, 0, [IntPtr]::Zero)
        Start-Sleep -Milliseconds $ClickGapMs
    }
}

# 끌기. "x1,y1,x2,y2" 비율. 누른 채 여러 걸음에 나눠 움직이고 뗀다 -
# 한 번에 옮기면 게임이 누름과 뗌만 보고 끌기로 안 읽는다.
if ($Drag -ne "") {
    $d = $Drag.Split(",")
    $x1 = $o.X + [int]([double]$d[0] * $w); $y1 = $o.Y + [int]([double]$d[1] * $ht)
    $x2 = $o.X + [int]([double]$d[2] * $w); $y2 = $o.Y + [int]([double]$d[3] * $ht)
    Write-Host ("끌기 {0},{1} -> {2},{3}" -f $x1, $y1, $x2, $y2)
    [void][Win]::SetCursorPos($x1, $y1)
    Start-Sleep -Milliseconds 300
    [Win]::mouse_event(0x0002, 0, 0, 0, [IntPtr]::Zero)
    Start-Sleep -Milliseconds 150
    for ($i = 1; $i -le $DragSteps; $i++) {
        [void][Win]::SetCursorPos(
            $x1 + [int](($x2 - $x1) * $i / $DragSteps),
            $y1 + [int](($y2 - $y1) * $i / $DragSteps))
        Start-Sleep -Milliseconds $DragStepMs
    }
    # 튕기려면 멈추지 않고 바로 떼야 한다. 여기서 쉬면 속도가 0 이 된다.
    [Win]::mouse_event(0x0004, 0, 0, 0, [IntPtr]::Zero)
    Start-Sleep -Milliseconds 400
}

Start-Sleep -Milliseconds $SettleMs

# 찍기 직전에 게임이 아직 살아 있는지 본다. 죽은 뒤에 찍으면 그 자리에
# 있던 다른 창이 찍히는데, 그림만 보고는 그 사실을 알 수 없다.
$p.Refresh()
if ($p.HasExited) { Write-Error ("게임이 먼저 꺼졌다 (종료코드 {0})" -f $p.ExitCode); exit 2 }
[void][Win]::SetForegroundWindow($h)
Start-Sleep -Milliseconds 400

Add-Type -AssemblyName System.Drawing
$bmp = New-Object System.Drawing.Bitmap $w, $ht
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($o.X, $o.Y, 0, 0, (New-Object System.Drawing.Size $w, $ht))
$outPath = if ([System.IO.Path]::IsPathRooted($Out)) { $Out } else { Join-Path $root $Out }
$bmp.Save($outPath, [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()

Get-Process cs -ErrorAction SilentlyContinue | Stop-Process -Force
Write-Host "찍었다: $outPath"
