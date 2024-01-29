//      booruDownloader 
//      danbooru.cpp
//      Jamason P Davis
//      Copyright 2023
//      <3

#include <filesystem>
#include <iostream>
#include <json/json.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>
#include <thread>
#include <vector>
#include "../include/danbooru.h"
#include "../include/cli.h"
#include "../include/download.h"
using namespace booruDownloader;

// This function is responsible for taking the vector with tags and making it a parsable string up ahead.
std::string buildUrl(bool testStatus, std::vector<std::string> tags) {
    std::string url;
    if(testStatus) {
        url = "https://testbooru.donmai.us/posts.json";
    } else {
        url = "https://danbooru.donmai.us/posts.json";
    } 
    // Start formatting for the tags to be inserted into the URLgo
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

void danbooruFetch::fetchPosts(bool testStatus, std::vector<std::string> tags, int limit, std::string rating) {
    // Build the URL.
    std::string url = buildUrl(testStatus, tags);
    if(rating != "") {
        url.append("rating%3A");
        url.append(rating);
    }

    // Good practice, I should put this into downloadImage().
    CURLcode res;

    // RATING SANITIZATION CODE
    if(rating == "g") {
        rating = "general";
    }
    if(rating == "s") {
        rating = "sensitive";
    }
    if(rating == "q") {
        rating = "questionable";
    }
    if(rating == "e") {
        rating = "explicit";
    }

    // Initialize the data string;
    int totalCount = 0;
    int pageCount = 1;
    int errorCount = 0;
    std::string downUrl;
    for(int iC = 1; (iC != limit); iC++) {
        std::string s;
        std::string page = "&page=" + std::to_string(pageCount);
        int count = 0;
        if(pageCount > 1) {
            downUrl.replace(url.length(), page.length(), page);
        } else {
            downUrl.append(url);
            downUrl.append(page);
        }
        std::cout << downUrl << "\n";

        // CURL! (we've been through this on download.cpp)
        CURL *easy = curl_easy_init();
        if(easy) {
            //curl_easy_setopt(easy, CURLOPT_VERBOSE, 1);       // Emergency "I BROKE SOMETHING" option.
            curl_easy_setopt(easy, CURLOPT_URL, downUrl.c_str());
            //curl_easy_setopt(easy, CURLOPT_USERPWD, "User:Key");      // Authenticate the user, Will need to be in a config for changing the API key.
            curl_easy_setopt(easy, CURLOPT_USERAGENT, "libcurl-agent/1.0");
            curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, writeFunc);
            curl_easy_setopt(easy, CURLOPT_WRITEDATA, &s);
            res = curl_easy_perform(easy);

            // If unsuccessful then inform and throw an error.
            if(res == CURLE_OK) {
                long response;
                curl_easy_getinfo(easy, CURLINFO_RESPONSE_CODE, &response);
                if(response == 404) {
                    exit(1);
                }
            } else {
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
        

        // OLD OBSOLETE RATING CODE, This is kept purely for debugging purposes. Remove before any release versions.
        //  if(rating == "general" || rating == "questionable" || rating == "sensitive" || rating == "explicit")  {
        //      if(std::filesystem::exists(imgDir+rating)!= true) {
        //          std::filesystem::create_directory(imgDir+rating);
        //          std::filesystem::create_directory(imgDir+rating+"/"+tagString);
        //          imgDir.append(rating+"/"+tagString+"/");
        //          std::cout << imgDir << "\n";
        //      } else {
        //          if(std::filesystem::exists(imgDir+rating+"/"+tagString) != true) {
        //              std::filesystem::create_directory(imgDir+rating+"/"+tagString);
        //          }
        //          imgDir.append(rating+"/"+tagString+"/");
        //          std::cout << imgDir << "\n";
        //      }
        //  } else {
        //      if(std::filesystem::exists(imgDir+"uncatagorized/") != true) {
        //          std::filesystem::create_directory(imgDir+"uncatagorized/");
        //          std::filesystem::create_directory(imgDir+"uncatagorized/"+tagString);
        //          imgDir.append("uncatagorized/"+tagString+"/");
        //          std::cout << imgDir <<  "\n";
        //      } else {
        //          if(std::filesystem::exists(imgDir+"uncatagorized/"+tagString) != true) {
        //              std::filesystem::create_directory(imgDir+"uncatagorized/"+tagString);
        //          }
        //          imgDir.append("uncatagorized/"+tagString+"/");
        //          std::cout << imgDir << "\n";
        //      }
        //  }
        
        // JSON time, Make a reader and data var.
        Json::Reader reader;
        Json::Value data;
        // Parse the data into the variable assigned above.
        reader.parse(s, data);

        // Temporary - Check parsed data to find out if it is an empty page, if so exit.

        if(!data[0]) {
            exit(1);
        }

        // Check each item in the array retrieved from CURL above, Download each image file and save it.
        if(count < 22) {
            for(Json::Value::ArrayIndex i = 0; (i != data.size()); i++) {
                // NEW FOLDER CODE
                if(std::filesystem::exists(imgDir+rating)!= true) {
                    std::filesystem::create_directory(imgDir+rating);
                    std::filesystem::create_directory(imgDir+rating+"/"+tagString);
                    imgDir.append(rating+"/"+tagString+"/");
                    std::cout << imgDir << "\n";
                } else {
                    if(std::filesystem::exists(imgDir+rating+"/"+tagString) != true) {
                        std::filesystem::create_directory(imgDir+rating+"/"+tagString);
                    }
                    imgDir.append(rating+"/"+tagString+"/");
                    std::cout << imgDir << "\n";
                }

                if(data[i].isMember("source_url")) { 
                    if(limit >= 1 && totalCount == limit) {
                        exit(0);
                    }
                    std::cout << totalCount << " " << count << " " << pageCount << " " << data[i]["large_file_url"] << "\n";
                    std::thread t1 (download::downloadImage,data[i]["source_url"].asString(), imgDir, data[i]["id"].asString(), data[i]["file_ext"].asString());
                    std::thread t2 (download::downloadImage, data[i]["source_url"].asString(), imgDir, data[i]["id"].asString(), data[i]["file_ext"].asString());
                    std::thread t3 (download::downloadImage, data[i]["source_url"].asString(), imgDir, data[i]["id"].asString(), data[i]["file_ext"].asString());
                    std::thread t4 (download::downloadImage, data[i]["source_url"].asString(), imgDir, data[i]["id"].asString(), data[i]["file_ext"].asString());
                    std::thread t5 (download::downloadImage,data[i]["source_url"].asString(), imgDir, data[i]["id"].asString(), data[i]["file_ext"].asString());
                    std::thread t6 (download::downloadImage, data[i]["source_url"].asString(), imgDir, data[i]["id"].asString(), data[i]["file_ext"].asString());
                    std::thread t7 (download::downloadImage, data[i]["source_url"].asString(), imgDir, data[i]["id"].asString(), data[i]["file_ext"].asString());
                    std::thread t8 (download::downloadImage, data[i]["source_url"].asString(), imgDir, data[i]["id"].asString(), data[i]["file_ext"].asString());

                    t1.join();
                    count++;
                    totalCount++;
                    t2.join();
                    count++;
                    totalCount++;
                    t3.join();
                    count++;
                    totalCount++;
                    t4.join();                                                        
                    count++;
                    totalCount++;
                    t5.join();
                    count++;
                    totalCount++;
                    t6.join();
                    count++;
                    totalCount++;
                    t7.join();
                    count++;
                    totalCount++;
                    t8.join();                                                        
                    count++;
                    totalCount++;
                } else {
                    if(limit >= 1 && totalCount == limit) {
                        exit(0);
                    }
                    std::cout << totalCount << " " << count << " " << pageCount << " " << data[i]["source"] << "\n";
                    download::downloadImage(data[i]["large_file_url"].asString(), imgDir, data[i]["id"].asString(), data[i]["file_ext"].asString());
                    count++;
                    totalCount++;
                }
            }
        }
        pageCount++;
    }
    exit(0);
}
