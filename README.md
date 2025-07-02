# 🧮 Calculator by MISTAAAOLIVAA


![Screenshot from 2025-07-02 06-43-24](https://github.com/user-attachments/assets/e6495c1a-3c08-451f-8b6d-a24a27feb2ef)

*Modern GTK3 calculator interface*

A sleek, modern calculator built with GTK3 Perfect for both Linux enthusiasts and Windows users who want a beautiful, functional calculator experience.

![Calculator Demo](https://img.shields.io/badge/Status-Ready%20to%20Use-brightgreen)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-blue)
![Language](https://img.shields.io/badge/Language-C-orange)

## ✨ Features

- **Clean, modern interface** with GTK3
- **Basic arithmetic operations**: +, -, ×, ÷
- **Decimal number support**
- **Clear function** for fresh calculations
- **Cross-platform**: Works on Linux and Windows
- **Lightweight**: No heavy dependencies

## 🚀 Quick Start

### For Linux Users 🐧

If you're on Linux, you're in luck! This is super easy:

```bash
# Clone or download the project
cd Calculator

# Build it
mkdir build && cd build
cmake .. && make

# Run it
./calculator
```

That's it! Your calculator should pop up with a beautiful interface.

### For Windows Users 🪟

Don't worry, we've got you covered! We've made it super easy with Docker.

#### Option 1: Super Easy Setup (Recommended)

1. **Double-click `setup.bat`** - This will install everything you need automatically
2. **Restart your computer** (if it asks you to)
3. **Start Docker Desktop** and **VcXsrv** from your Start menu
4. **Double-click `run_calculator.bat`** - Your calculator will appear!

#### Option 2: Manual Setup

If you prefer to do it manually:

1. **Install Docker Desktop** from [docker.com](https://www.docker.com/products/docker-desktop/)
2. **Install VcXsrv** from [sourceforge.net](https://sourceforge.net/projects/vcxsrv/)
3. **Open PowerShell as Administrator** and run:
   ```powershell
   powershell -ExecutionPolicy Bypass -File "install_docker.ps1"
   ```
4. **Build and run**:
   ```bash
   docker build -t calculator .
   docker run -e DISPLAY=host.docker.internal:0.0 --rm calculator
   ```

## 🛠️ What's Inside

This project includes everything you need:

```
Calculator/
├── calculator.c          # The main calculator code
├── CMakeLists.txt        # Build configuration
├── Dockerfile            # Docker setup for Windows
├── setup.bat             # One-click Windows setup
├── run_calculator.bat    # One-click calculator launch
├── install_docker.ps1    # Automated dependency installer
├── .dockerignore         # Optimized Docker builds
└── README.md             # This file
```

## 🎯 How to Use

Once the calculator is running:

- **Numbers**: Click the number buttons (0-9)
- **Operations**: Click +, -, ×, or ÷
- **Decimal**: Click the "." button for decimal numbers
- **Clear**: Click "C" to start over
- **Calculate**: Click "=" to see your result

## 🔧 Troubleshooting

### Linux Issues
- **"GTK not found"**: Install GTK3: `sudo apt-get install libgtk-3-dev` (Ubuntu/Debian)
- **"CMake not found"**: Install CMake: `sudo apt-get install cmake`

### Windows Issues
- **Calculator window doesn't appear**: Make sure VcXsrv is running and configured to allow connections
- **Docker not working**: Make sure Docker Desktop is running
- **Permission errors**: Run PowerShell as Administrator

## 🤝 Contributing

Found a bug? Want to add a feature? Feel free to contribute!

1. Fork the project
2. Create a feature branch
3. Make your changes
4. Test on both Linux and Windows
5. Submit a pull request


## 🙏 Acknowledgments

- Built with GTK3 for beautiful cross-platform GUI
- Docker setup makes Windows compatibility a breeze
- Thanks to the open source community for amazing tools

---

**Made with by MISTAAAOLIVAA**

*Enjoy your calculations!* 🧮✨ 
