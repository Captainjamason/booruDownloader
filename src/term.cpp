//  term.cpp
//  booruDownloader v2
//  JPD - 2024

#include "term.h"
#include <iostream>

using boorudownloader::terminal;

int terminal::initialize() {
    std::cout << "\x1B[2J";
    return 0;
}