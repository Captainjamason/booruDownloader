//      booruDownloader - v2
//      main.cpp
//      Jamason P Davis
//      Copyright 2024
//      <3

#define debug = false
#define VERSION = "0.2.0";

// Project Includes
#include <iostream>
#include "term.h"
#include "args.h"

int main(int argc, char *argv[]) {
    boorudownloader::terminal term;
    boorudownloader::argHandler args; 
    term.initialize();
    args.parseArgs(argc, argv);
}