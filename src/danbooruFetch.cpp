//      booruDownloader 
//      danbooruFetch.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <json/reader.h>
#include <json/value.h>
#include <json/json.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>
#include <vector>
#include "../include/danbooruFetch.h"
#include "../include/baseCLI.h"
using namespace booruDownloader;

struct data {
    char *ptr;
    size_t len;
};

void initMem(struct data *s) {
    s->len = 0;
    s->ptr = (char*)malloc(s->len+1);
    if(s->ptr == NULL) {
        CLI::error();
        std::cout << "Failure to `malloc`. OOM";
        exit(1);
    }
    s->ptr[0]='\0';
}

std::string buildUrl(std::vector<std::string> tags) {
    std::string url = "https://testbooru.donmai.us/posts.json";
    url.append("?tags=");
    //int i = 0;
    //while(tags.at(0) != "\0") {
        url.append(tags.at(0));
        url.append("%20");
        //i++;
    //}
    std::printf(url.c_str());
    return url;
}

size_t dataFunc(void *ptr, size_t size, size_t nmemb, struct data *s) {
    size_t realSize = s->len + size*nmemb;
    s->ptr = (char*)realloc(s->ptr, realSize+1);
    if(s->ptr == NULL) {
        CLI::error();
        std::cout << "Failure reallocating memory. OOM.";
        exit(1);
    }
    memcpy(s->ptr+s->len, ptr, size*nmemb);
    s->ptr[realSize]='\0';
    s->len = realSize;
    return size*nmemb;
}

Json::Value danbooruFetch::fetchPosts(std::vector<std::string> tags, int limit) {
    struct data s;
    initMem(&s);
    std::string url;
    url = buildUrl(tags);

    if(limit != 0) {
        url.append("&limit=");
        url.append(std::to_string(limit));
    }

    CURL *easy = curl_easy_init();
    curl_easy_setopt(easy, CURLOPT_URL, url.c_str());
    curl_easy_setopt(easy, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, dataFunc);
    curl_easy_setopt(easy, CURLOPT_WRITEDATA, &s);
    curl_easy_perform(easy);

    Json::Reader reader;
    Json::Value data;
    reader.parse(s.ptr, data);

    std::cout << data["id"].asString() << "\n";
    std::cout << data["large_file_url"].asString() << "\n";

    free(s.ptr);
    curl_easy_cleanup(easy);
    exit(0);
}