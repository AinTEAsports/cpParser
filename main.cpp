#include <iostream>
#include <vector>
#include "cpparser.hpp"


int main(int argc, char** argv) {
    Parser parser("This is a test program");

    parser.addArgument(
        "-i",
        "--ignore-case",
        "ignorecase",
        Parser::NO_ACTION,
        "Ignores case"
    );

    auto args = parser.parseArgs(argc, argv);

    return 0;
}
