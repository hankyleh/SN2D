#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include <msg.h>
#include <version.h>

void msg::startup(std::string casename, std::ofstream &out_file) {
  std::string version = std::to_string(version_major) + "." +
                        std::to_string(version_minor) + "." +
                        std::to_string(version_revision);

  // std::cout << "\n";
  print_and_record("\n***************************************\n\n", out_file);
  print_and_record("SN2D: Discrete ordinates transport code\n\n", out_file);
  print_and_record("Version : v" + version + "\n", out_file);
  print_and_record("Author  : Kyle H. Hansen\n\n", out_file);
  print_and_record("***************************************\n\n", out_file);

  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream datetime;
  datetime << std::put_time(std::localtime(&in_time_t), "%Y/%m/%d %X");

  print_and_record(datetime.str() + "\n", out_file);
  print_and_record("'" + casename + "'\n\n", out_file);
  print_and_record("-------------------------\n", out_file);
  print_and_record("---- begin execution ----\n", out_file);
  print_and_record("-------------------------\n\n", out_file);

  out_file.close();
}

std::string msg::add_spaces(std::string txt, int len) {
  std::string result = txt;
  for (int i = 0; i < (len - txt.length()); i++) {
    result = result + " ";
  }
  return result;
}

std::string msg::add_spaces(int integer, int len) {
  std::string result = std::to_string(integer);
  int ilen = result.length();
  for (int i = 0; i < (len - ilen); i++) {
    result = result + " ";
  }
  return result;
}

std::string msg::add_spaces(double number, int len) {
  std::string result = std::to_string(number);
  int dlen = result.length();
  if (dlen >= len) {
    result = result.substr(0, len - 1);
    dlen = len - 1;
  }
  for (int i = 0; i < (len - dlen); i++) {
    result = result + " ";
  }
  return result;
}

void msg::print_and_record(std::string msg, std::ofstream &out_file) {
  std::cout << msg;
  out_file << msg;
}

void msg::record(std::string msg, std::ofstream &out_file) { out_file << msg; }

std::string msg::sci_fmt(double value, int decimal){
  char result [decimal + 10];
  std::string prompt = "%."+std::to_string(decimal)+"e";
  int cx = sprintf(result, prompt.c_str(), value);
  return result;
}