//  args.h
//  booruDownloader v2
//  JPD - 2024

#pragma once

namespace boorudownloader {
    extern bool verbose;
    class argHandler {
        public:
        struct argData {
            int limit = 0;  /// Maybe make this configuration controlled in the future?
            std::string tags;
            std::string out = "";
            std::string configPath = ".config/boorudownloader/boorudownloader.cfg";
        };

        argData parseArgs(int argc, char *argv[]);
    };
}