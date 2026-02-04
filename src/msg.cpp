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




    out_file << "SN2D: Discrete ordinates transport code\n\n";
    out_file << "Version : "+ version +"\n";
    out_file <<  "Author  : Kyle H. Hansen\n\n";

    std::cout << "\n";
    std::cout << "SN2D: Discrete ordinates transport code\n\n";
    std::cout << "Version : "+ version +"\n";
    std::cout <<  "Author  : Kyle H. Hansen\n\n";


    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream datetime;
    datetime << std::put_time(std::localtime(&in_time_t), "%Y/%m/%d %X");

    out_file <<  datetime.str()+"\n";
    std::cout <<  datetime.str()+"\n";

    out_file << casename << "\n\n";
    std::cout << casename << "\n\n";

    out_file.close();
}
