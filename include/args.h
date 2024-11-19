//  args.h
//  booruDownloader v2
//  JPD - 2024

#pragma once

namespace boorudownloader {
    class argHandler {
        public:

        struct argData {
            int limit = 500000000;
            std::string tags = "";
        };

        argData parseArgs(int argc, char *argv[]);
    };
}