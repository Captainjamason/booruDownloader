//      booruDownloader 
//      main.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

#include "../include/download.h"
#include "../include/danbooruFetch.h"
#include "../include/baseCLI.h"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <string>
#include <vector>

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
                    std::cout << "Fetching posts with tag(s): " << argv[i+1] << "\n";
                    std::vector<std::string> tags;
                    //char* tmp = argv[i+1];
                    //char* word;
                    //word = strtok(tmp, ",");
                    //while(word != NULL) {
                        //tags.push_back(word);
                        //word = strtok(NULL, ",");
                        //std::cout << word;
                    //}
                    tags.push_back(argv[2]);
                    danbooruFetch::fetchPosts(tags, 1);
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
