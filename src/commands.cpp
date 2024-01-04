//      booruDownloader 
//      commands/help.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

#include <iostream>
#include "../include/cli.h"

using namespace booruDownloader;
void CLI::commands::help() {
    std::cout<<"["<<CLI::colorizeText("booruDownloader Help", CLI::color::fgYellow)<<"]\n"
    <<CLI::colorizeText("--version", CLI::color::fgGreen) << ": Shows the version menu.\n"
    <<CLI::colorizeText("-h", CLI::color::fgGreen)<<" || "<<CLI::colorizeText("--help", CLI::color::fgGreen) << ": Shows this help menu.\n"
    <<CLI::colorizeText("-r", CLI::color::fgGreen)<<" || "<<CLI::colorizeText("--rating", CLI::color::fgGreen) << ": Download/Sort by rating (General, Sensitive, Questionable, Explicit).\n"
    <<CLI::colorizeText("-v", CLI::color::fgGreen)<<" || "<<CLI::colorizeText("--limit", CLI::color::fgGreen) << ": Limit of how many posts to download.\n"
    <<CLI::colorizeText("-t", CLI::color::fgGreen)<<" || "<<CLI::colorizeText("--tags", CLI::color::fgGreen) << ": Comma seperated list of tags to filter by.\n";    
}

void::CLI::commands::version(std::string buildtype, std::string version) {
    std::cout<<"["<<CLI::colorizeText("booruDownloader", CLI::color::fgBlue)<<"]\n"
    <<buildtype<<" "<<version<<"\n"
    <<CLI::colorizeText("<3", CLI::color::fgRed)<<"\n";
}