# PasswordManager

A password manager/cracker used to demonstrate dictionary attacks for cracking passwords with MD5 and SHA256 hashes.

The software also demonstrates safer ways of storing passwords using SHA256 with salt. That is not possible to crack with the software. 

Crackable hashes is found in hashes.txt. Safe way of storing with salt is found in users.txt.

**Educational Purposes Only:** This program is strictly for educational purposes. The passwords utilized in this program are publicly available and commonly used, which you can easily find and download online. Any non-consensual use or misuse of this software that could cause harm is not the intended use.

**Compatibility Note:** The Makefile committed in this repository will run on Windows, Linux and MacOS. Be sure to follow the steps below in the "**How to run**" section to properly run the program.

## Project structure

```bash
├── CMakeLists.txt        # CMake configuration file
├── LICENSE               # License file
├── README.md             # Project README with instructions
├── build/                # Directory created by CMake for build files
├── build.sh              # Shell script to build the project (macOS/Linux/Windows with bash)
├── build.bat             # Batch script to build the project (Windows)
├── run.sh                # Shell script to run the project (macOS/Linux/Windows with bash)
├── run.bat               # Batch script to run the project (Windows)
├── commonpasswords/       # Directory containing common passwords list
│   ├── 100kMostUsedPasswords.txt
│   └── example.txt
├── include/              # Header files
│   ├── passwordManager.h
├── src/                  # Source files
│   ├── passwordManager.cpp
│   └── main.cpp
├── userdata/             # User data for the application
│   ├── hashes.txt
│   └── users.txt                 
```

### Prerequisites

Make sure you have the following installed on your system:

 - ***CMake*** (version 3.10 or higher)
     - [CMake Download and Installation Guide](https://perso.uclouvain.be/allan.barrea/opencv/building_tools.html)

 - ***G++ Compiler*** (for compiling C++ code)
     - Run: ***g++ --version*** in the terminal to verify G++ is installed. If not, refer to one of the setup guides below.
     
     - [G++ for Windows](https://www.youtube.com/watch?v=GxFiUEO_3zM)

     - [G++ for MacOS](https://www.youtube.com/watch?v=HYrXBoDJmcw)

     - [G++ for Linux](https://www.youtube.com/watch?v=4e7pa6Pf3VQ)

 - ***OpenSSL***
     - Run: ***openssl version*** in the terminal to verify OpenSSL is installed. If not, refer to one of the setup guides below.

     - [OpenSSL for Windows](https://www.youtube.com/watch?v=bguFKIgEpoM)

     - [OpenSSL for MacOS](https://www.youtube.com/watch?v=dFy6O8moG0I)

     - [OpenSSL for Linux](https://www.youtube.com/watch?v=eDCOBL4xJpg)

### 1. Clone the repository to your local machine

```bash
git clone https://github.com/petterssonb/Cardlist-manager.git
```

### 2. Navigate to the project directory.

```bash
cd Cardlist-manager
```

### 3. Build the Project:

***macOS/Linux (using build.sh)***
```bash
./build.sh
```

***Windows (using build.bat)***
```bash
./build.bat
```

This will generate the ***main*** executable on macOS/Linux or ***main.exe*** on Windows in the build directory

### 4. Run the Project

After successfully building the project, use the provided scripts to run the program:

***macOS/Linux***
```bash
./run.sh
```

***Windows***
```bash
./run.bat
```

## License

Distributed under the MIT License. See `LICENSE` for more information.
