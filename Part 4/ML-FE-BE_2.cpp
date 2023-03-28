// Part 1:
// Choose a data structure(s) to represent the game state. You need to keep track of the following:
// - NxN board
// - Location of black holes
// - Counts of # of adjacent black 
#include <iostream>
#include <string>

#include "GameController.h"


static void usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)>\n"
        << "Options:\n"
        << "\t-h,--help\t\tShow this help message\n"
        << "\t-d,--debug\t\tShow secondary debug game board\n"
        << "\t-f,--file <filename>\tRead game settings from the specified file"
        << std::endl;
}

int main(int argc, char* argv[]) {
    bool debug = false;
    const char* filename = nullptr;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            usage(argv[0]);
            return 0;
        }
        else if ((arg == "-d") || (arg == "--debug")) {
            debug = true;
        }
        else if ((arg == "-f") || (arg == "--file") ) {
            if (nullptr == argv[i + 1]) {
                std::cerr << "Invalid command line syntax. Filename required.\n";
                usage(argv[0]);
                return 1;
            }
            filename = argv[i + 1];
        }
    }
    return Run(debug, filename);
}