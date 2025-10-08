@echo off
echo Building ARTAMS CLI...
gcc -Wall -Wextra -std=c99 -I./core core/*.c cli/*.c -o artams_cli -lm
if %errorlevel% equ 0 (
    echo Build successful!
    echo.
    echo ========================================
    echo   ARTAMS - Attendance Management System
    echo ========================================
    echo.
    echo Starting ARTAMS CLI...
    echo Note: The application now includes exit confirmation.
    echo       You can safely use the program without it closing unexpectedly.
    echo.
    artams_cli.exe
) else (
    echo Build failed!
    pause
)