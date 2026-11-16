@echo off
setlocal
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat" >nul
if errorlevel 1 exit /b 1
cl /nologo /EHsc /std:c++14 /utf-8 /W4 tools\items\catalog_tests.cpp /Fo:output\item-series\catalog-tests.obj /Fe:output\item-series\catalog-tests.exe
if errorlevel 1 exit /b 1
output\item-series\catalog-tests.exe
exit /b %errorlevel%
