//      booruDownloader 
//      config.h
//      Jamason P Davis
//      Copyright 2023
//      <3

#include <iostream>
#include <jsoncpp/json/value.h>

namespace booruDownloader {
    class config {
        public:
        static Json::Value loadConfig();
        static std::string loginData(Json::Value conf);
    };
}