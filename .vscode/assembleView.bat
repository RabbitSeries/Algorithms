@echo off
setlocal

if "%~1"=="" (
    echo Please provide file name without extension.
    echo Usage: %~nx0 filename output_filename
    goto :end
)

if "%~2"=="" (
    echo Please provide output filename without extension.
    echo Usage: %~nx0 filename output_filename
    goto :eof
)
@REM Comiple.
set filename=%~1
set output_filename=%~1
g++ -O1 -S "%filename%.cpp" -o "%output_filename%.s"
code  "%output_filename%.s"
g++ -c "%filename%.cpp" -o "%output_filename%.o"
:end
endlocal