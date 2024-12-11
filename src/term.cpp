//  term.cpp
//  booruDownloader v2
//  JPD - 2024

// Includes
#include <iostream>
#include <string>
#include "term.h"
#include "args.h"

using boorudownloader::terminal;

//  All of these functions are used to pretty up the terminal, and make it snappy to do so.
int terminal::initialize() {
    std::cout << "\x1B[2J\x1b[H\x1b[?25l";
    return 0;
}
int terminal::release() {
    std::cout << "\x1b[?25h\n";
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
    if(verbose == true) {
        std::cout << "\x1b[36;1m[DBG]:  \x1b[0m" << s << "\n";
    }
    return 0;
}   
bool terminal::prompt(std::string s) {
    bool r;
    std::string i; 

    std::cout << "\x1b[0m" << s << " [y/n]:\x1b[?25h ";
    std::cin >> i;
    if(i == "y") {
        r = true;
    } else {
        r = false;
    }
    std::cout << "\x1b[?25l";

    return r;
}

/// This function is the primary progress function of program.
int terminal::progUpdate(int pend, int err, int done, std::string s) {
    std::cout <<"\x1b[33mPend: "<<pend<<" \x1b[0m/\x1b[31m Err: "<<err<<" \x1b[0m/\x1b[32m Done: "<<done<<"\x1b[0m   |   "<<s<<"\x1b[K\r";
    return 0;
}