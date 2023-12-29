//       booruDownloader 
//       CLI.cpp
//       Jamason P Davis
//       Copyright 2023
//       <3

#include "../include/baseCLI.h"
#include <iostream>

using namespace booruDownloader;
void error() {
    std::cout << "[";
    CLI::color::textRed();
    std::cout << "ERROR";
    CLI::color::textReset();
    std::cout << "] ";
}

void CLI::noArgs() {
    error();
    std::cout << "No arguments passed. Please use --help or -h\n";
}

void CLI::invalidArgs() {
    error();
    std::cout << "Invalid arguments passed. Please use --help or -h\n";
}