//      booruDownloader 
//      main.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

// Project Includes
#include "../include/download.h"
#include "../include/danbooru.h"
#include "../include/config.h"
#include "../include/commands.h"
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <json/value.h>
#include <opencxx-cli/cli.h>

// These variables are hard source linked vars defining if its indev or release.
// TODO: Move these to a seperate config that is loaded on runtime, allowing for more flexibility.
std::string VERSION = "0.1.3";
std::string BUILDTYPE = "indev";


// opencxx-cli integration, Create a class object `cli` and make so it can be called anywhere.
opencxx_cli::CLI cli;

int main(int argc, char *argv[])
{
    std::vector<opencxx_cli::CLI::entryData> entries;
    bool conf_testBooru = false;
    std::string outputDir;
    std::string rating;
    int limit = 0;

    // Basic configuration loading and handling, Exmaple configuration will be mocked up and added to installation commands.
    Json::Value conf = booruDownloader::config::loadConfig();
    if(conf["testbooru"].asBool()) {
        std::cout << "Using Testbooru.\n";
        conf_testBooru = true;
    }

    std::vector<std::string> tags;
    std::vector<std::string> args = cli.vectorize(argc, argv);

    cli.addEntry("--limit", "-l", booruDownloader::commands::setLimit, &entries, "Under construction, Do not use...");
    cli.addEntry("--rating", "-r", booruDownloader::commands::setRating, &entries, "Under construction, Do not use...");
    cli.addEntry("--out", "-o", booruDownloader::commands::setOut, &entries, "Under construction, Do not use...");
    cli.addEntry("--tags", "-t", booruDownloader::commands::setTags, &entries, "Under construction");

    cli.parse(entries, args);
}
