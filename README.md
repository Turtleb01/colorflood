# Colorflood by Turtleb01

This is an old learning project of mine. Most code was written around 2020.

## Requirements
gcc

make

Terminal with color support (most modern X terminals)

/dev/urandom (works on Linux and macOS but not windows)

## Installation
```
make
```
```
sudo make install
```
(requires /usr/local/bin/)

## Usage
Change color of the top left corner with keys 1-8 or a-h <enter>. Quit the game with q <enter>. 

You can create boards with custom sizes:
```
colorflood 50 25 4
```
creates 50x25 board with 4 different colors. Minimum and maximum values can be seen by inserting too big or too little values. With less than 3 arguments, board defaults to maximum size for user's terminal and 6 colors.
