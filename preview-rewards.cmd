@echo off
setlocal
cd /d "%~dp0Resources"
set "CS_MERGE_REVIEW=1"
set "CS_REWARD_REVEAL_REVIEW=1"
set "CS_REWARD_REVEAL_DEMO=%~1"
if not defined CS_REWARD_REVEAL_DEMO set "CS_REWARD_REVEAL_DEMO=30"
set "CS_MERGE_REVIEW_HEIGHT=%~2"
if not defined CS_MERGE_REVIEW_HEIGHT set "CS_MERGE_REVIEW_HEIGHT=850"
"%~dp0proj.win32\Debug.win32\cs.reward-reveal.exe"
endlocal
