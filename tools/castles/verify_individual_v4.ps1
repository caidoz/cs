param([int]$Height=900,[switch]$RoomReveal,[switch]$InteriorSync,[string]$Executable='proj.win32/Debug.win32/cs.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root "output/individual-v4-review-$Height"
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_INDIVIDUAL_V4_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT','CS_ROOM_COVER_REVIEW','CS_CASTLE_INTERIOR_SYNC_REVIEW')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_INDIVIDUAL_V4_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT="$Height"
 if($RoomReveal){$env:CS_ROOM_COVER_REVIEW='1'}else{$env:CS_ROOM_COVER_REVIEW=$null}
 if($InteriorSync){$env:CS_CASTLE_INTERIOR_SYNC_REVIEW='1'}else{$env:CS_CASTLE_INTERIOR_SYNC_REVIEW=$null}
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $deadline=[DateTime]::UtcNow.AddSeconds(55)
 do {
  Start-Sleep -Milliseconds 500
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS individual v4 all ten exteriors'){break}
  if($process.HasExited){throw 'Review process exited early'}
 } while([DateTime]::UtcNow -lt $deadline)
 if($log -notmatch 'PASS individual v4 all ten exteriors'){throw 'Review timed out'}
 foreach($check in @('placement and progression','wheels rolling')) {
  if(([regex]::Matches($log,"PASS individual $check")).Count -ne 10){throw "Expected ten checks: $check"}
 }
 if(([regex]::Matches($log,'PASS individual capture')).Count -ne 20){throw 'Expected twenty captures'}
 if(([regex]::Matches($log,'PASS uniform room dimensions and floor count')).Count -ne 10){throw 'Expected ten uniform room geometry checks'}
 if($InteriorSync) {
  foreach($check in @('castle zoom out','castle zoom in','twenty residents and intact room textures')) {
   if(([regex]::Matches($log,"PASS $check")).Count -ne 10){throw "Expected ten checks: $check"}
  }
 }
 if($RoomReveal) {
  foreach($check in @('room reveal','room closed','room persists after release','outside touch closed')) {
   if(([regex]::Matches($log,"PASS individual $check")).Count -ne 10){throw "Expected ten checks: $check"}
  }
 }
 'PASS ten exteriors, proportional growth, actor/muzzle anchors, rotating wheels, twenty captures'
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
