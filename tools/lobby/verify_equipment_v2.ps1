param([string]$Executable='proj.win32/Debug.win32/cs.equipment-v2.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$oldMode=$env:CS_BATTLE_MENU_REVIEW
$oldHeight=$env:CS_BATTLE_MENU_HEIGHT
try {
 $env:CS_BATTLE_MENU_REVIEW='1'
 foreach($height in @(850,960,1136,1408)) {
  $env:CS_BATTLE_MENU_HEIGHT=[string]$height
  & powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $PSScriptRoot 'verify_pixel_equipment.ps1') -Executable $Executable
  if($LASTEXITCODE -ne 0){throw "Equipment review failed: $height"}
  $review=Join-Path $root 'output/pixel-equipment-review'
  $log=Get-Content (Join-Path $review 'phases.log') -Raw
  if($log -notmatch 'PASS equipment all hero equip and power'){throw 'Missing real equip verification'}
  $destination=Join-Path $root "output/equipment-v2-$height"
  New-Item -ItemType Directory -Force $destination | Out-Null
  Copy-Item (Join-Path $review '*.png') $destination
  Copy-Item (Join-Path $review 'phases.log') $destination
 }
} finally {
 $env:CS_BATTLE_MENU_REVIEW=$oldMode
 $env:CS_BATTLE_MENU_HEIGHT=$oldHeight
}
