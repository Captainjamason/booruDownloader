//  main.cpp
//  booruDownloader v2
//  JPD - 2024

// Includes 
#include "term.h"
#include "args.h"
#include "download.h"
#include "define.h"
#include "config.h"

using namespace boorudownloader;
bool boorudownloader::verbose = false;
int main(int argc, char *argv[]) {
    config conf; 
    argHandler args;                                            /// Create our class for arguments.
    terminal::initialize();                                     /// Initialize the terminal.

    argHandler::argData argD = args.parseArgs(argc, argv);      /// Create our struct, and parse all arguments.
    config::confData c = conf.loadConfig(argD.configPath);
    if(argD.limit == 0) {
        argD.limit = c.limit_default;
    } else {
        terminal::message("Limit set to: "+std::to_string(argD.limit));
    }
    if(argD.out == "") {
        argD.out = c.default_out;
    } else {
        terminal::message("Output directory: "+argD.out);
    }
    if(DEBUG == 1) {                                            /// Check for debug flag
        terminal::debugMessage("Using testbooru...");
    }
    download(argD.tags, argD.limit, argD.out);                  /// Call the download function with arguments.

    terminal::release();                                        /// Release the terminal.
}