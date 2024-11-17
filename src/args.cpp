//  args.cpp
//  booruDownloader v2
//  JPD - 2024

#include <iostream>
#include "args.h"

using boorudownloader::argHandler;

void argHandler::parseArgs(int argc, char *argv[]) {
    for(int i = 0; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
}