param([string]$Executable='proj.win32/Debug.win32/cs.castle-final.exe',[int[]]$Heights=@(850,960,1136,1408))
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$keys=@('CS_CASTLE_REVIEW_PATH','CS_CASTLE_FINAL_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 foreach($height in $Heights){
  $review=Join-Path $root "output/castle-final-$height"
  New-Item -ItemType Directory -Force $review | Out-Null
  Set-Content (Join-Path $review 'phases.log') ''
  $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
  $env:CS_CASTLE_FINAL_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT=[string]$height
  $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
  $limit=[DateTime]::UtcNow.AddSeconds(45)
  do {
   Start-Sleep -Milliseconds 300
   $log=Get-Content (Join-Path $review 'phases.log') -Raw
   if($log -match 'FAIL'){throw $log}
   if($log -match 'PASS castle final review complete'){break}
   if($process.HasExited){throw "Review exited $height"}
  } while([DateTime]::UtcNow -lt $limit)
  if($log -notmatch 'PASS castle final review complete'){throw "Review timeout $height"}
  "640 x $height";$log
  Stop-Process -Id $process.Id;$process=$null
 }
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
