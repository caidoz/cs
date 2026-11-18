@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat" >nul
cl /nologo /EHsc /std:c++14 /utf-8 tools\lobby\test_shop_catalog.cpp /Fo:output\shop-catalog-tests.obj /Fe:output\shop-catalog-tests.exe
if errorlevel 1 exit /b 1
output\shop-catalog-tests.exe
