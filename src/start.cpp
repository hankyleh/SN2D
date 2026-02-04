#include <string>
#include <iostream>

#include <version.h>
#include <start.h>

void start::startup(){
    std::string version = std::to_string(version_major)+"."+
                          std::to_string(version_minor)+"."+
                          std::to_string(version_revision);
    std::cout << "\nSN2D Version "<< version <<std::endl;
}
