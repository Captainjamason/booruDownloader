//      booruDownloader 
//      main.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

// Project Includes
#include "../include/download.h"
#include "../include/danbooruFetch.h"
#include "../include/baseCLI.h"
#include <codecvt>
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <string>
#include <vector>

// These variables are hard source linked vars defining if its indev or release.
// TODO: Move these to a seperate config that is loaded on runtime, allowing for more flexibility.
std::string VERSION = "0.1.1";
std::string BUILDTYPE = "indev";

// Call booruDownloader namespace.
using namespace booruDownloader;
int main(int argc, char *argv[])
{
    std::string rating;
    int limit = 0;
    // If there is more or equal to 2 arguments (including filename) then iterate to figure what commands were called.
    // TODO: Clean this up, its kinda gross, I don't like iterating all of this with if-else statements.
    if(argc > 1) {
        // Iterate args.
        std::vector<std::string> args;
        for(int i=0; (i<argc); i++) {
            args.push_back(argv[i]);
            std::cout << "argv: " << argv[i] << "\n";
            std::cout << "vec: " << args[i] << "\n";
        }
        for(int i=1; (i<=args.size()); i++) {
            std::cout << "arg: " << args[i] << "\n";
            if(args[i] == "-h" || args[i] == "--help") {
                    CLI::help();
                    return 0;
                } else {
                if(args[i] == "--version") {
                    CLI::version(BUILDTYPE, VERSION);
                    return 0;
                } else
                if(args[i] == "-l" || args[i] == "--limit") {
                  limit = std::stoi(args[i+1]);
                } else
                if (args[i] == "-r" || args[i] == "--rating") {
                    rating = args[i+1];
                    std::cout << "Rating set to: " << rating << "\n";
                } else
                if (args[i] == "-t" || args[i] == "--tags") {
                    if(args[i+1] != "") {
                        std::cout << "Fetching Posts with tag(s): " << args[i+1] << "\n";
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
                        danbooruFetch::fetchPosts(tags, limit, rating);
                        return 0;
                    }
                    // call noTags if `-t` was called without adding a list.
                    else {
                        CLI::noTags();
                        return 1;
                    }
                }
            }
        }
    } else {
        CLI::noArgs();
        return 1;
    }
}