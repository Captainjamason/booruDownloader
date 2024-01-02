//       booruDownloader 
//       CLI.cpp
//       Jamason P Davis
//       Copyright 2023
//       <3

#include "../include/baseCLI.h"
#include <iostream>
#include <string>

// Welcome to the fun file...
// I really didn't want this to look *this* messy. If there's a better way of doing this I'd like to research and put it into
// practice, however this is not a primary concern at the moment; I wish to make sure the heavy lifting code works fine itself
// first before this gets cleaned up (and the GUI eventually gets added).

// Please feel free to clean this file up if you know how. 
// <3
// -JPD


using namespace booruDownloader;
// Error tag, this is mainly used internal to this file, however it is occasionally called from other files.
void CLI::error() {
    std::cout << "[" << CLI::color::textSet(CLI::color::fgRed) << "ERROR" << CLI::color::textSet(CLI::color::clrCode::fgDefault) << "]\n";
}

// Called when no tags are used, I hope most of these are pretty self-explanatory.
void CLI::noTags() {
    CLI::error();
    std::cout << "No tags passed, Please enter a comma seperated list of tags to filter and download.\n";
}

// I'm going to assume that you saw my last comment...
void CLI::noArgs() {
    CLI::error();
    std::cout << "No arguments passed. Please use --help or -h\n";
}

// go fish. no explanations here...
void CLI::invalidArgs() {
    CLI::error();
    std::cout << "Invalid arguments passed. Please use --help or -h\n";
}

// I'm not really sure how I managed to make this somewhat readable? atleast it looks pretty (i think).
void CLI::version(std::string buildtype, float ver) {
    std::cout << "[" << CLI::color::textSet(CLI::color::fgBlue) << "booruDownloader" << CLI::color::textReset() << "]\n"
    << buildtype << " " << ver << "\n"
    << "Made by Jamason 'Captainjamason' Davis\n"
    << CLI::color::textSet(CLI::color::fgRed) << "<3" << CLI::color::textReset() << "\n";
}

// this looks really nice with a solarized color scheme...
void CLI::help() {
    std::cout << "[" << CLI::color::textSet(CLI::color::fgYellow) << "booruDownloader - Help" << CLI::color::textReset() << "]\n"
    << CLI::color::textSet(CLI::color::fgGreen) << "--version" << CLI::color::textReset() <<  ": Shows the current version installed.\n"
    << CLI::color::textSet(CLI::color::fgGreen) << "-h || --help" << CLI::color::textReset() << ": Shows this help menu.\n"
    << CLI::color::textSet(CLI::color::fgGreen) << "-t || --tags" << CLI::color::textReset() << ": Define a comma seperated list of tags to filter by.\n"
    << CLI::color::textSet(CLI::color::fgGreen) << "-l || --limit" << CLI::color::textReset() << ": Define a limit to how many posts should be fetched and downloaded.\n"
    << CLI::color::textSet(CLI::color::fgGreen) << "-v || --verbose" << CLI::color::textReset() << ": Verbose output, Useful if something isn't working quite right.\n";
}