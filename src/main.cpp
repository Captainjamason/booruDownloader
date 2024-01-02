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
#include <iterator>
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
            }
            else if(string == "-t" || string == "--tags") {
                if(argv[i+1] != NULL) {
                    std::cout << "Fetching posts with tag(s): " << argv[i+1] << "\n";
                    std::vector<std::string> tags;
                    
                    std::string s = argv[i+1];
                    std::string delimiter = ",";
                    size_t pos = 0;

                    while((pos = s.find(delimiter)) != std::string::npos) {
                        std::string token = s.substr(0, pos);
                        //std::cout << token << std::endl;
                        tags.push_back(token);
                        s.erase(0, pos + delimiter.length());
                    }
                    //std::cout << s << std::endl;
                    tags.push_back(s);
                    danbooruFetch::fetchPosts(tags, 0);
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
