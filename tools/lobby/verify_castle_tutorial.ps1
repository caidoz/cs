param([string]$Executable='proj.win32/Debug.win32/cs.exe',[int[]]$Heights=@(850,1069,1280,1408))
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$keys=@('CS_CASTLE_REVIEW_PATH','CS_TUTORIAL_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try{
 foreach($height in $Heights){
  $review=Join-Path $root "output/castle-tutorial-$height"
  New-Item -ItemType Directory -Force $review|Out-Null
  $fixtureSave=Join-Path $review 'serverdb.dat'
  if(Test-Path -LiteralPath $fixtureSave){Remove-Item -LiteralPath $fixtureSave}
  $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
  $env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT=[string]$height
  foreach($mode in @('fresh','resume','done')){
   $env:CS_TUTORIAL_REVIEW=$mode
   Set-Content (Join-Path $review 'phases.log') ''
   $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
   $limit=[DateTime]::UtcNow.AddSeconds(90)
   do{
    Start-Sleep -Milliseconds 250
    $log=Get-Content (Join-Path $review 'phases.log') -Raw
    if($log -match 'FAIL'){throw $log}
    if($log -match 'PASS tutorial complete'){break}
    if($process.HasExited){throw "Review exited: $mode"}
   }while([DateTime]::UtcNow-lt $limit)
   if($log-notmatch 'PASS tutorial complete'){throw "Review timeout: $mode"}
   Copy-Item (Join-Path $review 'phases.log') (Join-Path $review "$mode.log")
   Stop-Process -Id $process.Id;$process=$null
   "PASS tutorial $mode at 640 x $height"
  }
 }
}finally{
 if($process-and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
