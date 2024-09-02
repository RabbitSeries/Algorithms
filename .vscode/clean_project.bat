@echo off
setlocal

if "%~1"=="" (
    echo Please provide working directory.
    echo Usage: %~nx0 workingPath
    goto :end
)

@REM No blank characters within.
set workingPath=%~1

echo %workingPath%
cd %workingPath%

echo About to perform deletion at
@REM echo %cd%
set /p confirm=Proceed? (Y/N) [default:N]:

if /i "%confirm%"=="" set confirm=N

if /i "%confirm%"=="N" (
    echo Operation aborted.
    goto end
)

REM For code::blocks projects

@REM for /d %%p in ("%workingPath%\.vs\*") do rd /s /q "%%p"
@REM del /s /q "%workingPath%\.vs\*"

if exist "%workingPath%\.vs" rd /s /q "%workingPath%\.vs"
if exist "%workingPath%\bin" rd /s /q "%workingPath%\bin"
if exist "%workingPath%\obj" rd /s /q "%workingPath%\obj"

echo.
echo code::blocks build files cleaned.
echo.

set tempFile=.\delete_list.txt

echo. > %tempFile%

for /r %%i in (*.exe) do echo %%i >> %tempFile%

for /r %%i in (*.o) do echo %%i >> %tempFile%

for /r %%i in (*.obj) do echo %%i >> %tempFile%

set filesFound=N

for /f "delims=" %%i in ('findstr /r ".exe" %tempFile%') do (
    set filesFound=F
)

for /f "delims=" %%i in ('findstr /r ".o" %tempFile%') do (
    set filesFound=F
)

if "%filesFound%"=="N" (
    echo .exe .o Files not found.
    del %tempFile%
    goto end
)

echo Files will be deleted as follows:
type %tempFile%
echo.

set /p deletionConfirm=Proceed? (Y/N) [default: N]:

if /i "%deletionConfirm%"=="" set deletionConfirm=N

if /i "%deletionConfirm%"=="Y" (
    echo Deleting...
    
    for /f "delims=" %%i in (%tempFile%) do del "%%i"
    
    echo Deletion completed successfully.
) else (
    echo Deletion aborted.
)

del %tempFile%

:end
endlocal