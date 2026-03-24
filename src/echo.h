#ifndef ECHO_H
#define ECHO_H

#include <iostream>
#include <string>

#include <input.h>

namespace io {
void echo(Parameters input_data, std::ofstream &out_file);
} // namespace io

#endif