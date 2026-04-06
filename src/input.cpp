#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <input.h>

Parameters io::read(std::string input_name) {

  // Check for valid input file

  // permissible extensions
  // std::vector<std::string> extensions = {".txt", ".inp", ".in", ".i"};

  std::filesystem::path input_path = input_name;

  std::string name;
  std::string casename;

  if (std::filesystem::exists(input_path)) {
    casename = input_path.stem();
  } else {
    throw std::runtime_error("Cannot find input file at" +
                             std::filesystem::absolute(input_path).u8string());
  }

  // transcribe contents of input file to 2d vector of strings
  std::vector<std::vector<std::string>> params;
  std::string line;
  std::string buffer;
  std::ifstream input_file(input_name);

  while (std::getline(input_file, line)) {
    // ignore any blank lines
    if (line != "") {
      std::istringstream linestream(line);
      std::vector<std::string> linevec;
      while (linestream >> buffer) {
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
  while (h_x.size() < I) {
    line_no++;

    for (std::string i : params[line_no]) {
      h_x.push_back(std::stod(i));
    }
  }

  // h_x vector should end with a new row
  if (h_x.size() != I) {
    err_msg(params[line_no], line_no + 1);
  }

  while (h_y.size() < J) {
    line_no++;

    for (std::string i : params[line_no]) {
      h_y.push_back(std::stod(i));
    }
  }

  // h_y vector should end with a new row
  if (h_y.size() != J) {
    err_msg(params[line_no], line_no + 1);
  }

  // Number of angles per octant
  int K;

  line_no++;
  count_args(params[line_no], 1, line_no + 1);
  K = std::stoi(params[line_no][0]);

  // Angular Quadrature
  std::vector<double> mu, eta, w;

  for (int i = 0; i < K; i++) {
    line_no++;
    count_args(params[line_no], 3, line_no + 1);
    mu.push_back(std::stod(params[line_no][0]));
    eta.push_back(std::stod(params[line_no][1]));
    w.push_back(std::stod(params[line_no][2]));
  }

  // Number of materials
  int M;
  line_no++;
  count_args(params[line_no], 1, line_no + 1);
  M = std::stoi(params[line_no][0]);

  // Macroscopic Cross Sections
  std::vector<double> sigma_tot, sigma_sca;                // xs by material
  std::vector<std::vector<double>> sig_t_func, sig_s_func; // xs by position

  for (int m = 1; m < M + 1; m++) {
    line_no++;
    count_args(params[line_no], 2, line_no + 1);
    sigma_tot.push_back(std::stod(params[line_no][0]));
    sigma_sca.push_back(std::stod(params[line_no][1]));
  }

  // Boundary conditions
  std::vector<int> bc_x, bc_y;

  line_no++;
  count_args(params[line_no], 4, line_no + 1);
  bc_x.push_back(std::stoi(params[line_no][0]));
  bc_x.push_back(std::stoi(params[line_no][1]));

  bc_y.push_back(std::stoi(params[line_no][2]));
  bc_y.push_back(std::stoi(params[line_no][3]));

  // Material and Source Assignment
  std::vector<std::vector<int>> mat_id;
  std::vector<std::vector<double>> source;

  for (int i = 0; i < I; i++) {
    mat_id.push_back({});
    source.push_back({});
    sig_t_func.push_back({});
    sig_s_func.push_back({});

    for (int j = 0; j < J; j++) {
      mat_id[i].push_back(0);
      source[i].push_back(0);
      sig_t_func[i].push_back(0);
      sig_s_func[i].push_back(0);
    }
  }

  line_no++;
  for (int j = J - 1; j > -1; j--) {
    count_args(params[line_no + j], I, line_no + 1);
    for (int i = 0; i < I; i++) {
      mat_id[i][j] = std::stoi(params[line_no + j][i]);
      sig_t_func[i][j] = sigma_tot[mat_id[i][j] - 1];
      sig_s_func[i][j] = sigma_sca[mat_id[i][j] - 1];
    }
  }

  line_no += J;
  for (int j = J - 1; j > -1; j--) {
    count_args(params[line_no + j], I, line_no + 1);
    for (int i = 0; i < I; i++) {
      source[i][j] = std::stod(params[line_no + j][i]);
    }
  }

  line_no += J;
  double epsilon = std::stod(params[line_no][0]);
  int max_iter = std::stoi(params[line_no][1]);

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
  input_data.sig_tot = sig_t_func;
  input_data.sig_sca = sig_s_func;
  input_data.sig_tot_m = sigma_tot;
  input_data.sig_sca_m = sigma_sca;
  input_data.bc_x = bc_x;
  input_data.bc_y = bc_y;
  input_data.mat_id = mat_id;
  input_data.source = source;
  input_data.epsilon = epsilon;
  input_data.max_iterations = max_iter;

  return input_data;
}

void io::count_args(std::vector<std::string> row, int exp, int row_number) {
  if (row.size() != exp) {
    std::string row_string;
    for (std::string i : row) {
      row_string = row_string + i + "  ";
    }
    std::string msg = "\n\tExpected row #" + std::to_string(row_number) +
                      " to be length " + std::to_string(exp) + " (was " +
                      std::to_string(row.size()) + ")" +
                      "\n\tRow contents:\n\t\t" + row_string;
    std::cout << msg << std::endl << std::endl;
    throw std::runtime_error("Invalid input file");
  }
}

void io::err_msg(std::vector<std::string> row, int row_number) {
  std::string row_string;
  for (std::string i : row) {
    row_string = row_string + i + "  ";
  }
  std::string msg = "\n\tInvalid input in row " + std::to_string(row_number) +
                    "\n\tRow contents:\n\t\t" + row_string;
  std::cout << msg << std::endl << std::endl;
  throw std::runtime_error("Invalid input file");
}