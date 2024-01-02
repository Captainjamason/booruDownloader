//      booruDownloader 
//      main.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

// Project Includes
#include "../include/download.h"
#include "../include/danbooruFetch.h"
#include "../include/baseCLI.h"
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <vector>

// These variables are hard source linked vars defining if its indev or release.
// TODO: Move these to a seperate config that is loaded on runtime, allowing for more flexibility.
float VERSION = 0.1;
std::string BUILDTYPE = "indev";

// Call booruDownloader namespace.
using namespace booruDownloader;
int main(int argc, char *argv[])
{
    // If there is more or equal to 2 arguments (including filename) then iterate to figure what commands were called.
    // TODO: Clean this up, its kinda gross, I don't like iterating all of this with if-else statements.
    if(argc >= 2) {
        // Iterate args.
        std::string string;
        for(int i=1; (argc = i); i++) {
            string = argv[i];
            // Version command:
            if(string == "--version") {
                CLI::version(BUILDTYPE, VERSION);
                return 0;
            } 
            // Help command:
            else if(string == "-h" || string == "--help") {
                CLI::help();
                return 0;
            }
            // Tag filtering:
            else if(string == "-t" || string == "--tags") {
                if(argv[i+1] != NULL) {
                    std::cout << "Fetching posts with tag(s): " << argv[i+1] << "\n";
                    std::vector<std::string> tags;
                    
                    std::string s = argv[i+1];
                    std::string delimiter = ",";
                    size_t pos = 0;

                    while((pos = s.find(delimiter)) != std::string::npos) {
                        std::string token = s.substr(0, pos);
                        tags.push_back(token);
                        s.erase(0, pos + delimiter.length());
                    }
                    tags.push_back(s);
                    danbooruFetch::fetchPosts(tags, 0);
                    return 0;
                }
                // call noTags if `-t` was called without adding a list.
                else {
                    CLI::noTags();
                    return 1;
                }
            } else {
                break;
            }
        };
        // bad argument call.
        CLI::invalidArgs();
        return 1;
    } else {
        // no argument call.
        CLI::noArgs();
        return 1;
    }
}
