# PasswordManager

A password manager/cracker used to demonstrate dictionary attacks for cracking passwords with MD5 and SHA256 hashes.

The software also demonstrates safer ways of storing passwords using SHA256 with salt.

**Educational Purposes Only:** This program is strictly for educational purposes. The passwords utilized in this program are publicly available and commonly used, which you can easily find and download online. Any non-consensual use or misuse of this software that could cause harm is not the intended use.

**Compatibility Note:** The Makefile committed in this repository only runs on macOS. To run it on Windows, be sure to use the Makefile version that corresponds to your OS.

## Downloading the Makefile for Windows

To download the Makefile for Windows, click the link below. Then, right-click on the `Raw` button and select `Save link as...` to save the file to your computer.

[Download Makefile](https://raw.githubusercontent.com/petterssonb/PasswordManager/main/MakefileWindows.txt
)


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
 - You have the right makefile for your OS


4. Run the app:

 - Run Makefile.
 - Start managing your passwords with the cli!
