//       booruDownloader 
//        download.cpp
//       Jamason P Davis
//       Copywrite 2023
//             <3

#include "../include/download.h"
#include <charconv>
#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <string>
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
int download::downloadImage(std::string url, std::string filename, std::string file_ext) {
    std::cout << url << "\n";
    filename.append(".");
    filename.append(file_ext);
    std::string fn = "./images/";
    fn.append(filename);

    // Open file to write, This will need to be passed as an arg to the func.
    FILE* fp = fopen(fn.c_str(), "wb");
    // If the file can't be opened/created just abort all together.
    if(!fp) {
        printf("Failed to create file\n");
        return 1;
    }
    
    // CURL boilerplate.
    CURL *easy = curl_easy_init();      // Init the easy handle.
    curl_easy_setopt(easy, CURLOPT_URL, url.c_str());     // Image download URL.
    curl_easy_setopt(easy, CURLOPT_USERAGENT, "libcurl-agent/1.0");     // Set the user agent - required for danbooru?
    curl_easy_setopt(easy, CURLOPT_WRITEDATA, fp);      // Write data to the file pointer. Kinda makes this shindig work. otherwise it won't download the whole image.
    curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, writeImage);      // Callback to write image.
    //curl_easy_setopt(easy, CURLOPT_USERPWD, "User:Key");      // Authenticate the user, Will need to be in a config for changing the API key.
    curl_easy_perform(easy);        // Run the deal, This will call func `writeImage()` whenever data is recieved.
    curl_easy_cleanup(easy);        // Clean up.
    return 0;
}