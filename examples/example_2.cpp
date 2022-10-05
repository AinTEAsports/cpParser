#include <iostream>
#include <string>
#include <vector>

#include "cpparser.hpp"


int main(int argc, char* argv[]) {
    Parser parser("Example for 'Parser::STORE_MULTIPLE_VALUES' argument type");

    parser.addArgument(
        "-u",
        "--urls",
        "urlList",
        true,
        Parser::STORE_MULTIPLE_VALUES,
        "The list of URL"
    );

    auto args = parser.parseArgs(argc, argv);

    for (std::string url: args["urlList"].Vector) {
        std::cout << url << std::endl;
    }

    return 0;
}