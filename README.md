# The Rabbit: Computer Graphics Story

An interactive animated story with five scenes, built with **C++** and **OpenGL (GLUT)** as a computer graphics course project.

## Features
- Five scenes with animated characters and objects drawn from OpenGL primitives
- Texture-mapped backgrounds loaded from BMP images
- Mouse control to move between scenes
- Keyboard control to move the rabbit

## Controls
| Input | Action |
|---|---|
| Left mouse click | Go to the next scene |
| Left / Right arrow keys | Move the rabbit (scenes 2 and 3) |
| `Q` or `Esc` | Exit |

## Tech Stack
C++ · OpenGL · GLUT / freeglut · GLEW (Windows and Linux)

## Required Files
The program loads two background images from the same folder as the executable:
- `garden_bg.bmp` (800 x 600)
- `home_bg.bmp` (800 x 600)

Place them next to the program before running.

## How to Build
- **Windows (Visual Studio):** create a console project, add `The_Rabbit.cpp`, and link GLEW and freeglut.
- **macOS:** the code uses the built-in OpenGL and GLUT frameworks.
- **Linux:** link `GL`, `GLU`, `glut`, and `GLEW`.

## Author
Layan Alsubhi, Computer Science student at Umm Al-Qura University
