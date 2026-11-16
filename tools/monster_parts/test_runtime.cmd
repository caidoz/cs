@echo off
setlocal
set "PATH=C:\Program Files (x86)\Microsoft Visual Studio\Installer;%PATH%"
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat" >nul
if errorlevel 1 exit /b 1
if not exist output\monster-parts-tests mkdir output\monster-parts-tests
cl /nologo /EHsc /std:c++14 /utf-8 /W4 tools\monster_parts\runtime_tests.cpp /Fo:output\monster-parts-tests\runtime.obj /Fe:output\monster-parts-tests\runtime.exe
if errorlevel 1 exit /b 1
output\monster-parts-tests\runtime.exe
