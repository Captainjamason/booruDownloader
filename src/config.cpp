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
    if(std::filesystem::exists(path) == true) {
        terminal::debugMessage("Using config: "+path);
    } else {
        terminal::error("Could not locate configuration file: "+path);
        exit(1);
    }
}