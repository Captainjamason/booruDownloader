//  args.cpp
//  booruDownloader v2
//  JPD - 2024

// Includes
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "args.h"
#include "term.h"

// For readability sake.
using boorudownloader::argHandler;
using boorudownloader::terminal;

// Argument functions.
int enableVerbose() {
    argHandler::argData argD;
    argD.verbose = true;
    terminal::message("Verbose enabled.");
    return 0;
}
int help() {
    std::cout << "help test\n";     /// Placeholder.
    return 0;
}
std::string tagSanitize(std::string tags) {
    size_t pos = 0;
    std::string toReplace = ",";
    std::string replace = "%20";
    while((pos = tags.find(toReplace, pos)) != std::string::npos) {
        tags.replace(pos, toReplace.length(), replace);
        pos += replace.length();
    }
    return tags;
}

// Primary argument handling function, called from main();
argHandler::argData argHandler::parseArgs(int argc, char *argv[]) {
    argHandler::argData argD;
    for(int i = 0; i < argc; i++) {
        if(strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0) {
            enableVerbose();
        } 
        if(strcmp(argv[i], "--limit") == 0 || strcmp(argv[i], "-l") == 0) {
            argD.limit = std::stoi(argv[i+1]);
            terminal::message("Limit set to: "+std::to_string(argD.limit));
        }
        if(strcmp(argv[i], "--tags") == 0 || strcmp(argv[i], "-t") == 0) {
            argD.tags = argv[i+1];
            argD.tags = tagSanitize(argD.tags);
            terminal::message("Filtering by tags: "+argD.tags);
        }
        if(strcmp(argv[i], "--out") == 0 || strcmp(argv[i], "-o") == 0) {
            argD.out = argv[i+1];
            terminal::message("Output directory: "+argD.out);
        }
    };
    return argD;
}