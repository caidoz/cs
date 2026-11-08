param([string]$Executable='proj.win32/Debug.win32/cs.exe',[int[]]$Heights=@(850,1069,1280,1408))
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$keys=@('CS_CASTLE_REVIEW_PATH','CS_MENU_RENEWAL_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try{
 foreach($height in $Heights){
  $folder=Join-Path $root "output/menu-renewal-$height"
  New-Item -ItemType Directory -Force $folder|Out-Null
  Set-Content (Join-Path $folder 'phases.log') ''
  $env:CS_CASTLE_REVIEW_PATH=$folder.Replace('\','/')+'/'
  $env:CS_MENU_RENEWAL_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT=[string]$height
  $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
  $limit=[DateTime]::UtcNow.AddSeconds(75)
  do{
   Start-Sleep -Milliseconds 400
   $log=Get-Content (Join-Path $folder 'phases.log') -Raw
   if($log -match 'FAIL'){throw $log}
   if($log -match 'PASS menu renewal complete'){break}
   if($process.HasExited){throw "Review exited: $height"}
  }while([DateTime]::UtcNow -lt $limit)
  if($log -notmatch 'PASS menu renewal complete'){throw "Review timeout: $height"}
  "PASS menu renewal 640 x $height"
  Stop-Process -Id $process.Id;$process=$null
 }
}finally{
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
