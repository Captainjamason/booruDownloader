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
    std::string homePath = getenv("HOME");
    // Check home folder first and foremost.
    if(std::filesystem::exists(homePath+"/.config/booruDownloader/config")) {
        path = homePath+"/.config/booruDownloader/config";
    } else
    // Check the alternate home config
    if(std::filesystem::exists(homePath+"/.config/booruDownloader.conf")) {
        path = homePath+"/.config/booruDownloader.conf";
    } else
    // Check in /etc/ aka use example conf. 
    if(std::filesystem::exists("/etc/booruDownloader/config")) {
        std::cout << "Using example configuration in /etc/booruDownloader/config...\n";
        path = "/etc/booruDownloader/config";
    } else 
    // Check local directory, Useful for portable installs.
    if(std::filesystem::exists("/etc/booruDownloader/config")) {
        std::cout << "Using example configuration located in the executable folder. (aka Portable)";
        path = "./config.json";
    } else {
        return 1;
    }
    // Open up the file and attempt to parse JSON data from it.
    std::ifstream file;
    file.open(path);

    Json::Value data;
    Json::Reader reader;

    // Sanity Check // 
    if(reader.parse(file, data)) {
        return data;
    } else {
        exit(1);
    }
}
