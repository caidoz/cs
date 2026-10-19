param([string]$Executable='proj.win32/Debug.win32/cs.map-icons-preview.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$review=Join-Path $root 'output/map-icon-resources-review'
New-Item -ItemType Directory -Force $review | Out-Null
$keys=@('CS_CASTLE_REVIEW_PATH','CS_CASTLE_MAP_ICON_REVIEW','CS_BATTLE_MENU_REVIEW','CS_BATTLE_MENU_HEIGHT')
$saved=@{};foreach($key in $keys){$saved[$key]=[Environment]::GetEnvironmentVariable($key)}
$process=$null
try {
 Set-Content (Join-Path $review 'phases.log') ''
 $env:CS_CASTLE_REVIEW_PATH=$review.Replace('\','/')+'/'
 $env:CS_CASTLE_MAP_ICON_REVIEW='1';$env:CS_BATTLE_MENU_REVIEW='1';$env:CS_BATTLE_MENU_HEIGHT='900'
 $process=Start-Process (Resolve-Path (Join-Path $root $Executable)).Path -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
 $deadline=[DateTime]::UtcNow.AddSeconds(75)
 do {
  Start-Sleep -Milliseconds 400
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -match 'FAIL'){throw $log}
  if($log -match 'PASS all ten map icons registered and preloaded'){break}
  if($process.HasExited){throw 'Map icon preview exited early'}
 } while([DateTime]::UtcNow -lt $deadline)
 if($log -notmatch 'PASS all ten map icons registered and preloaded'){throw 'Map icon preload review timed out'}
 $rows=@(Import-Csv (Join-Path $review 'icons.csv'))
 if($rows.Count -ne 10){throw 'Expected ten loaded icons'}
 for($i=0;$i -lt 10;$i++) {
  $row=$rows[$i]
  if([int]$row.castle -ne $i+1 -or [int]$row.width -ne 1024 -or [int]$row.height -ne 1024){throw 'Incorrect map icon dimensions or order'}
  if([int]$row.image_id -ne [int]$rows[0].image_id+$i){throw 'Map icon image IDs are not contiguous'}
  if(Test-Path (Join-Path $root 'content/castles/outdoor_castles_v2/map-icon-registration.json')) {
   $source=Join-Path $root ('content/castles/outdoor_castles_v2/map-icons/castle-map-{0:00}.png' -f ($i+1))
  } else {
  $version=if(Test-Path (Join-Path $root 'content/castles/map_icons_v2/manifest.json')){'map_icons_v2'}else{'map_icons_v1'}
  $source=Join-Path $root ('content/castles/'+$version+('/png/castle-map-{0:00}.png' -f ($i+1)))
  }
  $target=Join-Path $root ('Resources/res/castle_map_icons/castle_map_{0:00}.png' -f ($i+1))
  if((Get-FileHash -LiteralPath $source).Hash -ne (Get-FileHash -LiteralPath $target).Hash){throw 'Registered PNG differs from approved export'}
 }
 $rows | Format-Table
 'PASS ten map icon IDs, resource names, boot-loaded sprite/texture caches, 1024px dimensions and PNG hashes'
} finally {
 if($process -and !$process.HasExited){Stop-Process -Id $process.Id}
 foreach($key in $keys){[Environment]::SetEnvironmentVariable($key,$saved[$key])}
}
