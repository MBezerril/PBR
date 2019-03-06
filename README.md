# Changes 2

## Inserted the pinhole camera and the assimp:
The perspective camera (pinhole):
The pinhole works on a simples principle: the rays are now traced from the pin (a point created at some pre defined distance on camera creation) in direction of each pixel in a matrix created in the camera creation. This simple modification create the sens of perspective.

## The assimp:
Assimp is a opensource model loader that can load most of the 3D files formats, write in C++ and easy to use. 
There is some data structures to handle 3D model objects, but if you want to use your own 3D models structs, it can be easily converted reading the points from the Assimp struct and save in you own. (we made it :D)
Official site: http://www.assimp.org/index.php
GitHub repository: https://github.com/assimp/assimp

# Changes 1
Created and tested the triangle algorithm and was used the *Fast, Minimum Storage Ray/Triangle Intersection (Möller, T.; Trumbore, B.)*

The first try didn't go very well, but was a point position mistake.

*The speed and memory tests wasn't make yet, we still need the second triangle intersection algotihm to make the comparisions*

Output image rendered can be found in the *Output* folder with the "*Tringle.jpg*


# RT-Template

A very simple C++11 template code for the development of ray tracers.
The template that the project was based on, was created by Christian Pagot:
https://github.com/capagot/RT-Template

# Dependencies

This software depends on the following third party software to be compiled:

- glm version 0.9.7.0 or later (http://glm.g-truc.net).

# Compiling and Running

I've compiled and executed this software only in Linux (Ubuntu 14.04).
These are the steps needed in order to compile the program:

1. Install the dependencies (i.e. glm).
2. Download the source code together with the Makefile.
3. Open the Makefile with a text editor (e.g. vim, gedit, etc.).
4. Configure the variables CPPFLAGS and LDFLAGS in order to reflect your glm installations.
5. Save the Makefile.
6. Call 'make DEBUG=0' at the project root directory.
7. Done

To render the hardcoded scene, just issue the following command from the project root directory: 

    $ ./swpathtracer
