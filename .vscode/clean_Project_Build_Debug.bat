@echo off
setlocal

if "%~1"=="" (
    echo Please provide working directory.
    echo Usage: %~nx0 workingPath
    goto :end
)

@REM No blank characters within.
set workingPath=%~1
cd %workingPath%
echo Performed vc debug files deletion at
echo %workingPath%
@REM echo %cd%
for /r "%workingPath%" %%p in (*.pdb) do del /q "%%p"
for /r "%workingPath%" %%p in (*.ilk) do del /q "%%p"
@REM del /s /q "%workingPath%\.vs\*"
for /d %%p in ("%workingPath%\build\*") do rd /s /q "%%p"
del /s /q "%workingPath%\build\*"
:end
endlocal