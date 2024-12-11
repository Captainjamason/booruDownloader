//  main.cpp
//  booruDownloader v2
//  JPD - 2024

// Includes 
#include "term.h"
#include "args.h"
#include "download.h"
#include "define.h"

using namespace boorudownloader;
int main(int argc, char *argv[]) {
    argHandler args;                                            /// Create our class for arguments.
    terminal::initialize();                                     /// Initialize the terminal.
    argHandler::argData argD = args.parseArgs(argc, argv);      /// Create our struct, and parse all arguments.
    if(DEBUG == 1) {                                            /// Check for debug flag
        terminal::debugMessage("Using testbooru...");
    }
    download(argD.tags, argD.limit, argD.out);                  /// Call the download function with arguments.
    terminal::release();                                        /// Release the terminal.
}