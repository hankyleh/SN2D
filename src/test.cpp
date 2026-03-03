#include <transport.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

struct input_data {
  double dx;
  double dy;
  double mu;
  double eta;
  double sigma;
  double source;
  double psi_in_j;
  double psi_i_in;
};

input_data read_input(std::string input_name) {
  input_data result;

  // Read input file to vector of strings,
  // ignore blank lines
  std::ifstream input_file(input_name);
  std::vector<std::string> input_strings;

  std::string line;
  std::string buffer;
  while (std::getline(input_file, line)) {
    if (line != "") {
      std::istringstream linestream(line);
      while (linestream >> buffer) {
        input_strings.push_back(buffer);
      }
    }
  }
  input_file.close();

  if (input_strings.size() != 8){
    throw std::runtime_error("Wrong number of inputs in "+input_name);
  }

  result.dx = std::stod(input_strings[0]);
  result.dy = std::stod(input_strings[1]);
  result.mu = std::stod(input_strings[2]);
  result.eta = std::stod(input_strings[3]);
  result.sigma = std::stod(input_strings[4]);
  result.source = std::stod(input_strings[5]);
  result.psi_in_j = std::stod(input_strings[6]);
  result.psi_i_in = std::stod(input_strings[7]);
  return result;
}

void print_output(std::string output_name, transport::dd_out data) {
    std::ofstream outfile(output_name);

    outfile << "Cell-centered flux: ";
    outfile << data.psi_i_j << std::endl;
    outfile << "Flux, out, j: ";
    outfile << data.psi_out_j << std::endl;
    outfile << "Flux, i, out: ";
    outfile << data.psi_i_out;

    outfile.close();
}

int main(int argc, char *argv[]) {
    std::filesystem::path input_path(argv[1]);
    std::string input_file = input_path.string();
    std::string output_file = input_path.replace_extension(".out").string();
    
  input_data d = read_input(input_file);

  transport::dd_out output =  transport::ddsolve(d.dx, d.dy, d.mu,
                                   d.eta, d.sigma, d.source,
                                   d.psi_in_j, d.psi_i_in);

     print_output(output_file, output);


  return 0;
}
