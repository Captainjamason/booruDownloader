//  args.h
//  booruDownloader v2
//  JPD - 2024

#pragma once

namespace boorudownloader {
    class argHandler {
        public:

        struct argData {
            bool verbose = false;
            bool test = false;
            int limit = 500000000;  /// Maybe make this configuration controlled in the future?
            std::string tags = "";
        };

        argData parseArgs(int argc, char *argv[]);
    };
}