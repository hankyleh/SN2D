#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include <msg.h>
#include <version.h>

void msg::startup(std::string casename) {
  std::string version = std::to_string(version_major) + "." +
                        std::to_string(version_minor) + "." +
                        std::to_string(version_revision);

  // create output file
  std::string output_name;
  output_name = casename + ".out";
  std::ofstream out_file(output_name);

  std::cout << "\n";

  print_and_record("SN2D: Discrete ordinates transport code\n\n", out_file);
  print_and_record( "Version : v" + version + "\n", out_file);
  print_and_record("Author  : Kyle H. Hansen\n\n", out_file);

  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream datetime;
  datetime << std::put_time(std::localtime(&in_time_t), "%Y/%m/%d %X");

  print_and_record(datetime.str() + "\n", out_file);
  print_and_record(casename + "\n\n", out_file);

  out_file.close();
}

void msg::print_and_record(std::string msg, std::ofstream &out_file ) {
  std::cout << msg;
  out_file << msg;
}