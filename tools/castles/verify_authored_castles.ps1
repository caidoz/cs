param([string]$Executable='proj.win32/Debug.win32/cs.authored-castles.exe',[int[]]$Heights=@(850,1069,1280,1408))
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$keys=@('CS_CASTLE_REVIEW_PATH','CS_HYBRID_FLEET_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 foreach($height in $Heights){
  $review=Join-Path $root "output/authored-castles-$height"
  New-Item -ItemType Directory -Force $review | Out-Null
  Set-Content (Join-Path $review 'phases.log') ''
  $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
  $env:CS_HYBRID_FLEET_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT=[string]$height
  $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
  $limit=[DateTime]::UtcNow.AddSeconds(120)
  do {
   Start-Sleep -Milliseconds 350
   $log=Get-Content (Join-Path $review 'phases.log') -Raw
   if($log -match 'FAIL'){throw $log}
   if($log -match 'PASS fleet lobby review complete'){break}
   if($process.HasExited){throw "Review exited: $height"}
  } while([DateTime]::UtcNow -lt $limit)
  if($log -notmatch 'PASS fleet lobby review complete'){throw "Review timeout: $height"}
  if(([regex]::Matches($log,'PASS fleet lobby sockets and facade')).Count -ne 40){throw 'Missing socket checks'}
  if((Get-ChildItem $review -Filter '*.png').Count -ne 40){throw 'Missing lobby captures'}
  "PASS 10 authored castles x 4 states: native lobby 640 x $height"
  Stop-Process -Id $process.Id;$process=$null
 }
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
