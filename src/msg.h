#ifndef MSG_H
#define MSG_H

#include <string>

namespace msg {
void startup(std::string casename);
std::string add_spaces(std::string txt, int len);
std::string add_spaces(int integer, int len);
std::string add_spaces(double number, int len);
void print_and_record(std::string msg, std::ofstream &out_file);
void record(std::string msg, std::ofstream &out_file);

} // namespace msg

#endif