param([string]$Executable='proj.win32/Debug.win32/cs.drag-preview.exe')
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$old=$env:CS_DRAG_PREVIEW_REVIEW
try {
    $env:CS_DRAG_PREVIEW_REVIEW='1'
    & (Join-Path $root 'tools/boomerangs/verify_compact_equipment.ps1') -Executable $Executable
    $dest=Join-Path $root 'output/drag-preview-review'
    New-Item -ItemType Directory -Force $dest | Out-Null
    foreach($i in 0..3) {
        Copy-Item -LiteralPath (Join-Path $root "output/compact-equipment-review/compact-equipment-$i.png") -Destination (Join-Path $dest "drag-preview-$i.png") -Force
    }
    'PASS actual UI: gained and lost connections, ally conditions, invalid placement and cannon cap; four captures'
} finally {
    $env:CS_DRAG_PREVIEW_REVIEW=$old
}
