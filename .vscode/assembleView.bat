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
set output_filename=%~2
g++ -O2 -S "%filename%" -o "%output_filename%.s"
g++ -c "%filename%" -o "%output_filename%.o"
objdump -d "%output_filename%.o" > "%output_filename%_AT&T.txt"
objdump -d --disassembler-options=intel "%output_filename%.o" > "%output_filename%_intel.txt"
shift
shift
code  "%output_filename%.s" && code "%output_filename%_AT&T.txt" && code "%output_filename%_intel.txt"
:end
endlocal