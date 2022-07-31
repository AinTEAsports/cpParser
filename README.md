# Installation
To `compile` the library, use `setup.sh` by doing in your terminal :
```sh
chmod +x setup.sh && ./setup.sh
```
# Example
Here is a simple example of how works the `cpParser` library :
```cpp
#include <iostream>
#include <string>
#include <map>

#include "cpparser.cpp"


int main(int argc, char** argv) {
    // Initializing the parser
    Parser parser("A test CLI tool");

    // Adding an argument, that stores true if given, but false if not given
    parser.addArgument(
        "-i",
        "--ignore-case",
        "ignorecase",
        Parser::STORE_TRUE,
        "Ignores case"
    );

    // We get the args, it is a std::map<std::string, Argument>
    auto args = parser.parseArgs(argc, argv);

    if (args["ignorecase"].Bool == true) {
        std::cout << "'Ignore case' flag was given" << std::endl;
    } else {
        std::cout << "'Ignore case' flag was not given" << std::endl;
    }

    return 0;
}
```
# Documentation
There are 4 argument types (`Default`  means the value when the argument is not called) :
* `Parser::STORE_ONE_VALUE`, accessible with `args["argname"].String`, has type `std::string`. Default to `""`
* `Parser::STORE_MULTIPLE_VALUES`, accessible with `args["argname"].Vector`, has type `std::vector<std::string>`. Default to `{}`
* `Parser::STORE_TRUE`, accessible with `args["argname"].Bool`, has type `bool`. Default to `false`
* `Parser::STORE_FALSE`, accessible with `args["argname"].Bool`, has type `bool`. Default to `true`
# Problems
If you had any problem with compiling/using the library, or if you have any suggestions, please contact `AinTea#0519` on <a href="https://discord.com">Discord</a>
