//       booruDownloader 
//       CLI.cpp
//       Jamason P Davis
//       Copyright 2023
//       <3

#include "../include/baseCLI.h"
#include <iostream>
#include <string>

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

void CLI::version(char* buildtype, float ver) {
    std::cout << "[";
    CLI::color::textBlue();
    std::cout << "booruDownloader";
    CLI::color::textReset();
    std::cout << "]\n";
    std::cout << buildtype << " " << ver << "\n";
    std::cout << "Made by Jamason 'Captainjamason' Davis\n";
    CLI::color::textRed();
    std::cout << "<3";
    CLI::color::textReset();
    std::cout << "\n";
}

void CLI::help() {
    std::cout << "[";
    CLI::color::textYellow();
    std::cout << "booruDownloader Help";
    CLI::color::textReset();
    std::cout << "]\n";
    CLI::color::textGreen();
    std::cout << "--version";
    CLI::color::textReset();
    std::cout << ": Shows the current version installed.\n";
    CLI::color::textGreen();
    std::cout << "--help";
    CLI::color::textReset();
    std::cout << " || ";
    CLI::color::textGreen();
    std::cout << "-h";
    CLI::color::textReset();
    std::cout << ": Shows this help menu.\n";
}