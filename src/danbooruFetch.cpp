//      booruDownloader 
//      danbooruFetch.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

#include <cstddef>
#include <cstdio>
#include <iostream>
#include <json/forwards.h>
#include <json/reader.h>
#include <json/value.h>
#include <json/json.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <new>
#include <string>
#include <vector>
#include "../include/danbooruFetch.h"
#include "../include/baseCLI.h"
using namespace booruDownloader;

std::string buildUrl(std::vector<std::string> tags) {
    std::string url = "https://testbooru.donmai.us/posts.json";
    url.append("?tags=");
    //int i = 0;
    //while(tags.at(0) != "\0") {
        url.append(tags.at(0));
        url.append("%20");
    //    i++;
    //}
    return url;
}

static std::string readBuffer;

size_t writeFunc(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size*nmemb);
    return size*nmemb;
}

void danbooruFetch::fetchPosts(std::vector<std::string> tags, int limit) {
    std::string url = buildUrl(tags);
    CURLcode res;
    std::string s;

    if(limit != 0) {
        url.append("&limit=");
        url.append(std::to_string(limit));
    }

    CURL *easy = curl_easy_init();
    if(easy) {
            //curl_easy_setopt(easy, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(easy, CURLOPT_URL, url.c_str());
        curl_easy_setopt(easy, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, writeFunc);
        curl_easy_setopt(easy, CURLOPT_WRITEDATA, &s);
        res = curl_easy_perform(easy);

        if(res != CURLE_OK) {
            std::cout << "curl_easy_perform() failed." << curl_easy_strerror(res);
        }
        curl_easy_cleanup(easy);

        //std::cout << s << "\n";
    }
    Json::Reader reader;
    Json::Value data;
    std::string unparsed = s;
    reader.parse(s, data);

    //for(Json::Value::ArrayIndex i=0; i != data.size(); i++) {
        //if(data.isMember("id"))
        //std::cout << data[i]["id"].asString();
    //}

    std::cout << data[0]["id"] << "\n";

    //std::cout << data;
    //std::cout << data["id"].asString() << "\n";
    //std::cout << data["large_file_url"] << "\n";
}