//      booruDownloader 
//      danbooruFetch.h
//      Jamason P Davis
//      Copyright 2023
//      <3

#include <json/json.h>
#include <json/value.h>
#include <string>

namespace booruDownloader {
    class danbooruFetch {
        public:
        Json::Value static fetchPosts(std::string tags[], int limit);
    };
}