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
#include "define.h"

using namespace boorudownloader;
// Argument functions.
int enableVerbose() {
    verbose = true;
    terminal::debugMessage("Verbose enabled.");
    return 0;
}

int help() {
    std::cout << 
    "booruDownloader\n" <<
    "Version: " << VER << "\n" <<
    "2024 - JPD\n" <<
    "Made with love <3\n\n" <<
    "HELP:\n" <<
    "Command usage: `boorudownloader {arguments}`\n" <<
    "Arguments:\n" <<
    "-h / --help: Print this menu.\n" <<
    "-v / --verbose: Print all messages and updates to console.\n" <<
    "-l / --limit: Set a limit for media to fetch. Usage: `-l 50`\n" <<
    "-t / --tags: Set tags to search by. To filter by multiple tags, use comma separation.\n" <<
    "-o / --out: Specify output directory.\n";
    exit(0);
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
        if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            help();
        }
        if(strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0) {
            enableVerbose();
        } 
        if(strcmp(argv[i], "--limit") == 0 || strcmp(argv[i], "-l") == 0) {
            argD.limit = std::stoi(argv[i+1]);
        }
        if(strcmp(argv[i], "--tags") == 0 || strcmp(argv[i], "-t") == 0) {
            argD.tags = argv[i+1];
            argD.tags = tagSanitize(argD.tags);
            terminal::message("Filtering by tags: "+argD.tags);
        }
        if(strcmp(argv[i], "--out") == 0 || strcmp(argv[i], "-o") == 0) {
            argD.out = argv[i+1];

        }
    };
    return argD;
}