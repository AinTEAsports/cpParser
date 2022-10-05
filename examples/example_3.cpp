#include <iostream>
#include <string>
#include <map>

#include "cpparser.hpp"


int main(int argc, char* argv[]) {
    // It's the same for 'Parser::STORE_FALSE'
    Parser parser("Example for 'Parser::STORE_TRUE' argument type");

    parser.addArgument(
        "-i",
        "--ignore-case",
        "ignorecase",
        Parser::STORE_TRUE,
        "Ignores case"
    );

    auto args = parser.parseArgs(argc, argv);

    if (args["ignorecase"].Bool == true) {
        std::cout << "'Ignore case' flag was given" << std::endl;
    } else {
        std::cout << "'Ignore case' flag was not given" << std::endl;
    }

    return 0;
}