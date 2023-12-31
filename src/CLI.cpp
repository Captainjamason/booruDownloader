//       booruDownloader 
//       CLI.cpp
//       Jamason P Davis
//       Copyright 2023
//       <3

#include "../include/baseCLI.h"
#include <iostream>
#include <string>

using namespace booruDownloader;
void CLI::error() {
    std::cout << "[" << CLI::color::textSet(CLI::color::fgRed) << "ERROR" << CLI::color::textSet(CLI::color::clrCode::fgDefault) << "]\n";
}

void CLI::noTags() {
    CLI::error();
    std::cout << "No tags passed, Please enter a comma seperated list of tags to filter and download.\n";
}

void CLI::noArgs() {
    CLI::error();
    std::cout << "No arguments passed. Please use --help or -h\n";
}

void CLI::invalidArgs() {
    CLI::error();
    std::cout << "Invalid arguments passed. Please use --help or -h\n";
}

void CLI::version(std::string buildtype, float ver) {
    std::cout << "[" << CLI::color::textSet(CLI::color::fgBlue) << "booruDownloader" << CLI::color::textReset() << "]\n"
    << buildtype << " " << ver << "\n"
    << "Made by Jamason 'Captainjamason' Davis\n"
    << CLI::color::textSet(CLI::color::fgRed) << "<3" << CLI::color::textReset() << "\n";
}

void CLI::help() {
    std::cout << "[" << CLI::color::textSet(CLI::color::fgYellow) << "booruDownloader - Help" << CLI::color::textReset() << "]\n"
    << CLI::color::textSet(CLI::color::fgGreen) << "--version" << CLI::color::textReset() <<  ": Shows the current version installed.\n"
    << CLI::color::textSet(CLI::color::fgGreen) << "-h || --help" << CLI::color::textReset() << ": Shows this help menu.\n"
    << CLI::color::textSet(CLI::color::fgGreen) << "-t || --tags" << CLI::color::textReset() << ": Define a comma seperated list of tags to filter by.\n"
    << CLI::color::textSet(CLI::color::fgGreen) << "-l || --limit" << CLI::color::textReset() << ": Define a limit to how many posts should be fetched and downloaded.\n"
    << CLI::color::textSet(CLI::color::fgGreen) << "-v || --verbose" << CLI::color::textReset() << ": Verbose output, Useful if something isn't working quite right.\n";
}