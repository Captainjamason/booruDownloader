//  term.cpp
//  booruDownloader v2
//  JPD - 2024

#include "term.h"
#include <iostream>
#include <string>

using boorudownloader::terminal;

void resPos() {
    std::cout << "\x1b[H";
}

int terminal::initialize() {
    std::cout << "\x1B[2J";
    resPos();
    return 0;
}

int terminal::draw(std::string str, uint16_t x, uint16_t y) {
    std::cout << "\x1B[ "<<x<<" ; "<<y<<" H";
    std::cout << str;
    resPos();
}