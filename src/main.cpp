#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include <filesystem>

#include <echo.h>
#include <input.h>
#include <msg.h>
#include <parse.h>
#include <transport.h>
#include <vec.h>

int main(int argc, char *argv[]) {
  // check that input file exists

  auto start_time = std::chrono::steady_clock::now();
  std::filesystem::path input_path = argv[1];
  if (!std::filesystem::exists(input_path)) {
    throw std::runtime_error("Input file " +
                             input_path.relative_path().string() +
                             " does not exist");
  }
  std::filesystem::path output_path = input_path;
  output_path.replace_extension(".out");
  std::string casename = input_path.stem().u8string();
  std::ofstream outstream;


  // version data subroutine
  outstream.open(output_path, std::ios::trunc);
  msg::startup(casename, outstream);
  outstream.close();


  // input data subroutine
  Parameters input_data = io::read(input_path.u8string());


  // Input check subroutine
  io::parse(input_data);


  // Input echo subroutine
  outstream.open(output_path, std::ios::app);
  io::echo(input_data, outstream);
  outstream.close();


  // Transport solver subroutine
  vec2d result = transport::inner(input_data, output_path);


  // Calculate execution time and print in seconds
  auto end_time = std::chrono::steady_clock::now();
  std::chrono::duration<double> duration = end_time - start_time;
  outstream.open(output_path, std::ios::app);
  msg::print_and_record("\n----------------------------\n", outstream);
  msg::print_and_record("---- execution complete ----\n", outstream);
  msg::print_and_record("----------------------------\n\n", outstream);
  msg::print_and_record("Execution time " + std::to_string(duration.count()) +
                            " seconds\n",
                        outstream);
  std::cout << "\n";
  outstream.close();
  return 0;
}