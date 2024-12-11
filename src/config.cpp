//  config.cpp
//  booruDownloader v2
//  JPD - 2024

#include <iostream>
#include <filesystem>
#include <json/json.h>
#include <fstream>
#include "config.h"
#include "term.h"

using boorudownloader::config;
using boorudownloader::terminal;

int genConfig(std::string fullPath) {
    std::filesystem::path path(fullPath);

    if(path.has_parent_path()) {
        std::filesystem::create_directories(path.parent_path());
    }
    std::ofstream file(path);
    if(file) {
        file << "test\n";
        terminal::message("Default configuration saved at: "+fullPath);
    } else {
        terminal::error("Could not create configuration file!");
        exit(1);
    }

    file.close();
    return 0;
}

config::confData config::loadConfig(std::string path) {
    std::string home = getenv("HOME");
    std::string nPath = home+"/"+path;

    if(std::filesystem::exists(nPath) == true) {
        terminal::debugMessage("Using config: "+nPath);
        config::confData conf;
        return conf;
    } else {
        terminal::error("Could not locate config file: "+nPath);
        if(terminal::prompt("Would you like to create one now?")) {
            genConfig(nPath);
            return loadConfig(path);
        } else {
            exit(1);
        };
    }
}