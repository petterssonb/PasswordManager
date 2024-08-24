# PasswordManager

A password manager/cracker used to demonstrate dictionary attacks for cracking passwords with MD5 and SHA256 hashes.

The software also demonstrates safer ways of storing passwords using SHA256 with salt. That is not possible to crack with the software. 

Crackable hashes is found in hashes.txt. Safe way of storing with salt is found in users.txt.

**Educational Purposes Only:** This program is strictly for educational purposes. The passwords utilized in this program are publicly available and commonly used, which you can easily find and download online. Any non-consensual use or misuse of this software that could cause harm is not the intended use.

**Compatibility Note:** The Makefile committed in this repository will run on Windows, Linux and MacOS. Be sure to follow the steps below in the "**How to run**" section to properly run the program.

## Project structure

```bash
├── commonpasswords/
│   ├── 100kMostUsedPasswords.txt
│   └── example.txt
├── include/
│   ├── adminmenu.h        
├── src/
│   ├── passwordManager.cpp
│   └── main.cpp
├── userdata/
│   ├── hashes.txt
│   └── users.txt    
├── Makefile               
├── LICENSE                
└── README.md              

```

## How to run

1. Clone the repository to your local machine

```bash
git clone https://github.com/petterssonb/PasswordManager.git
```

2. Navigate to the project directory.

```bash
cd PasswordManager
```
3. Make sure:
 - You have g++ compiler (run the following in the terminal)
```bash
g++ --version
```
**If you do not have the compiler, you should see something like this:**

 'g++' is not recognized as an internal or external command,
operable program or batch file.

**Then watch one of these below**

[G++ for Windows](https://www.youtube.com/watch?v=GxFiUEO_3zM)

[G++ for MacOS](https://www.youtube.com/watch?v=HYrXBoDJmcw)

[G++ for Linux](https://www.youtube.com/watch?v=4e7pa6Pf3VQ)

 - Make sure you have OpenSSL aswell
```bash
openssl version
```
 **If you don't have OpenSSL watch one of these below**

 [OpenSSL for Windows](https://www.youtube.com/watch?v=bguFKIgEpoM)

 [OpenSSL for MacOS](https://www.youtube.com/watch?v=dFy6O8moG0I)

 [OpenSSL for Linux](https://www.youtube.com/watch?v=eDCOBL4xJpg)


### 4. Build the Project:

```bash
make
```

### 5. Run the Project

#### MacOS or Linux
```bash
./main
```

#### Windows
```bash
./main.exe
```

## License

Distributed under the MIT License. See `LICENSE` for more information.
