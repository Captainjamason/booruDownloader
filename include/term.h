//  term.h
//  booruDownloader v2
//  JPD - 2024

#pragma once
#include <cstdint>
#include <string>

namespace boorudownloader {
    class terminal {
        public:
        // Create our datatype for our progress bar.
        struct progBar {
            uint8_t w;
            uint8_t h;
            uint8_t prog;
        };

        struct termData {
            uint8_t w;
            uint8_t h;
            std::string output;
        };

        //  Initial two functions for terminal drawing.
        int initialize();
        int draw();

        // Our actual data drawing functions.
        int drawProgBar(progBar *pb);
        int drawText(std::string str);
        int debugPrint(std::string str);
    };
}
