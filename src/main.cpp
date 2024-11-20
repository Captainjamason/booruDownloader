//      booruDownloader - v2
//      main.cpp
//      Jamason P Davis
//      Copyright 2024
//      <3


// Project Includes
#include <iostream>
#include <algorithm>
#include <string>
#include "term.h"
#include "args.h"
#include "download.h"

int main(int argc, char *argv[]) {
    boorudownloader::argHandler args; 

    boorudownloader::terminal::initialize();

    boorudownloader::argHandler::argData argD = args.parseArgs(argc, argv);

    boorudownloader::download(argD.tags, argD.limit);
    std::cout << "\x1b[?25h\n";
}