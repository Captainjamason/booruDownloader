//  download.cpp
//  booruDownloader v2
//  JPD - 2024

// Includes.
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <curl/curl.h>
#include <json/json.h>
#include <thread>
#include <cmath>
#include "download.h"
#include "term.h"
#include "args.h"
#include "define.h"

using boorudownloader::terminal;

// Some global variables, This could be done better.
int count = 0;
int pend = 0;
int fail = 0;
int done = 0;
std::vector<std::string> vec1;
std::vector<std::string> vec2;
std::vector<std::string> vec3;
std::vector<std::string> vec4;

//  The callback for cURL in fetchData(); 
static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size*nmemb);
    return size*nmemb;
}
// The callback for cURL in downloadImage();
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

// This takes a vector of URLS, adn splits it into quarters for each thread.
int splitVec(std::vector<std::string> downloadUrls) {
    int half = round(downloadUrls.size() / 2);
    int q1 = round(half / 2);
    int q2 = round(half / 2) + half;
    for(int i = 0; i < q1; i++) {
        vec1.push_back(downloadUrls[i]);
    }
    for(int i = q1; i >= q1 && i < half; i++) {
        vec2.push_back(downloadUrls[i]);
    }
    for(int i = half; i >= half && i < q2; i++) {
        vec3.push_back(downloadUrls[i]);
    }
    for(int i = q2; i >= q2 && i < downloadUrls.size(); i++) {
        vec4.push_back(downloadUrls[i]);
    }
    downloadUrls.clear();
    return 0;
}

// The primary worker for download threads. 
int downloadImage(std::vector<std::string> vec) {
    CURLcode res;
    std::string readBuffer;
    
    // todo: add output folder argument and handling.
    if(std::filesystem::exists("./images") != true) {
        std::filesystem::create_directory("./images");
    }


    for(int i = 0; i <= vec.size()-1; i++) {
        std::hash<std::string> hash;

        std::string fn = "./images/"+std::to_string(hash(vec[i]))+vec[i].substr(vec[i].length() - 4);
        FILE* fp = fopen(fn.c_str(), "wb");

        CURL *easy = curl_easy_init();
        curl_easy_setopt(easy, CURLOPT_URL, vec[i].c_str());
        curl_easy_setopt(easy, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(easy, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, writeImage);

        res = curl_easy_perform(easy);
        curl_easy_cleanup(easy);

        if(res == 0) {
            pend--;
            done++;
        } else {
            pend--;
            fail++;
        }

        terminal::progUpdate(pend, fail, done, "Downloading: "+vec[i]+"     File: "+fn);
    }

    return 0;
}

// Primary function used to fetch downloadable data. 
// Please note that this is a recursive function.
std::vector<std::string> fetchData(std::string tags, int limit, int page = 1) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    static std::vector<std::string> downloadUrls;
    std::string srv_url;

    if(DEBUG == 1) {
        terminal::debugMessage("Using testbooru...");
        srv_url.append("https://testbooru.donmai.us/posts.json?limit=200");
    } else {
        srv_url.append("https://danbooru.donmai.us/posts.json?limit=200");  
    }

    srv_url.append("&page="+std::to_string(page));
    srv_url.append("&tags="+tags);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, srv_url.c_str());
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
        if(count == limit) {
            break;
        } else {
            count++;
        }
        
        if(!data[i]["large_file_url"]) {
            fail++;
        } else {
            pend++;
            downloadUrls.push_back(data[i]["large_file_url"].asString());
        }

        terminal::progUpdate(pend, fail, done, "Fetching URL: "+data[i]["large_file_url"].asString()+"  ID: "+data[i]["id"].asString());

        if(count % 200 == 0) {
           fetchData(tags, limit, page += 1);
        }
        

    }
    return downloadUrls;
}


// This is the "public" function that organizes everything and gets it all going.
int boorudownloader::download(std::string tags, int limit) {
    std::vector<std::string> urls = fetchData(tags, limit);
    splitVec(urls);
    std::thread t1 (downloadImage, vec1);
    std::thread t2 (downloadImage, vec2);
    std::thread t3 (downloadImage, vec3);
    std::thread t4 (downloadImage, vec4);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}