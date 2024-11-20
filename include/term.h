//  term.h
//  booruDownloader v2
//  JPD - 2024

#pragma once
#include <cstdint>
#include <string>

namespace boorudownloader {
    class terminal {
        public:
        static int initialize();
        static int release();
        static int message(std::string s);
        static int error(std::string s);
        static int debugMessage(std::string s); 
        static int progUpdate(int pend, int err, int done, std::string s = "");
    };
}
