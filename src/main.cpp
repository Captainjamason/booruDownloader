//      booruDownloader 
//      main.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

#include "../include/download.h"
#include "../include/baseCLI.h"
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>

using namespace booruDownloader;
int main(int argc, char *argv[])
{
    if(argc == 1) {
        CLI::noArgs();
        return 1;
    } else {
        CLI::invalidArgs();
    }
}
