param([string]$Executable = 'proj.win32/Debug.win32/cs.castle-menu-verify.exe')
$ErrorActionPreference = 'Stop'
$root = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$exe = (Resolve-Path (Join-Path $root $Executable)).Path
$review = Join-Path $root 'output/castle-menu-verification'
New-Item -ItemType Directory -Force $review | Out-Null
$oldProtocol = $env:CS_CASTLE_PROTOCOL_TEST
$oldReview = $env:CS_CASTLE_REVIEW_PATH
$process = $null
try {
    $env:CS_CASTLE_PROTOCOL_TEST = '1'
    $process = Start-Process $exe -WorkingDirectory $root -WindowStyle Hidden -PassThru
    if (-not $process.WaitForExit(15000)) { throw 'Protocol check timed out' }
    if ($process.ExitCode -ne 0) { throw "Protocol check failed: $($process.ExitCode)" }
    $env:CS_CASTLE_PROTOCOL_TEST = $null
    'PASS actual dump encoder/decoder: 10 castles, 100 upgrade levels'
    foreach ($name in @('phases.log','screens.log','frames.log')) {
        $path = Join-Path $review $name
        if (Test-Path -LiteralPath $path) { Remove-Item -LiteralPath $path }
    }
    $env:CS_CASTLE_REVIEW_PATH = $review.Replace('\','/') + '/'
    $process = Start-Process $exe -WorkingDirectory (Join-Path $root 'Resources') -WindowStyle Hidden -PassThru
    $deadline = [DateTime]::UtcNow.AddSeconds(45)
    $phases = Join-Path $review 'phases.log'
    do {
        Start-Sleep -Milliseconds 250
        if ($process.HasExited) { throw "UI process exited: $($process.ExitCode)" }
        $log = if (Test-Path $phases) { Get-Content $phases -Raw } else { '' }
        if ($log -match 'FAIL') { throw "UI verification failed:`n$log" }
        if ($log -match 'PASS local server save and reload') { break }
    } while ([DateTime]::UtcNow -lt $deadline)
    if ($log -notmatch 'PASS local server save and reload') { throw 'UI verification timed out' }
    $screens = @(Get-Content (Join-Path $review 'screens.log'))
    if ($screens.Count -ne 8 -or @($screens | Where-Object { $_ -notmatch '^PASS ' }).Count) {
        throw 'Expected 8 successful screen captures'
    }
    'PASS registered touch areas, room upgrade, paid purchase, local server save/reload, 8 screens'
} finally {
    if ($process -and -not $process.HasExited) { Stop-Process -Id $process.Id }
    $env:CS_CASTLE_PROTOCOL_TEST = $oldProtocol
    $env:CS_CASTLE_REVIEW_PATH = $oldReview
}
