param([string]$Executable='proj.win32/Debug.win32/cs.room-facade-v2-preview.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/room-facade-v2-review'
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_ROOM_COVER_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{}
foreach($key in $keys) { $saved[$key]=[Environment]::GetEnvironmentVariable($key) }
$process=$null
try {
    Set-Content (Join-Path $review 'phases.log') ''
    $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
    $env:CS_ROOM_COVER_REVIEW='1'
    $env:CS_BATTLE_MENU_REVIEW='1'
    $env:CS_BATTLE_MENU_HEIGHT='900'
    $process=Start-Process (Resolve-Path (Join-Path $root $Executable)).Path -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
    $deadline=[DateTime]::UtcNow.AddSeconds(45)
    do {
        Start-Sleep -Milliseconds 400
        $log=Get-Content (Join-Path $review 'phases.log') -Raw
        if($log -match 'FAIL') { throw $log }
        if($log -match 'PASS room cover review') { break }
        if($process.HasExited) { throw 'Preview exited early' }
    } while([DateTime]::UtcNow -lt $deadline)
    if($log -notmatch 'PASS room cover review') { throw 'Review timed out' }
    foreach($check in @('held circular reveal','released facade restored')) {
        if(([regex]::Matches($log,"PASS $check")).Count -ne 1) { throw "Missing check: $check" }
    }
    foreach($castle in @(1)) { foreach($state in 'closed','held','released') {
        if(!(Test-Path (Join-Path $review "castle-$castle-$state.png"))) { throw 'Missing capture' }
    } }
    'PASS first-castle unified facade, doubled reveal radius, release restoration and three captures'
} finally {
    if($process -and !$process.HasExited) { Stop-Process -Id $process.Id }
    foreach($key in $keys) { [Environment]::SetEnvironmentVariable($key,$saved[$key]) }
}
