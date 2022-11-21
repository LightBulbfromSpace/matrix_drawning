# Matrix Drawning App

This is an app which allows to create a picture on LED matrix. Code is written for 8x8 matrix but can be used for other sizes after changes in function main() in "matrix" variable (width and height) and "points" array (should be set number of all points).

User's controll tool is a dot which can be moved around and change visibility, called "pointer" below the text. 

## Buttons usage and modes:

* UP, DOWN, LEFT, RIGTH - move pointer.
* MIDDLE - change visibility (turn on/off pointer)
* SET - switch between two modes:
  * "Free moving" - pointer doesn't leave a trace.
  * "Drawning" - pointer leaves a trace. Unavailable when pointer is invisible.
* RESET - erases all drawn points.

## Matrix pinout

   &nbsp;&nbsp;R6&nbsp;&nbsp;&nbsp;&nbsp;C4&nbsp;&nbsp;&nbsp;&nbsp;C6&nbsp;&nbsp;&nbsp;R2  
  &nbsp;\_\_|\_\_|\_\_|\_\_|\_\_|\_\_|\_\_|\_\_|\_\_\
  |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;R3&nbsp;&nbsp;&nbsp;&nbsp;R1&nbsp;&nbsp;&nbsp;C7&nbsp;&nbsp;&nbsp;R4&nbsp;&nbsp;|\
  |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|\
  |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|\
  |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|\
  |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|\
  |\_\_\_C5\_\_\_R5\_\_\_R7\_\_C1\_|\
  &nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;|\
  &nbsp;R8&nbsp;&nbsp;&nbsp;&nbsp;C3&nbsp;&nbsp;&nbsp;&nbsp;C8&nbsp;&nbsp;&nbsp;&nbsp;C2 

## Pins' mapping

* Matrix

  * Rows:     R1 - B7,   R2 - B6,  R3 - B8,  R4 - B4,
              R5 - A5,   R6 - B9,  R7 - A6,  R8 - A4
              
  * Columns:  C1 - B11,  C2 - B10, C3 - B0,  C4 - B14,
              C5 - A7,   C6 - B13, C7 - B15, C8 - B1
  
* Buttons
  * COM - GND
  * UP  - A3
  * DWN - A2
  * LFT - A1
  * RHT - A0
  * MID - C15
  * SET - C14
  * RST - C13

## Technical aspects:

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
