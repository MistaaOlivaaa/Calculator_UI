Write-Host "=== Calculator Project - Docker Setup ===" -ForegroundColor Green
Write-Host "This script will help you install Docker Desktop and dependencies" 
Write-Host ""

$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")
if (-not $isAdmin) {
    Write-Host "ERROR: This script must be run as Administrator!" -ForegroundColor Red
    Write-Host "Right-click on PowerShell and select 'Run as Administrator'" -ForegroundColor Yellow
    exit 1
}

$osInfo = Get-ComputerInfo
$windowsVersion = $osInfo.WindowsVersion
Write-Host "Windows Version: $windowsVersion" -ForegroundColor Cyan

Write-Host "Checking WSL2 availability..." -ForegroundColor Yellow
$wslAvailable = Get-Command wsl -ErrorAction SilentlyContinue
if (-not $wslAvailable) {
    Write-Host "WSL not found. Installing WSL2..." -ForegroundColor Yellow
    try {
        wsl --install
        Write-Host "WSL2 installed successfully!" -ForegroundColor Green
        Write-Host "Please restart your computer and run this script again." -ForegroundColor Yellow
        exit 0
    }
    catch {
        Write-Host "Failed to install WSL2. Please install it manually:" -ForegroundColor Red
        Write-Host "https://docs.microsoft.com/en-us/windows/wsl/install" -ForegroundColor Cyan
        exit 1
    }
}

Write-Host "Checking if Docker Desktop is installed..." -ForegroundColor Yellow
$dockerPath = Get-Command docker -ErrorAction SilentlyContinue
if ($dockerPath) {
    Write-Host "Docker is already installed!" -ForegroundColor Green
    docker --version
} else {
    Write-Host "Docker Desktop not found. Installing..." -ForegroundColor Yellow
    
    $dockerUrl = "https://desktop.docker.com/win/stable/Docker%20Desktop%20Installer.exe"
    $dockerInstaller = "$env:TEMP\DockerDesktopInstaller.exe"
    
    Write-Host "Downloading Docker Desktop..." -ForegroundColor Yellow
    try {
        Invoke-WebRequest -Uri $dockerUrl -OutFile $dockerInstaller
        Write-Host "Download completed!" -ForegroundColor Green
        
        Write-Host "Installing Docker Desktop..." -ForegroundColor Yellow
        Start-Process -FilePath $dockerInstaller -ArgumentList "install --quiet" -Wait
        
        Write-Host "Docker Desktop installed successfully!" -ForegroundColor Green
        Write-Host "Please restart your computer and start Docker Desktop." -ForegroundColor Yellow
        
        Remove-Item $dockerInstaller -Force
    }
    catch {
        Write-Host "Failed to install Docker Desktop automatically." -ForegroundColor Red
        Write-Host "Please download and install manually from:" -ForegroundColor Yellow
        Write-Host "https://www.docker.com/products/docker-desktop/" -ForegroundColor Cyan
    }
}

Write-Host "Checking for X11 server (VcXsrv)..." -ForegroundColor Yellow
$vcxsrvPath = Get-ChildItem "C:\Program Files\VcXsrv" -ErrorAction SilentlyContinue
if ($vcxsrvPath) {
    Write-Host "VcXsrv is already installed!" -ForegroundColor Green
} else {
    Write-Host "VcXsrv not found. Installing..." -ForegroundColor Yellow
    
    $vcxsrvUrl = "https://sourceforge.net/projects/vcxsrv/files/latest/download"
    $vcxsrvInstaller = "$env:TEMP\vcxsrv_setup.exe"
    
    Write-Host "Downloading VcXsrv..." -ForegroundColor Yellow
    try {
        Invoke-WebRequest -Uri $vcxsrvUrl -OutFile $vcxsrvInstaller
        Write-Host "Download completed!" -ForegroundColor Green
        
        Write-Host "Installing VcXsrv..." -ForegroundColor Yellow
        Write-Host "Please follow the installation wizard and configure:" -ForegroundColor Cyan
        Write-Host "- Allow connections from any host" -ForegroundColor Cyan
        Write-Host "- Disable access control" -ForegroundColor Cyan
        Write-Host "- Set display number to 0" -ForegroundColor Cyan
        
        Start-Process -FilePath $vcxsrvInstaller -Wait
        
        Write-Host "VcXsrv installed successfully!" -ForegroundColor Green
        
        Remove-Item $vcxsrvInstaller -Force
    }
    catch {
        Write-Host "Failed to install VcXsrv automatically." -ForegroundColor Red
        Write-Host "Please download and install manually from:" -ForegroundColor Yellow
        Write-Host "https://sourceforge.net/projects/vcxsrv/" -ForegroundColor Cyan
    }
}

Write-Host ""
Write-Host "=== Installation Summary ===" -ForegroundColor Green
Write-Host "1. WSL2: Available" -ForegroundColor Green
Write-Host "2. Docker Desktop: Installed" -ForegroundColor Green
Write-Host "3. VcXsrv: Installed" -ForegroundColor Green
Write-Host ""
Write-Host "Next steps:" -ForegroundColor Yellow
Write-Host "1. Restart your computer if prompted" -ForegroundColor Cyan
Write-Host "2. Start Docker Desktop" -ForegroundColor Cyan
Write-Host "3. Start VcXsrv (XLaunch)" -ForegroundColor Cyan
Write-Host "4. Open PowerShell in the project directory" -ForegroundColor Cyan
Write-Host "5. Run: docker build -t calculator ." -ForegroundColor Cyan
Write-Host "6. Run: docker run -e DISPLAY=host.docker.internal:0.0 --rm calculator" -ForegroundColor Cyan
Write-Host ""
Write-Host "Enjoy your calculator!"