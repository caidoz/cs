param([string]$Executable='proj.win32/Debug.win32/cs.shop-spec.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/shop-spec-review'
New-Item -ItemType Directory -Force $review | Out-Null
Set-Content (Join-Path $review 'phases.log') ''
$oldPath=$env:CS_CASTLE_REVIEW_PATH
$oldMode=$env:CS_SHOP_SPEC_REVIEW
$process=$null
try {
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_SHOP_SPEC_REVIEW='1'
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $limit=[DateTime]::UtcNow.AddSeconds(40)
 do {
  Start-Sleep -Milliseconds 400
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS shop spec review complete'){break}
  if($process.HasExited){throw 'Review exited'}
 } while([DateTime]::UtcNow -lt $limit)
 if($log -notmatch 'PASS shop spec review complete'){throw 'Review timeout'}
 $log
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 $env:CS_CASTLE_REVIEW_PATH=$oldPath
 $env:CS_SHOP_SPEC_REVIEW=$oldMode
}

