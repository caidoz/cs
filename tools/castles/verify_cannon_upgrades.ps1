param([string]$Executable='proj.win32/Debug.win32/cs.cannon-upgrades.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$saved=$env:CS_CANNON_GRADE_REVIEW
try {
 & (Join-Path $PSScriptRoot 'verify_current_cannon_icons.ps1') -Executable $Executable
 for($grade=0;$grade -le 5;$grade++) {
  $env:CS_CANNON_GRADE_REVIEW="$grade"
  & (Join-Path $PSScriptRoot 'verify_individual_v4.ps1') -Height 1400 -Executable $Executable
  $destination=Join-Path $root "output/cannon-upgrades-review/grade-$grade"
  New-Item -ItemType Directory -Force $destination | Out-Null
  Copy-Item (Join-Path $root 'output/individual-v4-review-1400/*') $destination -Force
 }
 'PASS sixty mounted castle/grade combinations and sixty inventory frames'
} finally { $env:CS_CANNON_GRADE_REVIEW=$saved }
