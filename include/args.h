//  args.h
//  booruDownloader v2
//  JPD - 2024

#pragma once

#include <vector>

namespace boorudownloader {
    class argHandler {
        public:
        struct arg {
            std::string trigShort;
            std::string trigLong;
            std::string var;
        };

        void parseArgs(int argc, char *argv[]);
    };
}