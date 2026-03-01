#ifndef ECHO_H
#define ECHO_H

#include <string>

#include <input.h>

namespace io {
void echo(Parameters input_data);
std::string add_spaces(std::string msg, int len);
} // namespace io

#endif