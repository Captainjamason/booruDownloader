//      booruDownloader 
//      danbooruFetch.h
//      Jamason P Davis
//      Copyright 2023
//      <3

#include <jsoncpp/json/json.h>
#include <string>
#include <vector>

namespace booruDownloader {
    class danbooruFetch {
        public:
        void static fetchPosts(std::vector<std::string> tags, int limit);
    };
}