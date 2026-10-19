param([string]$Executable='proj.win32/Debug.win32/cs.ninth-modular-preview.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/ninth-upgrades-review'
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_NINTH_UPGRADE_REVIEW','CS_ROOM_COVER_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{}
foreach($key in $keys) { $saved[$key]=[Environment]::GetEnvironmentVariable($key) }
$process=$null
try {
    Set-Content (Join-Path $review 'phases.log') ''
    $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
    $env:CS_NINTH_UPGRADE_REVIEW='1'
    $env:CS_ROOM_COVER_REVIEW='1'
    $env:CS_BATTLE_MENU_REVIEW='1'
    $env:CS_BATTLE_MENU_HEIGHT='900'
    $process=Start-Process (Resolve-Path (Join-Path $root $Executable)).Path -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
    $deadline=[DateTime]::UtcNow.AddSeconds(75)
    do {
        Start-Sleep -Milliseconds 400
        $log=Get-Content (Join-Path $review 'phases.log') -Raw
        if($log -match 'FAIL') { throw $log }
        if($log -match 'PASS all ninth upgrades and mixed assemblies') { break }
        if($process.HasExited) { throw 'Upgrade preview exited early' }
    } while([DateTime]::UtcNow -lt $deadline)
    if($log -notmatch 'PASS all ninth upgrades and mixed assemblies') { throw 'Upgrade review timed out' }
    foreach($check in @('upgrade assets geometry and half width','upgrade room reveal','upgrade rolling wheels')) {
        if(([regex]::Matches($log,"PASS $check")).Count -ne 9) { throw "Expected nine successful checks: $check" }
    }
    if(([regex]::Matches($log,'PASS upgrade capture')).Count -ne 18) { throw 'Expected eighteen captures' }
    foreach($level in 0..5) { foreach($state in 'closed','open') {
        if(!(Test-Path (Join-Path $review "stage-$level-$state.png"))) { throw 'Missing stage capture' }
    } }
    foreach($mix in 0..2) { foreach($state in 'closed','open') {
        if(!(Test-Path (Join-Path $review "mixed-$mix-$state.png"))) { throw 'Missing mixed capture' }
    } }
    if($log -notmatch 'PASS ninth deployed deck positions') { throw 'Missing deployed companion position check' }
    'PASS ninth castle, nine floors, six stages, three mixed assemblies, 55-percent viewport width, rotating wheels, room reveal, resource bounds and 18 captures'
} finally {
    if($process -and !$process.HasExited) { Stop-Process -Id $process.Id }
    foreach($key in $keys) { [Environment]::SetEnvironmentVariable($key,$saved[$key]) }
}
