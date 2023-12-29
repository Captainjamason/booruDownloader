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
    int result = booruDownloader::download::downloadImage();
    if(result == 1) {
        return 1;
    } else {
        return 0;
    }
}
