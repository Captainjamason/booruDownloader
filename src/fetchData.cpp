//  fetchData.cpp
//  booruDownloader v2
//  JPD - 2024

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <curl/curl.h>
#include <json/json.h>
#include <thread>
#include <cmath>
#include "fetchData.h"

static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size*nmemb);
    return size*nmemb;
}

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


int count = 0;
int pend = 0;
int fail = 0;
int done = 0;

std::vector<std::string> downloadUrls;
std::vector<std::string> vec1;
std::vector<std::string> vec2;
std::vector<std::string> vec3;
std::vector<std::string> vec4;

int splitVec() {
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
    std::cout << "\n" << "vec1: " << vec1.size() << "       vec2: " << vec2.size() << "       vec3: " << vec3.size() << "       vec4: " << vec4.size() <<"\n";
    return 0;
}
    
int downloadImage(std::vector<std::string> vec, int id) {
    CURLcode res;
    std::string readBuffer;

    if(std::filesystem::exists("./images") != true) {
        std::filesystem::create_directory("./images");
    }


    for(int i = 0; i <= vec.size()-1; i++) {
        std::string fn = "./images/"+std::to_string(id)+"_"+std::to_string(i)+vec[i].substr(vec[i].length() - 4);
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

        std::cout <<"\x1b[0;0H\x1b[33m"<<pend<<"\x1b[0m/\x1b[31m"<<fail<<"\x1b[0m/\x1b[32m"<<done<<"\x1b[0m     \r";
    }

    return 0;
}

int boorudownloader::fetchData(int page, int limit) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;


    std::string url = "https://danbooru.donmai.us/posts.json?limit=200&tags=nakiri_ayame&page=";
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

        std::cout <<"\x1b[0;0H\x1b[33m"<<pend<<"\x1b[0m/\x1b[31m"<<fail<<"\x1b[0m/\x1b[32m"<<done<<"\x1b[0m       ";
        std::cout << "ID: " << data[i]["id"] << "       URL: " << data[i]["large_file_url"] << "                        ";

        if(count % 200 == 0) {
           fetchData(page += 1);
        }
        

    }
    return 0;
}



int boorudownloader::download() {
    fetchData(1, 200);
    //downloadImage(downloadUrls);
    splitVec();
    std::thread t1 (downloadImage, vec1, 1);
    std::thread t2 (downloadImage, vec2, 2);
    std::thread t3 (downloadImage, vec1, 3);
    std::thread t4 (downloadImage, vec2, 4);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}