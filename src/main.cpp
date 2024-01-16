//      booruDownloader 
//      main.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

// Project Includes
#include "../include/download.h"
#include "../include/danbooru.h"
#include "../include/cli.h"
#include "../include/config.h"
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <jsoncpp/json/value.h>
#include <string>
#include <vector>

// These variables are hard source linked vars defining if its indev or release.
// TODO: Move these to a seperate config that is loaded on runtime, allowing for more flexibility.
std::string VERSION = "0.1.2";
std::string BUILDTYPE = "indev";

// Call booruDownloader namespace.
using namespace booruDownloader;
int main(int argc, char *argv[])
{
    std::string outputDir;
    std::string rating;
    int limit = 0;

    // Basic configuration loading and handling, Exmaple configuration will be mocked up and added to installation commands.
    Json::Value config = config::loadConfig();
    if(config == NULL) {
        CLI::error();
        std::cout << "Invalid configuration syntax or no configuration file found. Exiting.\n";
        return 1;
    }

    // If there is more or equal to 2 arguments (including filename) then iterate to figure what commands were called.
    // TODO: Clean this up, its kinda gross, I don't like iterating all of this with if-else statements.
    if(argc > 1) {
        // Iterate args.
        std::vector<std::string> args;
        for(int i=0; (i<argc); i++) {
            args.push_back(argv[i]);
        }
        for(int i=1; (i<=args.size()); i++) {
            std::cout << "arg: " << args[i] << "\n";
            if(args[i] == "-h" || args[i] == "--help") {
                CLI::commands::help();
                return 0;
            } else
            if(args[i] == "--version") {
                CLI::commands::version(BUILDTYPE, VERSION);
                return 0;
            } else
            if(args[i] == "-l" || args[i] == "--limit") {
                if(args[i+1] != "") {
                    limit = std::stoi(args[i+1]);
                } else {
                    CLI::error();
                    std::cout << "No limit provided, Defaulting to unlimited.";
                }
            } else
            if (args[i] == "-r" || args[i] == "--rating") {
                if(args[i+1] == "general" || args[i+1] == "questionable" || args[i+1] == "sensitive" || args[i+1] == "explicit") {
                    rating = args[i+1];
                    std::cout << "Rating set to: " << rating << "\n";
                } else {
                    CLI::error();
                    std::cout << "Invalid rating provided." << "\n";
                    return 1;
                }
            } else
            if(args[i] == "-o" || args[i] == "--out") {
                
            } else
            if(args[i] == "-t" || args[i] == "--tags") {
                if(args[i+1] != "") {
                    std::cout << "Fetching Posts with tag(s): " << args[i+1] << "\n";
                    std::vector<std::string> tags;
                    std::string s = args[i+1];
                    std::string delimiter = ",";
                    size_t pos = 0;
                    while((pos = s.find(delimiter)) != std::string::npos) {
                        std::string token = s.substr(0, pos);
                        tags.push_back(token);
                        s.erase(0, pos + delimiter.length());
                    }
                    tags.push_back(s);
                    danbooruFetch::fetchPosts(tags, limit, rating);   
                } else {
                    CLI::error();
                    std::cout << "No tags provided, Please provide a comma seperated list of tags.";
                    return 1;
                }
            } else {
                if(args.empty()) {
                    CLI::commands::help();
                }
                CLI::error();
                std::cout << "Invalid command.\n";
                return 1;
            }
        }
    } else {
        CLI::commands::help();
    }
}