param(
    [Parameter(Mandatory=$true)][string]$SourceName,
    [Parameter(Mandatory=$true)][string]$ExpectedHash,
    [Parameter(Mandatory=$true)][string]$PreviousHash,
    [string]$SupersededHash='',
    [int]$TimeoutMinutes=120
)
$ErrorActionPreference='Stop'
$root=(Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$build=Join-Path $root 'proj.win32/Debug.win32'
if([IO.Path]::GetFileName($SourceName) -ne $SourceName -or [IO.Path]::GetExtension($SourceName) -ne '.exe') {throw 'Expected an executable basename'}
$source=Join-Path $build $SourceName
$target=Join-Path $build 'cs.exe'
$log=Join-Path $root 'output/verified-build-install.log'
$deadline=[DateTime]::UtcNow.AddMinutes($TimeoutMinutes)
Set-Content -LiteralPath $log -Encoding UTF8 -Value "Waiting for cs.exe to close. Source: $SourceName"
while([DateTime]::UtcNow -lt $deadline) {
    if((Get-FileHash -LiteralPath $source -Algorithm SHA256).Hash -ne $ExpectedHash) {
        Add-Content -LiteralPath $log -Value 'Cancelled: source changed after verification.';exit 2
    }
    $targetHash=(Get-FileHash -LiteralPath $target -Algorithm SHA256).Hash
    if($targetHash -ne $PreviousHash -and $targetHash -ne $SupersededHash) {
        Add-Content -LiteralPath $log -Value 'Cancelled: another build already replaced cs.exe.';exit 3
    }
    $active=Get-Process cs -ErrorAction SilentlyContinue | Where-Object {$_.Path -eq $target}
    if(!$active) {
        try {
            Copy-Item -LiteralPath $source -Destination $target -Force
            if((Get-FileHash -LiteralPath $target -Algorithm SHA256).Hash -ne $ExpectedHash) {throw 'Installed hash mismatch'}
            Add-Content -LiteralPath $log -Value "Installed: $SourceName SHA256 $ExpectedHash"
            exit 0
        } catch [System.IO.IOException] {
            # A process may be opening/closing the executable between checks.
        }
    }
    Start-Sleep -Milliseconds 1000
}
Add-Content -LiteralPath $log -Value 'Timed out without changing the executable.'
exit 4
