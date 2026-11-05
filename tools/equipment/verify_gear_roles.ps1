param([string]$Executable='proj.win32/Debug.win32/cs.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/gear-role-review'
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_GEAR_ROLE_REVIEW')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_GEAR_ROLE_REVIEW='1'
 $process=Start-Process (Resolve-Path (Join-Path $root $Executable)).Path -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $deadline=[DateTime]::UtcNow.AddSeconds(60)
 do {
  Start-Sleep -Milliseconds 400
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS gear role review complete'){break}
  if($process.HasExited){throw "Gear role review exited early: $($process.ExitCode)`n$log"}
 } while([DateTime]::UtcNow -lt $deadline)
 foreach($check in @(
   'gear role axes from bag',
   'gem socket amplifies primary axis',
   'per hero warehouse lines',
   'run shop swaps to hero line',
   'crew add no hero hp',
   'hero dual gauge stands alone',
   'hero down ends the run',
   'gear role review complete')) {
  if($log -notmatch [regex]::Escape("PASS $check")){throw "Missing check: $check`n$log"}
 }
 $log
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
