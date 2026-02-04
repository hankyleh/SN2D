# SN2D
2-dimensional discrete ordinates transport code for NE 523 computer projects

## Compilation Instructions

The makefile handles all of the compilation. To compile, just run the command `make` in either the main directory, or in `/src`.

## Execution Instructions

Input files should use the .txt extension, and the program is run using `sn2d filename`. The program *must* be run from the directory where the input file is located (for now). For example, to run `hw1.inp`, first navigate to `/examples` then run `../sn2d hw1`.

## Code Status

Code currently reads and checks parameters from an input file, and prepares the data to be used by the transport solver subroutine, which is not yet written.

TODO:

- Input parse needs to be concurrent with reading; check data types immediately

- Command line input syntax will be changed in the future to include the input file extension (e.g. the file will be run with `sn2d filename.txt`) so that any input file extension except `.out` may be used.

