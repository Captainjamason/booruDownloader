//      booruDownloader 
//      config.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

#include <filesystem>
#include <fstream>
#include <json/json.h>
#include <json/value.h>
#include "../include/config.h"

using namespace booruDownloader;

Json::Value config::loadConfig() {
    std::string path;
    // Check home folder first and foremost.
    if(std::filesystem::exists("~/.config/boorudownloader/config")) {
        path = "~/.config/booruDownloader/config";
    } else
    // Check the alternative home config location. 
    if (std::filesystem::exists("~/.config/boorudownloader.conf")) {
        path = "~/.config/booruDownloader.conf";
    } else 
    // Check for the default configuration file in /etc/ (This will need to be fixed for cross platform usage.)
    if (std::filesystem::exists("/etc/boorudownloader/config")) {
        path = "/etc/booruDownloader/config";
    } else 
    // Check for portable configuration setup, This is required to be in the same folder as the binary to run.
    if (std::filesystem::exists("./config.conf")) {
        path = "./config.conf";
    } 
    // If nothing is found, Return error code 2 and let main.cpp handle the rest.
    else {
        return NULL;
    }

    // Open up the file and attempt to parse JSON data from it.
    std::ifstream file;
    file.open(path);

    Json::Value data;
    Json::Reader reader;

    // Sanity Check // 
    reader.parse(file, data);
    return data;
}
