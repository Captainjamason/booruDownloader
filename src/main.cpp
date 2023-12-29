//      booruDownloader 
//         main.cpp
//      Jamason P Davis
//      Copywrite 2023
//            <3

#include "../include/download.h"
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>

int main(int argc, char *argv[])
{
    // Call the downloadImage() func, I don't particularly like how this error correction is handled. I may try to clean it up later (but it runs now).
    int result = booruDownloader::download::downloadImage();
    if(result == 1) {
        return 1;
    } else {
        return 0;
    }
}
