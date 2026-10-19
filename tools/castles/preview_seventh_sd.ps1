param([string]$Executable='proj.win32/Debug.win32/cs.seventh-modular-preview.exe',[ValidateRange(0,5)][int]$Stage=0)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$keys=@('CS_CASTLE_REVIEW_PATH','CS_SEVENTH_SD_SANDBOX','CS_SEVENTH_SD_STAGE','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{}
foreach($key in $keys) { $saved[$key]=[Environment]::GetEnvironmentVariable($key) }
try {
    $review=Join-Path $root 'output/seventh-sd-interactive'
    New-Item -ItemType Directory -Force $review | Out-Null
    $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
    $env:CS_SEVENTH_SD_SANDBOX='1'
    $env:CS_SEVENTH_SD_STAGE=[string]$Stage
    $env:CS_BATTLE_MENU_REVIEW='1'
    $env:CS_BATTLE_MENU_HEIGHT='900'
    # This launcher is explicitly for the user's interactive visual test.
    $process=Start-Process (Resolve-Path (Join-Path $root $Executable)).Path -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Normal -PassThru
    "Interactive seventh castle preview launched (PID $($process.Id)). Hold the facade to see the room."
} finally {
    foreach($key in $keys) { [Environment]::SetEnvironmentVariable($key,$saved[$key]) }
}
