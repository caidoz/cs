param([string]$Executable='proj.win32/Debug.win32/cs.combat-anchors.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/stage-combat-review'
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_STAGE_COMBAT_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_STAGE_COMBAT_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT='1400'
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $deadline=[DateTime]::UtcNow.AddSeconds(55)
 do {
  Start-Sleep -Milliseconds 400
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS stage combat review complete' -and $log -match 'PASS stage combat capture'){break}
  if($process.HasExited){throw 'Combat review exited early'}
 } while([DateTime]::UtcNow -lt $deadline)
 if($log -notmatch 'PASS stage combat review complete' -or $log -notmatch 'PASS stage combat capture'){throw 'Combat review timed out'}
 $log
 Get-Content (Join-Path $review 'impacts.log')
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
