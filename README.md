# Libre-Terminal
What is the goal of Libre Terminal? The goal of this software is to provide users with an easy terminal interface, cutting cross-platform incompatibilities, being extremely fast, and lastly, very customizable, having a configuration & [SOON] plug-in system.

- Easy terminal interface? What do you mean?
With an easy terminal interface, we refer to one that does not make you memorize either hard names or extremely long commands.

- Cutting cross-platform incompatabilities? What does this mean?
With the cut of cross-platform incompatabilities we mean stopping the differences between (mainly) Linux with Windows, along with MacOS, and then every other possible OS

[![GitHub Repo](https://img.shields.io/badge/github-repo-blue?logo=github)](https://github.com/fif3x/Libre-Terminal)

# Dependencies

You will need the following packages for this to work: `g++`, `make`

For Linux users, you can check the `dependencies.sh` file in `build/`. For Windows users, please download GCC through MinGW and make through MSYS2 which can be downloaded through winget: `winget install MSYS2.MSYS2` and then on MSYS2 run: `pacman -S make`

# Installation

**NOTE: instead of building the binary yourself, you can also download it through the releases**

*Note: its heavily discouraged, but if you don't want to download it manually, please run the following command (ONLY FOR LINUX)*
```bash
curl https://raw.githubusercontent.com/fif3x/LibreTerminal/refs/heads/main/build/autobuild.sh | bash
```

1. Install the repo, you can either do this with Git, the GitHub GUI or GitHub CLI. It's strongly recommended to install it through Git, using this command:
```bash
git clone https://github.com/fif3x/LibreTerminal.git
```

2. If you are a Linux/MacOS user skip this. For Windows users, copy the file named `config.conf` from the repository folder under the 'etc' subfolder to the location `C:\\LibreTerminal`

3. Now change directory to the build folder, make the script executable (if needed) and run it
For Windows:
```bat
cd build
build
```
For Linux:
```bash
cd build
chmod +x *
./build.sh
```

4. If it has been compiled succesfully, your program should be located in either `bin/linux` or `bin/win`

# Licensing
Free and Open Source Software (FOSS) program.
Licensed under the GNU GPL v3 license.
No warranty.

# Contact
For any questions, suggestions, ideas or problems, please contact me on one of the following platforms:
- **Instagram:** @fifex._
- **Telegram:** t.me/fif3x

![Screenshot 2025-06-18 200800](https://github.com/user-attachments/assets/63b62b76-2cfe-4747-ba81-1d1e81e974c1)
