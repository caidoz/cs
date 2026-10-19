param([ValidateRange(0,5)][int]$Stage=0)
$ErrorActionPreference='Stop'
# Rebuild all six stages together: one common canvas and room aperture are required.
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$python=Join-Path $env:LOCALAPPDATA 'Python/bin/python.exe'
if(!(Test-Path $python)){$python='python'}
& $python (Join-Path $root 'tools/castles/restore_uniform_castles.py') --family seventh
if($LASTEXITCODE -ne 0){throw 'Uniform source registration failed'}
