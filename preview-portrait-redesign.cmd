@echo off
setlocal
set "CS_WINDOW_HEIGHT=%~1"
if not defined CS_WINDOW_HEIGHT set "CS_WINDOW_HEIGHT=1408"
cd /d "%~dp0Resources"
"%~dp0proj.win32\Debug.win32\cs_portrait_redesign.exe"
endlocal
