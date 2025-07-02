@echo off
echo Calculator Project - Docker Setup
echo =================================
echo.
echo This will install Docker Desktop and dependencies for Windows users.
echo.
echo Press any key to continue...
pause >nul

powershell -ExecutionPolicy Bypass -File "install_docker.ps1"

echo.
echo Setup completed! Check the output above for next steps.
echo.
pause 