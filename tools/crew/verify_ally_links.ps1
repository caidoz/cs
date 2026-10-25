param([string]$Executable='proj.win32/Debug.win32/cs.ally-links.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/ally-links-review'
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_ALLY_LINK_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 Set-Content (Join-Path $review 'phases.log') ''
 Set-Content (Join-Path $review 'activations.tsv') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_ALLY_LINK_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT='1400'
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $deadline=[DateTime]::UtcNow.AddSeconds(55)
 do {
  Start-Sleep -Milliseconds 400
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS three hero ally links complete' -and ([regex]::Matches($log,'PASS hero ally link capture')).Count -eq 3){break}
  if($process.HasExited){throw 'Ally link review exited early'}
 } while([DateTime]::UtcNow -lt $deadline)
 foreach($check in @('three approved companions placed','link clocks ready through actual tick model','paused ally link clocks','hero repair heal supply and support projectile impacts','repair heal link cooldown bars rendered','run exit clears ally links','hero ally link capture')) {
  if(([regex]::Matches($log,[regex]::Escape("PASS $check"))).Count -ne 3){throw "Expected three checks: $check`n$log"}
 }
 if($log -notmatch 'PASS three hero ally links complete'){throw 'Ally link review incomplete'}
 $log
 'hero / repairs / smith links / heals / support shots / support impacts'
 Get-Content (Join-Path $review 'activations.tsv')
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
