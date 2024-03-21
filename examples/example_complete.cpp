#include <iostream>
#include <string>
#include <vector>

#include "cpparser.hpp"


// By the way the program is not optimized so you can see everything you can do (like conversions, directly print thins, etc...)
int main(int argc, char* argv[]) {
    Parser parser("Complete demonstration for https://github.com/AinTEAsports/cpParser");

    parser.addArgument(
        "-d",
        "--dirs",
        "dirs",
        true,
        Parser::STORE_MULTIPLE_VALUES,
        "Directories in which to pass"
    );

    parser.addArgument(
        "-r",
        "--recursive",
        "recursive",
        Parser::STORE_TRUE,
        "Recurse into subdirectories"
    );

    parser.addArgument(
        "-action",
        "--action",
        "action",
        true,
        Parser::STORE_ONE_VALUE,
        {"delete", "rename", "grep"},
        "Action to perform on files"
    );

    auto args = parser.parseArgs(argc, argv);
    std::vector<std::string> directories = args["dirs"];


    std::cout << "The action you choose was '" << std::string(args["action"]) << "'" << std::endl;

    if (args["recursive"]) { std::cout << "You choose 'recursive' option" << std::endl; }

    std::cout << "Here are directories you wanted to check:" << std::endl;
    for (std::string dir: directories) {
        std::cout << dir << '\n';
    }

    return 0;
}
