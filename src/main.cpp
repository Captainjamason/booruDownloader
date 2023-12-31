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
#include <string>

float VERSION = 0.1;
std::string BUILDTYPE = "indev";

using namespace booruDownloader;
int main(int argc, char *argv[])
{
    if(argc >= 2) {
        std::string string;
        for(int i=1; (argc = i); i++) {
            string = argv[i];
            if(string == "--version") {
                CLI::version(BUILDTYPE, VERSION);
                return 0;
            } else if(string == "-h" || string == "--help") {
                CLI::help();
                return 0;
            } else if(string == "--debug-download") {
                download::downloadImage("https://testbooru-cdn.donmai.us/original/3a/0e/3a0e769991323dcf9748adba9ab530dc.jpg");
                return 0;
            } else if(string == "-t" || string == "--tags") {
                if(argv[i+1] != NULL) {
                    std::string tags = argv[i+1];
                    std::cout << tags << "\n";
                    return 0;
                }
                else {
                    CLI::noTags();
                    return 1;
                }
            } else {
                break;
            }
        };
        CLI::invalidArgs();
        return 1;
    } else {
        CLI::noArgs();
        return 1;
    }
}
