param([string]$Executable='proj.win32/Debug.win32/cs.fixed-width-preview.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/fixed-width-review'
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_FIXED_WIDTH_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_FIXED_WIDTH_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT='900'
 $process=Start-Process (Resolve-Path (Join-Path $root $Executable)).Path -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $deadline=[DateTime]::UtcNow.AddSeconds(75)
 do {
  Start-Sleep -Milliseconds 400
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS all castle widths and heights'){break}
  if($process.HasExited){throw 'Fixed width preview exited early'}
 } while([DateTime]::UtcNow -lt $deadline)
 if($log -notmatch 'PASS all castle widths and heights'){throw 'Fixed width review timed out'}
 if(([regex]::Matches($log,'PASS fixed width and growing height')).Count -ne 10){throw 'Expected ten width checks'}
 if($log -notmatch 'PASS tall castle vertical pan'){throw 'Missing vertical pan check'}
 if(([regex]::Matches($log,'PASS width capture')).Count -ne 11){throw 'Expected eleven captures'}
 $rows=@(Import-Csv (Join-Path $review 'sizes.csv'))
 if($rows.Count -ne 10){throw 'Expected ten size rows'}
 $previousHeight=0.0
 foreach($row in $rows){
  if([Math]::Abs([double]$row.width-[double]$rows[0].width) -gt .5 -or [double]$row.height -le $previousHeight){throw 'Width changed or height did not increase'}
  $previousHeight=[double]$row.height
 }
 $rows | Format-Table
 'PASS all ten castles: fixed width, increasing height, rail contact and vertical pan to the top'
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
