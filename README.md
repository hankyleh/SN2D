# SN2D
2-dimensional discrete ordinates transport code for NE 523 computer projects

## Compilation Instructions

The makefile handles all of the compilation. To compile, just run the command `make` in either the main directory, or in `/src`.

## Execution Instructions

Input files should use the .txt extension, and the program is run using `sn2d filename`.

## Code Status

Code currently reads and checks parameters from an input file, and prepares the data to be used by the transport solver subroutine, which is not yet written.

No input check subroutine
No input echo subroutine

Command line input syntax will be changed in the future to include the input file extension (e.g. the file will be run with `sn2d filename.txt`) so that any input file extension except `.o` may be used.

