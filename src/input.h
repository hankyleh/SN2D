#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <string>

struct Parameters{
    std::string casename;
    int I;
    int J;
    std::vector<double> h_x;
    std::vector<double> h_y;
    int K;
    std::vector<double> mu, eta, w;
    int M;
    std::vector<std::vector<double>> sig_tot, sig_sca; // by space
    std::vector<double> sig_tot_m, sig_sca_m; // by material id
    std::vector<int> bc_x, bc_y;
    std::vector<std::vector<int>> mat_id;
    std::vector<std::vector<double>> source;
};


namespace io{

    Parameters read(std::string casename);

    void count_args(std::vector<std::string> row, int exp, int row_number);

    void err_msg(std::vector<std::string> row,int row_number);

}

#endif