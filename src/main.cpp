//      booruDownloader - v2
//      main.cpp
//      Jamason P Davis
//      Copyright 2024
//      <3

#define debug = true 
#define VERSION = "0.2.0"

// Project Includes
#include <iostream>
#include "term.h"
#include "args.h"
#include "fetchData.h"

int main(int argc, char *argv[]) {
    boorudownloader::terminal term;
    boorudownloader::argHandler args; 
    term.initialize();

    args.parseArgs(argc, argv);

    boorudownloader::download();
    //term.draw("test", 0, 0);
}