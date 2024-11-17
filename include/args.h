//  args.h
//  booruDownloader v2
//  JPD - 2024

#pragma once

#include <vector>
#include <string>

namespace boorudownloader {
    class argHandler {
        public:

        int callArg()
        void parseArgs(int argc, char *argv[]);
        std::vector<std::string> args;
    };
}