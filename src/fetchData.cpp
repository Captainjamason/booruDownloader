//  fetchData.cpp
//  booruDownloader v2
//  JPD - 2024

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include "fetchData.h"

static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size*nmemb);
    return size*nmemb;
}

int count = 0;
int pend = 0;
int fail = 0;
int done = 0;
    
int boorudownloader::fetchData(int page) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;


    std::string url = "https://testbooru.donmai.us/posts.json?limit=200&page=";
    url.append(std::to_string(page));

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    Json::Reader reader;
    Json::Value data;
    reader.parse(readBuffer, data);

    if(!data[0]) {
        exit(1);
    }

    for(int i = 0; i != data.size(); i++) {
        count++;

        if(!data[i]["large_file_url"]) {
            fail++;
        } else {
            pend++;
        }
        std::cout <<"\x1b[33m"<<pend<<"\x1b[0m/\x1b[31m"<<fail<<"\x1b[0m/\x1b[32m"<<done<<"\x1b[0m       ";
        std::cout << "ID: " << data[i]["id"] << "       URL: " << data[i]["large_file_url"] << "\n";

        if(count % 200 == 0) {
           fetchData(page += 1);
        }
    }

    return 0;
}