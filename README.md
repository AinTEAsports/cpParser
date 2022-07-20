# cpParser
A Python argparse like C++ argument parser


`STEPS :`

- `1- Make the header accessible:` you just need to download `cpparser.hpp` into your current directory

- `2- Start coding:` it is as simple as that, there is documentation in every function/method in `cpparser.hpp`

- `3- Example:` here is a short example
```cpp
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
```

- `4- Problems`
If you encounter any problems, contact me on Discord: `AinTea#0519`