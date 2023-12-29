//       booruDownloader 
//        download.cpp
//       Jamason P Davis
//       Copywrite 2023
//             <3

#include "../include/download.h"
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
using namespace booruDownloader;

// `downloadImage()` callback function. What actually does the work.
size_t writeImage(char *ptr, size_t size, size_t nmemb, void *userdata) {
    // Init `stream` variable to hold incoming data.
    FILE* stream = (FILE*)userdata;
    // Check to make sure there *is* an incoming data stream.
    if(!stream) {
        printf("No file stream\n");
        return 1;
    }
    // Write data to the file opened in `downloadImage()` and return the written amount.
    size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
    return written;
}


// Image download function
int download::downloadImage() {
    // Open file to write, This will need to be passed as an arg to the func.
    FILE* fp = fopen("images/test.jpg", "wb");
    // If the file can't be opened/created just abort all together.
    if(!fp) {
        printf("Failed to create file\n");
        return 1;
    }
    
    // CURL boilerplate.
    CURL *easy = curl_easy_init();      // Init the easy handle.
    curl_easy_setopt(easy, CURLOPT_URL, "https://testbooru-cdn.donmai.us/original/3a/0e/3a0e769991323dcf9748adba9ab530dc.jpg");     // Image download URL.
    curl_easy_setopt(easy, CURLOPT_USERAGENT, "libcurl-agent/1.0");     // Set the user agent - required for danbooru?
    curl_easy_setopt(easy, CURLOPT_WRITEDATA, fp);      // Write data to the file pointer. Kinda makes this shindig work. otherwise it won't download the whole image.
    curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, writeImage);      // Callback to write image.
    //curl_easy_setopt(easy, CURLOPT_USERPWD, "User:Key");      // Authenticate the user, Will need to be in a config for changing the API key.
    curl_easy_perform(easy);        // Run the deal, This will call func `writeImage()` whenever data is recieved.
    curl_easy_cleanup(easy);        // Clean up.
    return 0;
}