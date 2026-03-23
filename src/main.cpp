#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include <filesystem>
#include <vector> // only for demo, TODO remove
// #include <fstream>
// #include <sstream>

#include <echo.h>
#include <input.h>
#include <msg.h>
#include <parse.h>
#include <transport.h>

int main(int argc, char *argv[]) {
  // check that input file exists

  auto start_time = std::chrono::steady_clock::now();
  std::filesystem::path input_path = argv[1];
  std::string casename = input_path.stem().u8string();

  // version data subroutine
  msg::startup(casename);

  // input data subroutine
  Parameters input_data = io::read(input_path.u8string());

  // Input check subroutine
  io::parse(input_data);

  // Input echo subroutine
  io::echo(input_data);

  // Transport solver subroutine
  // Will solve D.O. here

  // Calculate execution time and print in seconds
  auto end_time = std::chrono::steady_clock::now();
  std::chrono::duration<double> duration = end_time - start_time;

  std::cout << "SN2D execution complete.\nExecution time: " << duration.count()
            << " seconds\n\n";

  return 0;
}