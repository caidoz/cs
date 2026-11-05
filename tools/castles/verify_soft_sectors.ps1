param([string]$Executable='proj.win32/Debug.win32/cs.soft-sectors.exe',[int]$Height=1408)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root "output/soft-sectors-$Height"
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_SOFT_SECTORS_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try{
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_SOFT_SECTORS_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT=[string]$Height
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $limit=[DateTime]::UtcNow.AddSeconds(120)
 do{
  Start-Sleep -Milliseconds 300
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS soft sectors complete'){break}
  if($process.HasExited){throw 'Review process exited'}
 }while([DateTime]::UtcNow -lt $limit)
 if($log -notmatch 'PASS soft sectors complete'){throw 'Review timeout'}
 if(([regex]::Matches($log,'PASS soft castle capture')).Count -ne 40){throw 'Missing forty castle captures'}
 "PASS ten castles, base/max closed/open, sector/resident registration: 640 x $Height"
}finally{
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
