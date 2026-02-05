#include <echo.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

void io::echo(Parameters input_data){
    std::ofstream out_file(input_data.casename+".out", std::ios::app);
    std::string buffer;

    out_file << "---- Input data ----\n\n";

    out_file << "Discrete Ordinates/Octant\n";
    out_file << "n          mu          eta         w\n";
    for (int n=0; n<input_data.K; n++){
        buffer = "";
        buffer = buffer + io::add_spaces(std::to_string(n+1), 11);
        buffer = buffer + io::add_spaces(std::to_string(input_data.mu[n]), 11);
        buffer = buffer + io::add_spaces(std::to_string(input_data.eta[n]), 11);
        buffer = buffer + io::add_spaces(std::to_string(input_data.w[n]), 11);
        out_file << buffer << std::endl;
    }

    out_file << "\n";

    out_file << "Boundary Conditions\n";
    out_file << "Left    Right   Bottom  Top \n";
    buffer = "";
    buffer = buffer + io::add_spaces(std::to_string(input_data.bc_x[0]), 8);
    buffer = buffer + io::add_spaces(std::to_string(input_data.bc_x[1]), 8);
    buffer = buffer + io::add_spaces(std::to_string(input_data.bc_y[0]), 8);
    buffer = buffer + io::add_spaces(std::to_string(input_data.bc_y[1]), 8);
    out_file << buffer << std::endl;
    out_file << std::endl;

    out_file << "Computational Cell data" << std::endl;
    out_file << "i  j  Material  dx    dy    SigmaT    SigmaS    Source" << std::endl;

    for (int i=0; i<input_data.I; i++){
        for (int j=0; j<input_data.J; j++){
            buffer = "";
            buffer = buffer + io::add_spaces(std::to_string(i+1), 3);
            buffer = buffer + io::add_spaces(std::to_string(j+1), 3);
            buffer = buffer + io::add_spaces(std::to_string(input_data.mat_id[i][j]), 10);

            std::ostringstream os;
            os << input_data.h_x[i];
            buffer = buffer + io::add_spaces(os.str(), 6);
            os.str("");
            os << input_data.h_y[j];
            buffer = buffer + io::add_spaces(os.str(), 6);
            buffer = buffer + io::add_spaces(std::to_string(input_data.sig_tot[i][j]), 10);
            buffer = buffer + io::add_spaces(std::to_string(input_data.sig_sca[i][j]), 10);
            buffer = buffer + std::to_string(input_data.source[i][j]);
            out_file << buffer << std::endl;
        }
    }
    out_file.close();
}

std::string io::add_spaces(std::string txt, int len){
    std::string result = txt;
    // TODO-- should round doubles that are too long
    for (int i=0; i<(len - txt.length()); i++){
        result = result + " ";
    }
    return result;
}