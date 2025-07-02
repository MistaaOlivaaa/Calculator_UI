@echo off
echo Calculator Project - Quick Start
echo ===============================
echo.

REM 
docker version >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: Docker is not running!
    echo Please start Docker Desktop and try again.
    echo.
    pause
    exit /b 1
)

echo Building Docker image...
docker build -t calculator .

if %errorlevel% neq 0 (
    echo ERROR: Build failed!
    echo Please check the error messages above.
    echo.
    pause
    exit /b 1
)

echo.
echo Build successful! Starting calculator...
echo Make sure VcXsrv is running for the GUI to appear.
echo.

docker run -e DISPLAY=host.docker.internal:0.0 --rm calculator

echo.
echo Calculator closed.
pause 