//       booruDownloader 
//       CLI.cpp
//       Jamason P Davis
//       Copyright 2023
//       <3

#include "../include/cli.h"
#include <iostream>
#include <string>

using namespace booruDownloader;
void CLI::error() {
    std::cout << "[" << CLI::color::textSet(CLI::color::fgRed) << "ERROR" << CLI::color::textSet(CLI::color::clrCode::fgDefault) << "]\n";
}

void CLI::info() {
    std::cout << "[" << CLI::colorizeText("INFO", CLI::color::fgBlue) << "]";
}

std::string CLI::colorizeText(std::string str, CLI::color::clrCode clr) {
    return CLI::color::textSet(clr)+str+CLI::color::textReset();
}
