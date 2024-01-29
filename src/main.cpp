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
#include <json/value.h>
#include <string>
#include <vector>

// These variables are hard source linked vars defining if its indev or release.
// TODO: Move these to a seperate config that is loaded on runtime, allowing for more flexibility.
std::string VERSION = "0.1.3";
std::string BUILDTYPE = "indev";

// Call booruDownloader namespace.
using namespace booruDownloader;
int main(int argc, char *argv[])
{
    bool conf_testBooru = false;
    std::string outputDir;
    std::string rating;
    int limit = 0;

    // Basic configuration loading and handling, Exmaple configuration will be mocked up and added to installation commands.
    Json::Value conf = config::loadConfig();
    if(conf["testbooru"].asBool()) {
        std::cout << "Using Testbooru.\n";
        conf_testBooru = true;
    }
    if(argc > 1) {
        // Iterate args.
        std::vector<std::string> args;
        for(int i=0; (i<argc); i++) {
            args.push_back(argv[i]);
        }
        for(int i=1; (i<=args.size()); i++) {
            if(args[i] == "-h" || args[i] == "--help") {
                CLI::commands::help();
                return 0;
            }
            if(args[i] == "--version") {
                CLI::commands::version(BUILDTYPE, VERSION);
                return 0;
            }
            if(args[i] == "-l" || args[i] == "--limit") {
                if(args[i+1] != "") {
                    limit = std::stoi(args[i+1]);
                } else {
                    CLI::error();
                    std::cout << "No limit provided, Defaulting to unlimited.";
                }
            }
            if (args[i] == "-r" || args[i] == "--rating") {
                if(args[i+1] == "general" || args[i+1] == "questionable" || args[i+1] == "sensitive" || args[i+1] == "explicit") {
                    rating = args[i+1];
                    std::cout << "Rating set to: " << rating << "\n";
                } else {
                    CLI::error();
                    std::cout << "Invalid rating provided." << "\n";
                    return 1;
                }
            }
            if(args[i] == "-o" || args[i] == "--out") {
                
            }
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
                    danbooruFetch::fetchPosts(conf_testBooru, tags, limit, rating);   
                } else {
                    CLI::error();
                    std::cout << "No tags provided, Please provide a comma seperated list of tags.\n";
                    return 1;
                }
                if(args.empty()) {
                    CLI::commands::help();
                    CLI::error();
                    std::cout << "Invalid command.\n";
                    return 1;
                }
            }
        }
    } else {
        CLI::error();
	std::cout << "No arguments provided. Please use -h or --help for list of options.\n";
    }
}
