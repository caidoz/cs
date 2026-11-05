param([string]$Executable='proj.win32/Debug.win32/cs.room-upgrades.exe',[int[]]$Heights=@(850,1069,1280,1408),[switch]$NoCrowd)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$keys=@('CS_CASTLE_REVIEW_PATH','CS_ROOM_UPGRADE_REVIEW','CS_ROOM_UPGRADE_REVIEW_NO_CROWD','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try{
 foreach($height in $Heights){
  $folder=if($NoCrowd){"output/room-integrated-empty-$height"}else{"output/room-upgrades-$height"}
  $review=Join-Path $root $folder
  New-Item -ItemType Directory -Force $review | Out-Null
  Set-Content (Join-Path $review 'phases.log') ''
  $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
  $env:CS_ROOM_UPGRADE_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT=[string]$height
  if($NoCrowd){$env:CS_ROOM_UPGRADE_REVIEW_NO_CROWD='1'}else{$env:CS_ROOM_UPGRADE_REVIEW_NO_CROWD=$null}
  $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
  $limit=[DateTime]::UtcNow.AddSeconds(180)
  do{
   Start-Sleep -Milliseconds 300
   $log=Get-Content (Join-Path $review 'phases.log') -Raw
   if($log -match 'FAIL'){throw $log}
   if($log -match 'PASS room upgrades complete'){break}
   if($process.HasExited){throw "Review exited at height $height"}
  }while([DateTime]::UtcNow -lt $limit)
  if($log -notmatch 'PASS room upgrades complete'){throw "Review timeout at height $height"}
  if(([regex]::Matches($log,'PASS facility level capture')).Count -ne 60){throw 'Missing upgrade captures'}
  if(([regex]::Matches($log,'PASS facility atlas level and shader')).Count -ne 60){throw 'Incorrect atlas/level/shader'}
  if(([regex]::Matches($log,'PASS final castle independent facility')).Count -ne 5){throw 'Final castle facilities are not independent'}
  "PASS 640 x ${height}: ten castles, six stages, live NPCs, shader and save isolation"
  if(!$process.HasExited){Stop-Process -Id $process.Id};$process=$null
 }
}finally{
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
