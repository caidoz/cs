param([string]$Executable='proj.win32/Debug.win32/cs.title-login.exe',[int]$Height=1408)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root "output/title-login-$Height"
New-Item -ItemType Directory -Force $review | Out-Null
$marker=Join-Path $review 'title-login-resume.dat'
if(Test-Path -LiteralPath $marker){Remove-Item -LiteralPath $marker}
$keys=@('CS_CASTLE_REVIEW_PATH','CS_TITLE_LOGIN_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try{
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT=[string]$Height
 foreach($mode in @('fresh','returning')){
  Set-Content (Join-Path $review 'phases.log') ''
  $env:CS_TITLE_LOGIN_REVIEW=$mode
  $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
  $limit=[DateTime]::UtcNow.AddSeconds(60)
  do{
   Start-Sleep -Milliseconds 250
   $log=Get-Content (Join-Path $review 'phases.log') -Raw
   if($log -match 'FAIL'){throw $log}
   if($log -match 'PASS title login review complete'){break}
   if($process.HasExited){throw 'Review exited'}
  }while([DateTime]::UtcNow -lt $limit)
  if($log -notmatch 'PASS title login review complete'){throw 'Review timeout'}
  Copy-Item (Join-Path $review 'phases.log') (Join-Path $review "$mode.log")
  if(!$process.HasExited){Stop-Process -Id $process.Id};$process=$null
  "PASS title ${mode}: login, loading and lobby at 640 x $Height"
 }
}finally{
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
