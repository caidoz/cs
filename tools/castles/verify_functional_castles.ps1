param([string]$Executable='proj.win32/Debug.win32/cs.functional-castles.exe',[int]$Height=1408)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root "output/functional-castles-$Height"
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_FUNCTIONAL_CASTLES_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try{
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_FUNCTIONAL_CASTLES_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT=[string]$Height
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $limit=[DateTime]::UtcNow.AddSeconds(180)
 do{
  Start-Sleep -Milliseconds 300
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS functional castles complete'){break}
  if($process.HasExited){throw 'Review process exited'}
 }while([DateTime]::UtcNow -lt $limit)
 if($log -notmatch 'PASS functional castles complete'){throw 'Review timeout'}
 if(([regex]::Matches($log,'PASS functional capture')).Count -ne 20){throw 'Missing captures'}
 if(([regex]::Matches($log,'PASS lobby cannon impact')).Count -ne 10){throw 'Missing impacts'}
 "PASS ten functional castles, crowd, cannon hits and save isolation: 640 x $Height"
}finally{
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
