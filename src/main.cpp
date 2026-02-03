#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

#include <version.h>
#include <input.h>
#include <parse.h>
#include <echo.h>
#include <transport.h>


int main(int argc, char* argv[]){

    // check that input file exists
    std::string casename = std::string(argv[1]);


    std::vector<std::string> extensions = {".txt", ".inp", ".in", ".i"};

    int file_exists = 0;
    for (std::string ext : extensions){
        // std::cout << ext << std::endl;

    }

    // create output file
    std::string output_file;
    output_file = casename + ".out";
    std::cout << output_file << std::endl;
    std::cout << output_file << std::endl;
    

    // version data subroutine

    

    // input data subroutine



    // Input check subroutine
    // Input echo subroutine

    // Transport solver subroutine
        // Will solve D.O. here


    return 0;
}