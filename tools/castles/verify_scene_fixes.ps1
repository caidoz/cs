param([string]$Executable='proj.win32/Debug.win32/cs.scene-fixes.exe',[int]$Height=1408)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root "output/scene-fixes-$Height"
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_SCENE_FIX_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try{
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_SCENE_FIX_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT=[string]$Height
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $limit=[DateTime]::UtcNow.AddSeconds(90)
 do{
  Start-Sleep -Milliseconds 300
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS scene fixes review complete'){break}
  if($process.HasExited){throw 'Review process exited'}
 }while([DateTime]::UtcNow -lt $limit)
 if($log -notmatch 'PASS scene fixes review complete'){throw 'Review timeout'}
 foreach($check in @('original castle grid and cell alignment','expanded debug controls accessible','scene capture')){
  if(([regex]::Matches($log,"PASS $check")).Count -ne 10){throw "Missing ten checks: $check"}
 }
 "PASS ten original castle grids, debug toggle/touch regions, background scroll phases: 640 x $Height"
}finally{
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
