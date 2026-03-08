# Installation

## Build on mac

1. Open your terminal. Make sure you have Homebrew with: `brew -- version` in the terminal. If not run `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"` in the terminal to install homebrew.

2. Download Cmake on your device if not already done with: `brew install cmake` Verify with `cmake --version`.

3. Go inside the folder where you want to clone and run `git clone --recurse-submodules https://github.com/OscarDebra/VevingHjelper.git` in the terminal to clone the project.

4. Go inside the project by running `cd VevingHjelper` in the terminal.

5. Run `mkdir build && cd build`, then run `cmake ..`, then run `cmake --build .` in the terminal.

6. Now go back to root with `cd ..` and run the file with `./build/VevingHjelper` in the terminal everytime.


## Build on windows

1. The msys2 mingw64 terminal is needed, it is possible otherwise, with visual studio, but you're on your own in that case. Go to msys2.org and download the installer.

2. When the installer is done downloading, open it and go through the steps leaving everything at default. Click install when you're at the end and wait until it's done.

3. Search "MSYS2 MINGW64" not just "MSYS2" in the search bar and open the app with the same name, use this terminal for all the upcoming commands.

4. Run `pacman -Syu`, and then run `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-make git` in the terminal. The first command updates the package installer called pacman and the second one installs the c++ compiler, cmake, make and git with pacman.

5. Navigate inside the folder where you want to clone and run `git clone --recurse-submodules https://github.com/OscarDebra/VevingHjelper.git` in the terminal to clone the project.

6. Go inside the project by running `cd VevingHjelper` in the terminal.

7. Run `mkdir build && cd build`, then run `cmake .. -G "MinGW Makefiles"`, then run `cmake --build .` in the terminal.

8. Now go back to root with `cd ..` and run the file with `./build/VevingHjelper.exe` in the terminal everytime.



# Manual

The first screen to pop up should be the form screen, from here you can choose the ratio of the canvas, for example if you choose 2 for the width and 1 for the height, the canvas will be twice as wide as it is tall. After entering the ratio, click on the confirm button.

After you've clicked the confirm button, you should find yourself on the main screen. First, you can modify the amount of columns and rows the canvas has by changing the values of the columns and rows input fields that are located to the top left of the screen. You will probably find that your canvas has a checkerboard pattern, this is because the threads running through the canvas, represented by the colored squares interlock each other, going over and under each other. I've made one side of the threads white, and the other black so it's easy to see at which thread goes over the other. 

To change where the borders between the threads are, simply hover over a border between 2 threads on the canvas, where it goes from one color to another. You should find that your mouse icon changes to a two-sided arrow and the border changes color from black to grey. Now hold down the left click and move your mouse to move the boundary, the border you're dragging should turn white, although it may be a bit hard to see. 

If you want to make the size of the rows or the columns equal, click the equalize rows or equalize columns buttons situated under the input fields for the columns and rows to the top left of the screen. 

To change the colors of the canvas, simply click on any of the colored squares that you can find to the left, to the right, over and under the canvas. A menu with the corresponding hex code, which is a six-character method to represent any color will appear after clicking. To change it to your own color, simply remove the text and paste in the hex code of your desired color. You can find the hex code of your color by looking up a hex color picker in your browser. After you've pasted the hex code you should be able to see the thread with a different color, mixing with the other threads to create new colors. 

Fill in all the input fields with your own colors, and experiment with new combos to make a beautiful and balanced canvas. After you're done, make sure to take a screenshot of your work, now you know exactly which threads to use and where when making your carpet by looking at the screenshot.



# About the project

This is a small project made for my mother in c++ 17 with raylib and raygui. The goal is to make an app that facilitates the creative process of making a pattern for a checkered double-weave carpet.