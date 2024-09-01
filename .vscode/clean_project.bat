@echo off
setlocal

if "%~1"=="" (
    echo Please provide working directory.
    echo Usage: %~nx0 workingPath
    goto :end
)

set workingPath = %~1

cd %workingPath%



echo About to perform deletion at
echo %cd%
set /p confirm=Proceed? (Y/N) [default:N]:

@REM For code::blocks projects
rd /s /q "%workingPath%\obj\Debug"
rd /s /q "%workingPath%\obj\Release"
echo.
echo code::blocks build files cleaned.
echo.
if /i "%confirm%"=="" set confirm=N

if /i "%confirm%"=="N" (
    echo Operation aborted.
    goto end
)

set tempFile=.\delete_list.txt

echo. > %tempFile%

for /r %%i in (*.exe) do echo %%i >> %tempFile%

for /r %%i in (*.o) do echo %%i >> %tempFile%

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