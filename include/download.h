//      booruDownloader 
//      download.h
//      Jamason P Davis
//      Copyright 2023
//      <3

#include <iostream>

namespace booruDownloader {
    class download {
        public:
        static int downloadImage(std::string url, std::string filename, std::string file_ext);
    };
}