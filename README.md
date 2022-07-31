# Installation
---
To `compile` the library, use `setup.sh` by doing in your terminal :
```sh
chmod +x setup.sh && ./setup.sh
```
# Example
---
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
---


<br>

# Problems
---
If you had any problem with compiling/using the library, or if you have any suggestions, please contact `AinTea#0519` on <a href="https://discord.com">Discord</a>