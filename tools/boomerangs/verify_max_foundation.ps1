param([string]$Executable='proj.win32/Debug.win32/cs.max-weapon.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/max-weapon-review'
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_MAX_WEAPON_REVIEW','CS_SHOP_OFFER_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_MAX_WEAPON_REVIEW='1';$env:CS_SHOP_OFFER_REVIEW='1'
 $env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT='1400'
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $deadline=[DateTime]::UtcNow.AddSeconds(55)
 do {
  Start-Sleep -Milliseconds 400
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS Max foundation review complete' -and $log -match 'PASS Max capture'){break}
  if($process.HasExited){throw 'Max review exited early'}
 } while([DateTime]::UtcNow -lt $deadline)
 foreach($check in @('four rewards required weapon optional crew persistent equipment and run cleanup','boomerang hit once return pause target loss and readiness','live Max throw','live Max contact damage and returning','live Max ready after return','repeated automatic Max basic attack','Max capture','Max foundation review complete')) {
  if($log -notmatch [regex]::Escape("PASS $check")){throw "Missing check: $check`n$log"}
 }
 $log
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
