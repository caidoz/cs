param([string]$Executable='proj.win32/Debug.win32/cs.castle-parts-complete.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/castle-upgrade-parts-review'
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_CASTLE_MODULE_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_CASTLE_MODULE_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT='850'
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $limit=[DateTime]::UtcNow.AddSeconds(150)
 do {
  Start-Sleep -Milliseconds 400
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS 120 castle upgrade combinations complete'){break}
  if($process.HasExited){throw 'Review exited'}
 } while([DateTime]::UtcNow -lt $limit)
 if($log -notmatch 'PASS 120 castle upgrade combinations complete'){throw 'Upgrade composition review timeout'}
 if(([regex]::Matches($log,'PASS stable hull deck hero and axle placement')).Count -ne 120){throw 'Missing placement checks'}
 if((Get-ChildItem $review -Filter '*.png').Count -ne 120){throw 'Missing composition captures'}
 'PASS 120 rendered combinations and fixed hull/deck/hero/axle registration'
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
