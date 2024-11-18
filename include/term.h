//  term.h
//  booruDownloader v2
//  JPD - 2024

#pragma once
#include <cstdint>
#include <string>

namespace boorudownloader {
    class terminal {
        public:

        //  Initial two functions for terminal drawing.
        int initialize();
        int draw(std::string str, uint16_t x = 0, uint16_t y = 0);

        // Our actual data drawing functions.
        int drawProgBar();
        int drawText(std::string str);
        int debugPrint(std::string str);
    };
}
