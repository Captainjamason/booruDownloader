//       booruDownloader 
//       baseCLI.h
//       Jamason P Davis
//       Copyright 2023
//       <3

#include <iostream>
#include <string>
namespace booruDownloader {
    class CLI {
        public:
        class color {
            public:
            enum clrCode {
                fgRed = 31,
                fgGreen = 32,
                fgYellow = 33,
                fgBlue = 34,
                fgDefault = 39
            };
            public:
            std::string static textSet(CLI::color::clrCode color);
            std::string static textReset();
        };
        public:
        void static error();
        void static noArgs();
        void static invalidArgs();
        void static version(std::string buildtype, std::string ver);
        void static help();
        void static download();
        void static noTags();
    };
}