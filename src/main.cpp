//      booruDownloader 
//      main.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

#include "../include/download.h"
#include "../include/danbooruFetch.h"
#include "../include/baseCLI.h"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <string>
#include <vector>

float VERSION = 0.1;
std::string BUILDTYPE = "indev";

using namespace booruDownloader;
int main(int argc, char *argv[]) {
    std::vector<std::string> tags;
    tags.push_back("blue_hair");
    std::cout << tags.at(0) << "\n";
    danbooruFetch::fetchPosts(tags, 1);
}
