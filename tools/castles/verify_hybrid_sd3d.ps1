param([string]$Executable='proj.win32/Debug.win32/cs.hybrid-sd3d.exe',[int[]]$Heights=@(850,1069,1280,1408))
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$keys=@('CS_CASTLE_REVIEW_PATH','CS_HYBRID_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 foreach($height in $Heights){
  $review=Join-Path $root "output/hybrid-sd3d-$height"
  New-Item -ItemType Directory -Force $review | Out-Null
  Set-Content (Join-Path $review 'phases.log') ''
  $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
  $env:CS_HYBRID_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT=[string]$height
  $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
  $limit=[DateTime]::UtcNow.AddSeconds(70)
  do {
   Start-Sleep -Milliseconds 300
   $log=Get-Content (Join-Path $review 'phases.log') -Raw
   if($log -match 'FAIL'){throw $log}
   if($log -match 'PASS hybrid UI review complete'){break}
   if($process.HasExited){throw "Review exited: $height"}
  } while([DateTime]::UtcNow -lt $limit)
  if($log -notmatch 'PASS hybrid UI review complete'){throw "Review timeout: $height"}
  if((Get-ChildItem $review -Filter '*.png').Count -lt 12){throw 'Missing UI captures'}
  "PASS hybrid SD 3D 640 x $height";$log
  Stop-Process -Id $process.Id;$process=$null
 }
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
