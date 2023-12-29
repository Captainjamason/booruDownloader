//      booruDownloader 
//         main.cpp
//      Jamason P Davis
//      Copywrite 2023
//            <3

#include "../include/download.h"
#include "../include/baseCLI.h"
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>

using namespace booruDownloader;
int main(int argc, char *argv[])
{
    std::cout << "This is a test\n";
    CLI::color::textRed();
    std::cout << "this should be red\n";
    CLI::color::textReset();
    // Call the downloadImage() func, I don't particularly like how this error correction is handled. I may try to clean it up later (but it runs now).
    int result = download::downloadImage();
    if(result == 1) {
        return 1;
    } else {
        return 0;
    }
}
