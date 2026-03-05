# Installation

## Build on mac

1. Make sure you have Homebrew with: `brew -- version` If not run `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"` to install homebrew.

2. Download Cmake on your device if not already done with: `brew install cmake` Verify with `cmake --version`.

3. Go inside the folder where you want to clone and run `git clone --recurse-submodules https://github.com/OscarDebra/VevingHjelper.git`to clone the project.

4. Go inside the project with `cd VevingHjelper`.

5. Run `mkdir build && cd build`, then run `cmake ..`, then run `cmake --build .`.

6. Now go back to root with `cd ..` and run the file with `./build/VevingHjelper` everytime.


## Build on windows

1. The msys2 mingw64 terminal is needed, it is possible otherwise, with visual studio, but you're on your own in that case. Go to msys2.org and download the installer.

2. When the installer is done downloading, open it and go through the steps leaving everything at default. Click install when you're at the end and wait until it's done.

3. Search "MSYS2 MINGW64" not just "MSYS2" in the search bar and open the app with the same name, use this terminal for all the upcoming commands.

4. Run `pacman -Syu`, and then run `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-make git`. The first command updates the package installer and the second one installs the c++ compiler, cmake, make and git.

5. Navigate inside the folder where you want to clone and run `git clone --recurse-submodules https://github.com/OscarDebra/VevingHjelper.git`to clone the project.

6. Go inside the project with `cd VevingHjelper`.

7. Run `mkdir build && cd build`, then run `cmake .. -G "MinGW Makefiles"`, then run `cmake --build .`.

8. Now go back to root with `cd ..` and run the file with `./build/VevingHjelper.exe` everytime.



