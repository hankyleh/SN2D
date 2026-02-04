#include <parse.h>
#include <input.h>

#include <iostream>
#include <string>
#include <cmath>


void io::parse(Parameters input_data){
    // I, J
        // must be positive integers
        if (input_data.I <=0 || input_data.J <=0){
            parse_err("I and J must be positive integers");
        }

    // Cell widths
        // must be positive real numbers
        for (auto i : input_data.h_x){
            if (i <=0){
                parse_err("Cell widths must be positive");
            }
        }
        for (auto i : input_data.h_y){
            if (i <=0){
                parse_err("Cell widths must be positive");
            }
        }

    // Quadrature
        // K must convert to integer N
        double N = std::sqrt((8*input_data.K)+1) - 1;
        if (std::abs(std::fmod(N, 1)) !=0){
            parse_err("sqrt(8K + 1) - 1 must be an integer");
        }
        // mu, eta, w must exist and be positive for each k
        for (int k=0; k<input_data.K; k++){
            if (input_data.mu[k]<=0 || input_data.eta[k]<=0 || input_data.w[k]<=0){
                parse_err("Angular quadrature values must be positive");
            }
        }

    // Materials and xs data
        // M must be positive integer
        if (input_data.M <1){
            parse_err("Number of materials must be integer >= 1");
        }
        // xs must be non-negative reals, sig_s < sig_t
        for (int m=0; m<input_data.M; m++){
            if (input_data.sigma_sca[m]<0 || input_data.sigma_tot[m]<0){
                parse_err("Cross sections must be non-negative");
            }
            if (input_data.sigma_sca[m] > input_data.sigma_tot[m]){
                parse_err("SigmaS must be < SigmaTot");
            }
        }

    // BCs
        // must be zero or one.

        for (int i=0; i<2; i++){
            if ((input_data.bc_x[i] != 0 && input_data.bc_x[i] != 1) ||
                (input_data.bc_y[i] != 0 && input_data.bc_y[i] != 1)){
                    parse_err("All Boundary Conditions must be 0 or 1");
                }
        }

    // Material Assignment
        for (int i=0; i<input_data.I; i++){
            for (int j=0; j<input_data.J; j++){
                if (input_data.mat_id[i][j] > input_data.M || input_data.mat_id[i][j] < 1){
                    parse_err("All material IDs must be {1, ..., M}");
                }
            }
        }

    // Source
        // non-negative real
        for (int i=0; i<input_data.I; i++){
            for (int j=0; j<input_data.J; j++){
                if (input_data.source[i][j] < 0){
                    parse_err("Source must be non-negative");
                }
            }
        }
    
}

void io::parse_err(std::string msg){
    msg = "\n\t"+msg;
    std::cout << msg << std::endl << std::endl;
    throw std::runtime_error("Invalid input file");
}