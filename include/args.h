//  args.h
//  booruDownloader v2
//  JPD - 2024

#pragma once

namespace boorudownloader {
    extern bool verbose;
    class argHandler {
        public:
        struct argData {
            bool test = false;
            int limit = 3000;  /// Maybe make this configuration controlled in the future?
            std::string tags = "";
            std::string out = "./out";
            std::string configPath = ".config/boorudownloader/boorudownloader.cfg";
        };

        argData parseArgs(int argc, char *argv[]);
    };
}