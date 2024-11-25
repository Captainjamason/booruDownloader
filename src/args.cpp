//  args.cpp
//  booruDownloader v2
//  JPD - 2024

#include <iostream>
#include <vector>
#include <cstring>
#include "args.h"

using boorudownloader::argHandler;

int enableVerbose() {
    std::cout << "\x1b[35;1mVerbose enabled\n\x1b[0m";
    return 0;
}

int help() {
    std::cout << "help test\n";
    return 0;
}

argHandler::argData argHandler::parseArgs(int argc, char *argv[]) {
    argHandler::argData argD;
    for(int i = 0; i < argc; i++) {
        if(strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0) {
            enableVerbose();
        } 
        if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            help();
        }
        if(strcmp(argv[i], "--limit") == 0 || strcmp(argv[i], "-l") == 0) {
            argD.limit = std::stoi(argv[i+1]);
            std::cout << "\x1b[32mLimit set to: " << argv[i+1] << "\x1b[0m\n";
        }
        if(strcmp(argv[i], "--tags") == 0 || strcmp(argv[i], "-t") == 0) {
            argD.tags = argv[i+1];
            std::cout << "\x1b[32mTags set to: " << argv[i+1] << "\x1b[0\n";
        }
    };
    return argD;
}