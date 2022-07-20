#include <iostream>
#include <string>
#include <map>

#include "cpparser.cpp"


int main(int argc, char** argv) {
    Parser parser("A test CLI tool");

    parser.addArgument(
        "-i",
        "--ignore-case",
        "ignorecase",
        Parser::STORE_TRUE,
        "Ignores case"
    );

    std::map<std::string, std::string> args = parser.parseArgs(argc, argv);

    if (args["ignorecase"] == "true") {
        std::cout << "Ignore case flag was given" << std::endl;
    }

    return 0;
}
