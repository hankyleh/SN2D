#ifndef ECHO_H
#define ECHO_H

#include <string>
#include <iostream>

#include <input.h>

namespace io {
void echo(Parameters input_data);
std::string add_spaces(std::string msg, int len);
void write_and_print(std::string msg, std::ostream& outfile);
} // namespace io

#endif