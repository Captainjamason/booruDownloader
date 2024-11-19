//  term.cpp
//  booruDownloader v2
//  JPD - 2024

#include <iostream>
#include <string>
#include "term.h"

using boorudownloader::terminal;

int terminal::initialize() {
    std::cout << "\x1B[2J\x1b[H";
    return 0;
}

int terminal::message(std::string s) {
    std::cout << "\x1b[32;1m[INFO]: \x1b[0m" << s << "\n";
    return 0;
}

int terminal::error(std::string s) {
    std::cout << "\x1b[31;1m[ERR]:  \x1b[0m" << s << "\n";
    return 0;
}   

int terminal::debugMessage(std::string s) {
    std::cout << "\x1b[36;1m[ERR]:  \x1b[0m" << s << "\n";
    return 0;
}   

int terminal::progUpdate(int pend, int err, int done, std::string s) {
    std::cout <<"\x1b[33m"<<pend<<"\x1b[0m/\x1b[31m"<<err<<"\x1b[0m/\x1b[32m"<<done<<"  |   "<<s<<"\x1b[0m         \r";
}