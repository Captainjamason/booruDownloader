//       booruDownloader 
//       cli.h
//       Jamason P Davis
//       Copyright 2023
//       <3

#include <iostream>
#include <string>
#include <vector>
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
        class commands {
            public:
            void static help();
            void static version(std::string buildtype, std::string version);
        };
        public:
        void static error();
        void static info();
        std::string static colorizeText(std::string str, CLI::color::clrCode clr);
    };
}