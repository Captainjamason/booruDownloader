//      booruDownloader 
//      danbooru.h
//      Jamason P Davis
//      Copyright 2023
//      <3

#include <json/json.h>
#include <string>
#include <vector>

namespace booruDownloader {
    class danbooruFetch {
        public:
        int static fetchPosts(bool testStatus, std::vector<std::string> tags, int limit, std::string rating);
    };
}
