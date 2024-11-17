//  args.cpp
//  booruDownloader v2
//  JPD - 2024

#include <iostream>
#include <vector>
#include "args.h"

using boorudownloader::argHandler;
argHandler argH;

void argHandler::parseArgs(int argc, char *argv[]) {
    argH.args
    for(int i = 0; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
}