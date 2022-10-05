#include <iostream>
#include <string>

#include "cpparser.hpp"


int main(int argc, char* argv[]) {
    Parser parser("Example for 'Parser::STORE_ONE_VALUE' argument type");

    parser.addArgument(
        "-n",				// Short flag
        "--name",			// Long flag
        "name",				// Key with which you will access value
        true,				// true if the argument is required, false 
					// otherwise. Default to false if nothing given
        Parser::STORE_ONE_VALUE,	// Type of stored argument
        {"ain", "tea"},			// Values accepted for the flag.
					// If not given, all values are considered correct
        "User name"			// Description of argument
    );

    auto args = parser.parseArgs(argc, argv);

    // args["name"] is printable directly, but to get the value you
    // will need to write 'args["name"].String'
    std::cout << "Your name is " << args["name"] << std::endl;

    return 0;
}