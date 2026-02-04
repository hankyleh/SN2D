#include <iostream>
#include <string>
#include <chrono>


// #include <filesystem>
// #include <vector>
// #include <fstream>
// #include <sstream>

#include <input.h>
#include <msg.h>
#include <parse.h>
// #include <echo.h>
#include <transport.h>


int main(int argc, char* argv[]){
    // check that input file exists

    auto start_time = std::chrono::steady_clock::now();
    std::string casename = std::string(argv[1]);
    

    

    // version data subroutine
    msg::startup(casename);

    // input data subroutine
    Parameters input_data = io::read(casename);

    // Input check subroutine

    // Input echo subroutine
    io::echo(input_data);

    // Transport solver subroutine
        // Will solve D.O. here


    // Calculate execution time and print in seconds

    auto end_time  = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    std::cout << "SN2D execution complete.\nExecution time: "<<duration.count()<<" seconds\n\n";
    



    return 0;
}