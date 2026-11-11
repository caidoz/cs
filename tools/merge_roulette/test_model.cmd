@echo off
setlocal
set "PATH=C:\Program Files (x86)\Microsoft Visual Studio\Installer;%PATH%"
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat" >nul
if errorlevel 1 exit /b 1
if not exist output\merge-roulette mkdir output\merge-roulette
cl /nologo /EHsc /std:c++14 /utf-8 /W4 /Zi /Od tools\merge_roulette\model_tests.cpp /Fo:output\merge-roulette\model-tests.obj /Fe:output\merge-roulette\model-tests.exe /Fd:output\merge-roulette\model-tests.pdb
if errorlevel 1 exit /b 1
output\merge-roulette\model-tests.exe %*
