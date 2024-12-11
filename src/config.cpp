//  config.cpp
//  booruDownloader v2
//  JPD - 2024

#include <iostream>
#include <filesystem>
#include <json/json.h>
#include "config.h"
#include "term.h"

using boorudownloader::config;
using boorudownloader::terminal;

config::confData config::loadConfig(std::string path) {
    std::string home = getenv("HOME");
    std::string nPath = home+"/"+path;

    if(std::filesystem::exists(nPath) == true) {
        terminal::debugMessage("Using config: "+nPath);
        config::confData conf;
        return conf;
    } else {
        terminal::error("Could not locate config file: "+nPath);
        terminal::prompt("Would you like to create one now?");
        exit(1);
    }
}