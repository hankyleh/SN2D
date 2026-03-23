#ifndef MSG_H
#define MSG_H

#include <string>

namespace msg {
void startup(std::string casename);

void print_and_record(std::string msg, std::ofstream &out_file);

} // namespace msg

#endif