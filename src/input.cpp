#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

#include <input.h>


Parameters io::read(std::string casename){

    // Check for valid input file

    // permissible extensions
    std::vector<std::string> extensions = {".txt", ".inp", ".in", ".i"};

    int file_exists = 0;
    std::string name;
    std::string input_name;

        // TODO: program should be run with 'sn2d input.txt' instead of
        // 'sn2d input'. First, identify and truncate extension

    // check for file with each extension type
    for (std::string ext : extensions){
        name = casename + ext;
        if (std::filesystem::exists(name)){
            file_exists++;
            input_name = name;
        }
    }

    if (file_exists == 0){
        std::cout << "Input file must have txt, inp, in, or i extension!"<< std::endl << std::endl;
        throw std::runtime_error("Invalid input file!");
    }
    if (file_exists > 1){
        std::cout<<  "Input files must have a unique name" << std::endl << std::endl;
        throw std::runtime_error("Invalid input file!");
    }

    // transcribe contents of input file to 2d vector of strings
    std::vector<std::vector<std::string>> params;
    std::string line;
    std::string buffer;
    std::ifstream input_file(input_name);

    while(std::getline(input_file, line)){
        // ignore any blank lines
        if (line != ""){
            std::istringstream linestream(line);
            std::vector<std::string> linevec;
            while (linestream >> buffer){
                linevec.push_back(buffer);
            }
            params.push_back(linevec);
        }
        
    }

    // Number of x, y computational cells
    count_args(params[0], 2, 1);
    int I, J;
    I = std::stoi(params[0][0]);
    J = std::stoi(params[0][1]);

    // Cell sizes in x- and y-dimension
    std::vector<double> h_x, h_y;

    int line_no = 0;
    while (h_x.size() < I){
        line_no++;

        for (std::string i : params[line_no]){
            h_x.push_back(std::stod(i));
        }
    }

    // h_x vector should end with a new row
    if (h_x.size() != I){
        err_msg(params[line_no], line_no+1);
    }

    while (h_y.size() < I){
        line_no++;

        for (std::string i : params[line_no]){
            h_y.push_back(std::stod(i));
        }
    }

    // h_y vector should end with a new row
    if (h_x.size() != I){
        err_msg(params[line_no], line_no+1);
    }


    // Number of angles per octant
    int K;

    line_no++;
    count_args(params[line_no], 1, line_no+1);
    K = std::stoi(params[line_no][0]);

    // Angular Quadrature
    std::vector<double> mu, eta, w;

    for (int i=0; i<K; i++){
        line_no++;
        count_args(params[line_no], 3, line_no+1);
        mu.push_back(std::stod(params[line_no][0]));
        eta.push_back(std::stod(params[line_no][1]));
        w.push_back(std::stod(params[line_no][2]));
    }

    // Number of materials
    int M;
    line_no++;
    count_args(params[line_no], 1, line_no+1);
    M = std::stoi(params[line_no][0]);
    
    // Macroscopic Cross Sections

    std::vector<double> sigma_tot, sigma_sca;

    for (int m=1; m<M+1; m++){
        line_no++;
        count_args(params[line_no], 2, line_no+1);
        sigma_tot.push_back(std::stod(params[line_no][0]));
        sigma_sca.push_back(std::stod(params[line_no][1]));
    }


    // Boundary conditions
    std::vector<int> bc_x, bc_y;

    line_no++;
    count_args(params[line_no], 4, line_no+1);
    bc_x.push_back(std::stoi(params[line_no][0]));
    bc_x.push_back(std::stoi(params[line_no][1]));

    bc_y.push_back(std::stoi(params[line_no][0]));
    bc_y.push_back(std::stoi(params[line_no][1]));

    // Material and Source Assignment
    std::vector<std::vector<int>> mat_id;
    std::vector<std::vector<double>> source;

    
    for (int i=0; i<I; i++){
        mat_id.push_back({});
        source.push_back({});
        for (int j=0; j<J; j++){
            mat_id[i].push_back(0);
            source[i].push_back(0);
        }
    }

    // TODO: should create a vector of all cross sections, sigma[i][j]

    line_no++;
    for (int j=J-1; j>-1; j--){
        count_args(params[line_no+j], I, line_no+1);
        for (int i=0; i<I; i++){
            mat_id[i][j] = std::stoi(params[line_no + j][i]);
        }
    }

    line_no+= J;
    for (int j=J-1; j>-1; j--){
        count_args(params[line_no+j], I, line_no+1);
        for (int i=0; i<I; i++){
            source[i][j] = std::stod(params[line_no + j][i]);
        }
    }

    // add all data to struct and output
    Parameters input_data;
    input_data.casename = casename;
    input_data.I = I;
    input_data.J = J;
    input_data.h_x = h_x;
    input_data.h_y = h_y;
    input_data.K = K;
    input_data.mu = mu;
    input_data.eta = eta;
    input_data.w = w;
    input_data.M = M;
    input_data.sigma_tot = sigma_tot;
    input_data.sigma_sca = sigma_sca;
    input_data.bc_x = bc_x;
    input_data.bc_y = bc_y;
    input_data.mat_id = mat_id;
    input_data.source = source;

    return input_data;
}

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
            buffer = buffer + io::add_spaces(std::to_string(i), 3);
            buffer = buffer + io::add_spaces(std::to_string(j), 3);
            buffer = buffer + io::add_spaces(std::to_string(input_data.mat_id[i][j]), 10);

            std::ostringstream os;
            os << input_data.h_x[i]+1;
            buffer = buffer + io::add_spaces(os.str(), 6);
            os << input_data.h_y[j]+1;
            buffer = buffer + io::add_spaces(os.str(), 6);
            buffer = buffer + io::add_spaces(std::to_string(input_data.sigma_tot[input_data.mat_id[i][j] - 1]), 10);
            buffer = buffer + io::add_spaces(std::to_string(input_data.sigma_sca[input_data.mat_id[i][j] - 1]), 10);
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

void io::count_args(std::vector<std::string> row, int exp, int row_number){
    if (row.size() != exp){
        std::string row_string;
        for (std::string i : row){
            row_string = row_string + i + "  ";
        }
        std::string msg = "\n\tExpected row #"+std::to_string(row_number)+
                          " to be length "+std::to_string(exp)+
                          " (was "+std::to_string(row.size())+")"+
                          "\n\tRow contents:\n\t\t"+row_string;

        std::cout << msg << std::endl << std::endl;
        throw std::runtime_error("Invalid input file");
    }
}

void io::err_msg(std::vector<std::string> row, int row_number){
    std::string row_string;
    for (std::string i : row){
        row_string = row_string + i + "  ";
    }
    std::string msg = "\n\tInvalid input in row "+std::to_string(row_number)+
                      "\n\tRow contents:\n\t\t"+row_string;
    std::cout << msg << std::endl << std::endl;
    throw std::runtime_error("Invalid input file");
}