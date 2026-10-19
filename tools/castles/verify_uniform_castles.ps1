param([string]$Executable='proj.win32/Debug.win32/cs.uniform-castles-preview.exe',[int]$Height=1400)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root "output/uniform-castles-review-$Height"
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_UNIFORM_CASTLE_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT','CS_ROOM_COVER_REVIEW')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_UNIFORM_CASTLE_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT="$Height"
 $env:CS_ROOM_COVER_REVIEW='1'
 $process=Start-Process (Resolve-Path (Join-Path $root $Executable)).Path -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $deadline=[DateTime]::UtcNow.AddSeconds(100)
 do {
  Start-Sleep -Milliseconds 500
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if(($log -match 'PASS all uniform castle stages and mixed parts') -and
     ([regex]::Matches($log,'PASS uniform capture')).Count -eq 70){break}
  if($process.HasExited){throw 'Uniform preview exited early'}
 } while([DateTime]::UtcNow -lt $deadline)
 if($log -notmatch 'PASS all uniform castle stages and mixed parts'){throw 'Uniform castle review timed out'}
 if(([regex]::Matches($log,'PASS uniform castle placement')).Count -ne 35){throw 'Expected 35 successful placements'}
 if(([regex]::Matches($log,'PASS uniform capture')).Count -ne 70){throw 'Expected 70 successful captures'}
 if(([regex]::Matches($log,'PASS uniform room reveal')).Count -ne 35){throw 'Expected 35 room reveal checks'}
 'PASS five castles, six stages plus mixed parts each, native sprite bounds and actor/muzzle/deck anchors, room reveal; 70 captures'
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
