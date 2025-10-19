@echo off
REM Build script for ARTAMS (Attendance Management System)

echo ========================================
echo    Building ARTAMS - Attendance System
echo ========================================
echo.

REM Compile the project
gcc -Wall -Wextra -std=c99 -I core core\*.c cli\*.c -o artams_cli.exe -lm

REM Check if build was successful
if %errorlevel% equ 0 (
    echo.
    echo [SUCCESS] Build completed successfully!
    echo Executable: artams_cli.exe
) else (
    echo.
    echo [ERROR] Build failed! Check the error messages above.
    pause
    exit /b 1
)

echo ========================================
echo.
