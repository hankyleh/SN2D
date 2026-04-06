# SN2D
2-dimensional discrete ordinates transport code for NE 523 computer projects

Note for Code #4: input and output files are located in `examples/source_island.*`

## Compilation Instructions

The makefile handles all of the compilation. Navigate to the main directory, then run the makefile for the desired target:

- Main module: `make`

- Single-cell DD test: `make ddsolve`

## Execution Instructions

#### Main Module (`sn2d`)

The program is run using `./sn2d input_name`. Specify the relative path of both the `sn2d` executable and the input file. For example, `./sn2d examples/source_island.inp` or `../sn2d ./source_island.inp`.

#### Single-cell Diamond Difference test (`test`)

The ddsolve test program is run in the same way as the main executable, for example, from the `/examples` directory, run `../test hw2/ddsolve_test.inp`.

## Input format
Fortran free format. Input file may have any extension, and comments begin with `#`.
#### Main module
```
I J                  # Number of computational cells [2 integers]
dx dx dx...          # Cell widths in x-direction [I floats]
dy dy dy...          # Cell widths in y-direction [J floats]
K                    # Angles per octant [1 integer]
mu_1  eta_1  w_1     # Angular quadrature [K rows of 3 floats]
....  ....   ...     
M                    # Number of materials [1 integer]
total_1 scatter_1    # Cross sections [M rows of 2 floats]
.....   ..... 
1 1 1 1 1            # Material IDs [J rows of I integers 1-M]
1 2 2 2 1
1 2 2 2 1
1 2 2 2 1
1 1 1 1 1

0.0 0.0 0.0 0.0 0.0  # Source strength [J rows of I floats]
0.0 1.0 1.0 1.0 0.0  # Units 1/(cm^2 sec ster)
0.0 1.0 1.0 1.0 0.0
0.0 1.0 1.0 1.0 0.0
0.0 0.0 0.0 0.0 0.0

1e-3  50             # convergence tolerance and max. iterations
```
#### Single-cell Diamond Difference test (`test`)
```
dx dy              # cell dimensions
mu eta             # angle
sigma              # cross section
source             # source strength
psi_in_j psi_i_in  # L/R flux in, Top/Bottom flux in
```

## Code Status

Code currently reads and checks parameters from an input file, prepares the data to be used by the transport solver subroutine, then performs source iteration until convergence is reached or maximum number of iterations is reached.

TODO:

- Input parse needs to be concurrent with reading; check data types immediately
