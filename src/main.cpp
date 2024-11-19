//      booruDownloader - v2
//      main.cpp
//      Jamason P Davis
//      Copyright 2024
//      <3

#define debug = true 
#define VERSION = "0.2.1"

// Project Includes
#include <iostream>
#include <algorithm>
#include <string>
#include "term.h"
#include "args.h"
#include "download.h"

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

int main(int argc, char *argv[]) {
    boorudownloader::argHandler args; 

    boorudownloader::terminal::initialize();

    boorudownloader::argHandler::argData argD = args.parseArgs(argc, argv);
    std::string tags = tagSanitize(argD.tags);

    boorudownloader::download(tags, argD.limit);
    std::cout << "\n";
}