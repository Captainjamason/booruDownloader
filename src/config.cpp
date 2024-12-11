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
        file << 
        "{\n" <<
        "   \"limit_default\": 1000000000,\n"<<
        "   \"default_out\": \"./out\",\n"<<
        "   \"sort_by\": \"none\"\n"<<
        "}";
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
        config::confData conf;
        terminal::debugMessage("Attempting to use config: "+nPath);

        std::ifstream file(nPath);
        Json::Reader reader;
        Json::Value data;
        if(file.is_open()) {
            if(!reader.parse(file, data)) {
                terminal::error("Could not parse configuration file!");
                exit(1);
            };
        }
        file.close();

        if(data["limit_default"]) {
            terminal::debugMessage("Using config: "+nPath);
            terminal::debugMessage("Default Limit: "+data["limit_default"].asString());
            conf.limit_default = data["limit_default"].asInt();
            terminal::debugMessage("Default output: "+data["default_out"].asString());
            conf.default_out = data["default_out"].asString();
            terminal::debugMessage("Folder Sorting: "+data["sort_by"].asString());
            conf.sortby = data["sort_by"].asString();
            return conf;
        }
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