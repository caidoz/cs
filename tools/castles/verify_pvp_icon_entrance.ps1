param([string]$Executable='proj.win32/Debug.win32/cs.pvp-icons.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/pvp-icon-entrance-review'
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_PVP_ICON_ENTRANCE_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_PVP_ICON_ENTRANCE_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT='1400'
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $deadline=[DateTime]::UtcNow.AddSeconds(55)
 do {
  Start-Sleep -Milliseconds 400
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS all ten current icon entrances'){break}
  if($process.HasExited){throw 'PVP icon review exited early'}
 } while([DateTime]::UtcNow -lt $deadline)
 if($log -notmatch 'PASS all ten current icon entrances'){throw 'PVP icon entrance review timed out'}
 if(([regex]::Matches($log,'PASS entrance icon IDs mirrored wheels and bounds')).Count -ne 10){throw 'Expected ten icon layout checks'}
 if(([regex]::Matches($log,'PASS entrance icon capture')).Count -ne 10){throw 'Expected ten entrance captures'}
 'PASS all ten current icons on both sides, mirrored opponent, shared wheel baseline and screen bounds; ten captures'
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
