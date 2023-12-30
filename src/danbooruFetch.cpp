//      booruDownloader 
//      danbooruFetch.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <json/value.h>
#include <stdio.h>
#include <json/json.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>
#include "../include/danbooruFetch.h"
using namespace booruDownloader;

std::string buildUrl(std::string tags[]) {
    std::string url = "https://testbooru.donmai.us/posts.json";
    url.append("?tags=");
    for(auto var : *tags) {
        std::string tmp = &var;
        url.append(tmp);
        url.append("%20");
    }
    return url;
}



void callBooru(std::string url, int limit, std::string tags[]) {

    url = buildUrl(tags);
    if(limit != 0) {
        url.append("&limit=");
        url.append(std::to_string(limit));
    }
    CURL *easy = curl_easy_init();
    curl_easy_setopt(easy, CURLOPT_URL, url.c_str());
    curl_easy_setopt(easy, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION);
}

Json::Value danbooruFetch::fetchPosts(std::string tags[], int limit) {

}