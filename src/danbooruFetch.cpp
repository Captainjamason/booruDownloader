//      booruDownloader 
//      danbooruFetch.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <json/json.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>
#include <vector>
#include "../include/danbooruFetch.h"
#include "../include/baseCLI.h"
#include "../include/download.h"
using namespace booruDownloader;

// This function is responsible for taking the vector with tags and making it a parsable string up ahead.
std::string buildUrl(std::vector<std::string> tags) {
    // This will be replaced with standard danbooru once we have some semblance of stability.
    std::string url = "https://danbooru.donmai.us/posts.json";
    // Start formatting for the tags to be inserted into the URL.
    url.append("?tags=");
    // Iterate the vector, pop each one onto the url with a seperation character.
    for(int i = 0; i < tags.size(); i++) {
        url.append(tags[i]);
        url.append("%20");
    }
    return url;
}

// Callback from CURL on data retrieval.
size_t writeFunc(void *contents, size_t size, size_t nmemb, void *userp) {
    // Append the stream into the `userp` pointer, passed by a curlopt.
    ((std::string*)userp)->append((char*)contents, size*nmemb);
    return size*nmemb;
}

void danbooruFetch::fetchPosts(std::vector<std::string> tags, int limit) {
    // Build the URL.
    std::string url = buildUrl(tags);
    // Good practice, I should put this into downloadImage().
    CURLcode res;
    // Initialize the data string;
    int totalCount = 0;
    int pageCount = 1;
    int failCount = 0;
    bool noData = false;
    for(int iC = 1; (iC != limit); iC++) {
        std::string s;
        std::string page = "&page=" + std::to_string(pageCount);
        int count = 0;
        if(pageCount > 1) {
            url.replace(url.length()-page.length()+1, page.length(), page);
        } else {
            url.append(page);
        }
        std::cout << url << "\n";

        // CURL! (we've been through this on download.cpp)
        CURL *easy = curl_easy_init();
        if(easy) {
            //curl_easy_setopt(easy, CURLOPT_VERBOSE, 1);       // Emergency "I BROKE SOMETHING" option.
            curl_easy_setopt(easy, CURLOPT_URL, url.c_str());
            curl_easy_setopt(easy, CURLOPT_USERAGENT, "libcurl-agent/1.0");
            curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, writeFunc);
            curl_easy_setopt(easy, CURLOPT_WRITEDATA, &s);
            res = curl_easy_perform(easy);

            // If unsuccessful then inform and throw an error.
            if(res != CURLE_OK) {
                std::cout << "curl_easy_perform() failed." << curl_easy_strerror(res);
            }
            // Cleanup
            curl_easy_cleanup(easy);
        }
        // Check if the folder `./images/` exists.
        std::string imgDir = "./images/";
        if(std::filesystem::exists(imgDir) != true) {
            std::filesystem::create_directory(imgDir);
        }
        // Iterate tags vector and append each one into the tagString
        std::string tagString;
        for(int i = 0; i < tags.size(); i++) {
            tagString.append(tags[i]);
            tagString.append("-");
        }
        // Same thing as above, but with the *new* imagedir string.
        imgDir.append(tagString);
        imgDir.append("/");
        if(std::filesystem::exists(imgDir) != true) {
            std::filesystem::create_directory(imgDir);
        }

        // JSON time, Make a reader and data var.
        Json::Reader reader;
        Json::Value data;
        // Parse the data into the variable assigned above.
        reader.parse(s, data);
        // Check each item in the array retrieved from CURL above, Download each image file and save it.
        if(count < 22) {
            for(Json::Value::ArrayIndex i = 0; (i != data.size()); i++) {
                if(data[i].isMember("large_file_url")) { 
                    std::cout << data[i]["large_file_url"] << "\n";
                    std::cout << totalCount << " " << count << " " << pageCount << " ";
                    download::downloadImage(data[i]["large_file_url"].asString(), imgDir, data[i]["id"].asString(), data[i]["file_ext"].asString());
                    count++;
                    totalCount++;
                } else {
                    std::cout << "No URL found in retrieved data." << "\n";
                }
            }
        }
        pageCount++;
    }
}