//  config.h
//  booruDownloader v2
//  JPD - 2024

#pragma once

namespace boorudownloader {
    class config {
        public:
        struct confData {
            // Limit options
            int limit_default;
            int limit_hard;
            // Default out directory
            std::string default_out;
            // Sorting
            std::string sortby;     /// 'none', 'batch', 'artist', 'rating' 
        }
        confData loadConfig(std::string path);
    }
}