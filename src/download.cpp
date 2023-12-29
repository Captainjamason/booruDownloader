//       booruDownloader 
//        download.cpp
//       Jamason P Davis
//       Copywrite 2023
//             <3

#include "../include/download.h"
#include <cstdio>
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
using namespace booruDownloader;

// Image callback function, points to file to save
size_t writeImage(char *ptr, size_t size, size_t nmemb, void *userdata) {
    FILE* stream = (FILE*)userdata;
    if(!stream) {
        printf("No file stream\n");
        return 1;
    }
    size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
    return written;
}


// Image download function
int download::downloadImage() {
    printf("Downloading: ");

    FILE* fp = fopen("images/test.jpg", "wb");
    if(!fp) {
        printf("Failed to create file\n");
        return false;
    }

    CURL *easy = curl_easy_init(); // Init the easy handle
    curl_easy_setopt(easy, CURLOPT_URL, "https://testbooru-cdn.donmai.us/original/3a/0e/3a0e769991323dcf9748adba9ab530dc.jpg"); // Image download URL
    curl_easy_setopt(easy, CURLOPT_USERAGENT, "libcurl-agent/1.0"); // Set the user agent - required for danbooru?
    curl_easy_setopt(easy, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, writeImage); // Callback to write image
    curl_easy_setopt(easy, CURLOPT_USERPWD, "User:Key");   // Authenticate the user
    curl_easy_perform(easy);
    curl_easy_cleanup(easy); // clean up
    return 0;
}