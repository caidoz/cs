param([string]$Executable='proj.win32/Debug.win32/cs.battle-menu48-preview.exe',[int]$ScreenHeight=725)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/battle-menu-flow-review'
New-Item -ItemType Directory -Force $review | Out-Null
$oldPath=$env:CS_CASTLE_REVIEW_PATH
$oldMode=$env:CS_BATTLE_MENU_REVIEW
$oldHeight=$env:CS_BATTLE_MENU_HEIGHT
$process=$null
try {
    Set-Content (Join-Path $review 'phases.log') ''
    $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
    $env:CS_BATTLE_MENU_REVIEW='1'
    $env:CS_BATTLE_MENU_HEIGHT="$ScreenHeight"
    $process=Start-Process (Resolve-Path (Join-Path $root $Executable)).Path -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
    $deadline=[DateTime]::UtcNow.AddSeconds(50)
    do {
        Start-Sleep -Milliseconds 250
        $log=Get-Content (Join-Path $review 'phases.log') -Raw
        if($log -match 'FAIL') { throw "Battle menu verification failed:`n$log" }
        if($log -match 'PASS battle menu flow review') { break }
        if($process.HasExited) { throw "Preview exited: $($process.ExitCode)" }
    } while([DateTime]::UtcNow -lt $deadline)
    foreach($check in @('star footer button drag tap and cancel','preparation outside tap and back stay in run','precombat abandon blocked','exit unlocks after combat starts','explicit combat abandon','warehouse drag into grid','initial shop before battle','world descends with full battle grid','pause retains compact combat menu','world returns for shopping','centred 48px grid and four warehouse rows','battle menu flow review')) {
        if($log -notmatch [regex]::Escape("PASS $check")) { throw "Missing check: $check" }
    }
    if(([regex]::Matches($log,'PASS battle menu capture')).Count -ne 6) { throw 'Expected six menu captures' }
    "PASS 48px cells, warehouse drag/full height, initial shop, compact combat, pause and castle 10; six 640x$ScreenHeight screens"
} finally {
    if($process -and !$process.HasExited) { Stop-Process -Id $process.Id }
    $env:CS_CASTLE_REVIEW_PATH=$oldPath
    $env:CS_BATTLE_MENU_REVIEW=$oldMode
    $env:CS_BATTLE_MENU_HEIGHT=$oldHeight
}
