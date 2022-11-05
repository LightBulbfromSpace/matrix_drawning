# Matrix Drawning App

This is an app which allows to create a picture on LED matrix. Code is written for 8x8 matrix but after changes in function main() in "matrix" variable (width and height) and "points" array (should be set number of all points) can be used for other sizes.

User's controll tool is a dot which can be moved around and change visibility, called "pointer" below the text. 

## Buttons usage and modes:

* UP, DOWN, LEFT, RIGTH - move pointer.
* MIDDLE - change visibility (turn on/off "pointer")
* SET - switch between two modes:
  * "Free moving" - pointer doesn't leave a trace.
  * "Drawning" - pointer leaves a trace. Unavailable when pointer is invisible.
* RESET - erases all drawn pointers.

Based on CMSIS, uses cmake+make bulding system.

## Requirements:
* Arm Toolchain: arm-none-eabi-gcc
* gdb-multiarch or arm-none-eabi-gdb debugger
* cmake >= 3.0
* make
* build-essential
* st-link utility for Linux
* git (recommended for clonning project)

## Usage:

Clone project via git or http download (not recommended).

Open terminal, cd to root project directory.

Run `cmake .` to generate Makefile, then run `make` or `make bin` or `make hex` depending on what format of firmware you want.

Flash firmware with command `make flash`.

To clean build artifacts run `make clean`. Also after modifying CMakeLists.txt you need to clean cmake cache via deleting CMakeCache.txt file (but NOT CMakeLists!)

## Usage in VScode:

Required VS extensions:
* CMake
* Cmake Tools
* C/C++ (IntelliSense, debugging, and code browsing)
* Cortex-Debug
* C/C++ Themes (optional)

Firstly, open working directory and setup toochain.

Visit https://code.visualstudio.com/docs/cpp/cmake-linux for details.

Setup variant: Debug or Release.

To build project run: "Terminal->Run Build task->Cmake: build"
Project can be rebuild with "Cmake: clean rebuild"

Also you can build artifacts (bin/hex/elf) from CMake extension tab.
