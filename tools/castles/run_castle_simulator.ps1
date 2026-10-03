$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$directory = Join-Path $root 'proj.win32/Debug.castle.simulator'
$simulatorExe = Join-Path $directory 'cs.exe'
$msbuild = 'C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe'
if (!(Test-Path -LiteralPath $msbuild)) { throw "MSBuild was not found: $msbuild" }

# Build into a separate output directory: the running game also locks its DLLs.
$running = Get-Process -Name 'cs' -ErrorAction SilentlyContinue |
    Where-Object { $_.Path -eq $simulatorExe } |
    Select-Object -First 1
if ($running) {
    Write-Host "Castle simulator is already running (PID $($running.Id))."
    return
}
& $msbuild (Join-Path $root 'proj.win32/cs.vcxproj') '/t:Build' '/p:Configuration=Debug' '/p:Platform=Win32' "/p:OutDir=$directory\" '/m:4' '/v:minimal' '/nologo'
if ($LASTEXITCODE -ne 0) { throw "Castle simulator build failed (exit $LASTEXITCODE)." }
if (!(Test-Path -LiteralPath $simulatorExe)) { throw "Simulator executable was not produced: $simulatorExe" }

$oldValue = [Environment]::GetEnvironmentVariable('CS_CASTLE_DEBUG', 'Process')
try {
    [Environment]::SetEnvironmentVariable('CS_CASTLE_DEBUG', '1', 'Process')
    $process = Start-Process -FilePath $simulatorExe -WorkingDirectory $directory -WindowStyle Normal -PassThru
    Write-Host "Castle simulator started (PID $($process.Id)): $simulatorExe"
} finally {
    [Environment]::SetEnvironmentVariable('CS_CASTLE_DEBUG', $oldValue, 'Process')
}
