param(
  [string]$target = "learnOpenGL"
)
$dir = "./build/bin/${target}"
$exe = "${target}.exe"

if (!(Test-Path build)) { mkdir build }

cmake -S . -B build -G "MinGW Makefiles"

if ($LASTEXITCODE -eq 0) {
  cmake --build build --target $target
}

if ($LASTEXITCODE -eq 0) {
  if (!(Test-Path "$dir/$exe")) {
    Write-Host "Executable not found: $dir/$exe" -ForegroundColor Red
    exit 1
  }

  Write-Host "--- Launching [${target}] ---" -ForegroundColor Green
  Push-Location $dir
  & "./$exe"
  Pop-Location
} else {
  Write-Host "--- Build Failed ---" -ForegroundColor Red
}
