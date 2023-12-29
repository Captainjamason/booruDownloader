//      booruDownloader
//      termcolor.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

#include "../include/baseCLI.h"
#include "iostream"

using namespace booruDownloader;

int CLI::color::textRed() {
    std::cout << "\033[" << CLI::color::clrCode::fgRed << "m";
    return 0;
}

int CLI::color::textReset() {
    std::cout << "\033[" << CLI::color::clrCode::fgDefault << "m";
    return 0;
}


int CLI::color::textGreen() {
    std::cout << "\033[" << CLI::color::clrCode::fgGreen << "m";
    return 0;
}


int CLI::color::textYellow() {
    std::cout << "\033[" << CLI::color::clrCode::fgYellow << "m";
    return 0;
}


int CLI::color::textBlue() {
    std::cout << "\033[" << CLI::color::clrCode::fgBlue << "m";
    return 0;
}