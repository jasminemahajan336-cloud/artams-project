@echo off
setlocal
REM Quick compilation script - outputs to root folder

echo ========================================
echo    Compiling ARTAMS
echo ========================================
echo.

REM Check for GCC in PATH
where gcc >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] gcc not found. Please install MinGW-w64 or add gcc to PATH.
    echo        Download: https://www.mingw-w64.org/ or TDM-GCC
    exit /b 1
)

REM Compile the project (output to root folder)
gcc -Wall -Wextra -std=c99 -I core core\*.c cli\*.c -o artams_cli.exe -lm

REM Check if build was successful
if %errorlevel% equ 0 (
    echo.
    echo [SUCCESS] Build completed successfully!
    echo Executable: artams_cli.exe
    echo.
    echo Run: artams_cli.exe
    exit /b 0
) else (
    echo.
    echo [ERROR] Build failed! Check the error messages above.
    exit /b 1
)

endlocal
