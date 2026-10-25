param([string]$Executable='proj.win32/Debug.win32/cs.allies-audit.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/hero-allies-audit'
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_HERO_ALLIES_AUDIT','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_HERO_ALLIES_AUDIT='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT='1400'
 $process=Start-Process (Join-Path $root $Executable) -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $deadline=[DateTime]::UtcNow.AddSeconds(50)
 do {
  Start-Sleep -Milliseconds 400
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS existing 64 allies audit complete' -and ([regex]::Matches($log,'PASS allies audit capture')).Count -eq 2){break}
  if($process.HasExited){throw 'Allies audit exited early'}
 } while([DateTime]::UtcNow -lt $deadline)
 if($log -notmatch 'PASS existing 64 allies audit complete' -or ([regex]::Matches($log,'PASS allies audit capture')).Count -ne 2){throw "Incomplete allies audit: $log"}
 $actual=@(Import-Csv (Join-Path $review 'runtime-catalog.tsv') -Delimiter "`t" -Encoding UTF8)
 $expected=@(Import-Csv (Join-Path $root 'reports/hero_allies_64/catalog.tsv') -Delimiter "`t" -Encoding UTF8)
 if($actual.Count -ne 64 -or $expected.Count -ne 64){throw 'Expected 64 live and source records'}
 foreach($row in $actual) {
  $reference=$expected[[int]$row.crew_id]
  foreach($field in @('crew_id','npc_id','cmf_id','name','grid','skill1_id','skill2_id','skill3_id','base_cooldown_frames','attack_cooldown_frames','ability_cooldown_frames')) {
   if($row.$field -cne $reference.$field){throw "Live catalog differs: $($row.crew_id) $field live=$($row.$field) source=$($reference.$field)"}
  }
 }
 $log
 'PASS all 64 live names, IDs, sprites, sizes, skills and cooldowns match source catalog'
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
