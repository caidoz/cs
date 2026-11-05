param([string]$Executable='proj.win32/Debug.win32/cs.regions-sd3d.exe',[int]$Height=1408)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root "output/all-regions-$Height"
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_ALL_REGION_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try{
 Set-Content (Join-Path $review 'phases.log') ''
 Set-Content (Join-Path $review 'tone-shader.txt') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_ALL_REGION_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT=[string]$Height
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $limit=[DateTime]::UtcNow.AddSeconds(120)
 do{
  Start-Sleep -Milliseconds 300
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS all region review complete'){break}
  if($process.HasExited){throw 'Review process exited'}
 }while([DateTime]::UtcNow -lt $limit)
 if($log -notmatch 'PASS all region review complete'){throw 'Review timeout'}
 if(([regex]::Matches($log,'PASS region capture')).Count -ne 30){throw 'Missing region captures'}
 if((Get-Content (Join-Path $review 'tone-shader.txt') -Raw) -notmatch 'PASS foreground shader'){throw 'Foreground shader did not compile or uniforms were missing'}
 "PASS all 15 regions, two scroll phases, five textures each: 640 x $Height"
}finally{
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
