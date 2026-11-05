param([string]$Executable='proj.win32/Debug.win32/cs.lobby-castle-debug.exe',[int]$Height=1408)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root "output/lobby-castle-debug-$Height"
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_LOBBY_CASTLE_DEBUG_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try{
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_LOBBY_CASTLE_DEBUG_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT=[string]$Height
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $limit=[DateTime]::UtcNow.AddSeconds(120)
 do{
  Start-Sleep -Milliseconds 300
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS lobby castle debug complete'){break}
  if($process.HasExited){throw 'Review process exited'}
 }while([DateTime]::UtcNow -lt $limit)
 if($log -notmatch 'PASS lobby castle debug complete'){throw 'Review timeout'}
 if(([regex]::Matches($log,'PASS castle debug capture')).Count -ne 10){throw 'Missing castle debug captures'}
 if($log -notmatch 'PASS castle debug restored'){throw 'Missing restore check'}
 "PASS all ten castle previews and save restoration: 640 x $Height"
}finally{
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
