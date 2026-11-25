@echo off
setlocal
set CS_TITLE_CAMP_REVIEW=1
python "%~dp0verify_portrait.py" --height 850 --stage 0 --lobby
if errorlevel 1 exit /b 1
python "%~dp0verify_portrait.py" --height 1408 --stage 0 --lobby
exit /b %errorlevel%
