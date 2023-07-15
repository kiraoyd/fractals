# Fractal Art in C

## Kira Klingenberg 2023

### A Portfolio of work done for Dr.David Ely's Exploring Fractals graduate course at Portland State University.

This project is a collection of programs written in C using the Gkit library to harness the power of math to manipulate the pixels on a graphics window to generate fractal based art.
The fractal paradigms explored here are: Recursive Fractals, L-system Grammars, Iterated Function Systems, and Complex Number Fractals.
The 'fractals' directory contains a series of .c files that each run a different animation, displayed on a graphics window.

### To compile any .c file:

From the root project directory 'fractals', ```cd fractals``` to access the inner 'fractals' directory

To compile a program, execute this command on the linux command line from the 'fractals' directory: 

```cc <filename.c> -lm -lX11```

replacing <filename.c> with the actual .c filename.

### To run:

The resulting executable will always be named: ```a.out```. So to run the most recently compiled code execute ```./a.out``` on the linux command line.

### Recommended Runs:

Still Images:
>ifc.c
> 
>mandelbrot.c
> 
>p_tree.c

Animations (click and hold any point on the graphics screen to see animation):
>wireframe.c
> 
>spiro.c
> 
>lights_out.c

### Notes:

```demo.c``` is the provided Gkit demo file.

```complex.c``` is a test program to play with complex numbers, and can be ignored,

The files ending in .txt and .in are grammar strings used in the L-systems fractal animations, and can be ignored.

Still images generated from running some of the previous programs are stored in 'Images'.

The Directories postfixed with the word "Movie" contain mp4 movies generated from a frame-by-frame script run of one of fractal files, as well as all the .bmp and .jpeg still images needed to create the mp4.

```FPToolkit.c``` contains the Gkit graphics library functions, provided by the Ely family. 