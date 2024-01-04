//      booruDownloader
//      termcolor.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

#include "../include/cli.h"
#include "iostream"
#include <string>

using namespace booruDownloader;

// Rewrote the color set code, It's now one function and works great! I wish there was a way to auto reset but I'm much happier with this.
std::string CLI::color::textSet(CLI::color::clrCode colorCode) {
    std::string string("\033[");
    std::string color(std::to_string(colorCode));
    string.append(color);
    string.append("m");
    return string;
}

// This function is extremely similar to textSet(), only difference is it *only* calls fgDefault.
std::string CLI::color::textReset() {
    std::string string("\033[");
    std::string color(std::to_string(CLI::color::fgDefault));
    string.append(color);
    string.append("m");
    return string;
}