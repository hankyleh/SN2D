#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>

#include <version.h>
#include <msg.h>

void msg::startup(std::string casename){
    std::string version = std::to_string(version_major)+"."+
                          std::to_string(version_minor)+"."+
                          std::to_string(version_revision);

    // create output file
    std::string output_name;
    output_name = casename + ".out";
    std::ofstream out_file(output_name);

    std::cout << "\n";

    print_and_record(out_file, "SN2D: Discrete ordinates transport code\n\n");
    print_and_record(out_file, "Version : v"+ version +"\n");
    print_and_record(out_file, "Author  : Kyle H. Hansen\n\n");

    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream datetime;
    datetime << std::put_time(std::localtime(&in_time_t), "%Y/%m/%d %X");

    print_and_record(out_file, datetime.str()+"\n");
    print_and_record(out_file, casename+"\n\n");

    out_file.close();
}

void msg::print_and_record(std::ofstream& out_file, std::string msg){
    std::cout << msg;
    out_file << msg;
}
