param([string]$Executable='proj.win32/Debug.win32/cs.allies-balance.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/ally-balance-review'
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_ALLIES_BALANCE_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 Set-Content (Join-Path $review 'phases.log') ''
 Set-Content (Join-Path $review 'details.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_ALLIES_BALANCE_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT='1400'
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $deadline=[DateTime]::UtcNow.AddSeconds(55)
 do {
  Start-Sleep -Milliseconds 400
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw ($log+(Get-Content (Join-Path $review 'details.log') -Raw))}
  if($log -match 'PASS ally balance review complete'){break}
  if($process.HasExited){throw 'Ally balance review exited early'}
 } while([DateTime]::UtcNow -lt $deadline)
 if($log -notmatch 'PASS 64 placements attack timings 61 unique abilities 183 synergies dedup caps and cleanup' -or $log -notmatch 'PASS ally balance review complete'){throw "Incomplete balance review: $log"}
 $log
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
