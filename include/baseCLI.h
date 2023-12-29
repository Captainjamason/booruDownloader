//       booruDownloader 
//       baseCLI.h
//       Jamason P Davis
//       Copyright 2023
//       <3

namespace booruDownloader {
    class CLI {
        public:
        class color {
            enum clrCode {
                fgRed = 31,
                fgGreen = 32,
                fgYellow = 33,
                fgBlue = 34,
                fgDefault = 39
            };
            public:
            int static textRed();
            int static textReset();
            int static textGreen();
            int static textYellow();
            int static textBlue();
        };
        public:
        void static noArgs();
        void static invalidArgs();
    };
}