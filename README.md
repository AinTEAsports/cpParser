# cpParser
A Python argparse like C++ argument parser


`STEPS :`

- `1- Make the header accessible`
You just need to download `cpparser.hpp` into your current directory

- `2- Start coding`
It is as imple as that, there is documentation in every function/method in `cpparser.hpp`

- `3- Example`
Here is an example
```cpp
#include <iostream>
#include <string>
#include <map>

#include "cpparser.hpp"

int main(int argc, char** argv) {
    Parser parser(description="A test CLI tool");

    parser.addArgument(
        shortFlag="-i",
        longFlag="--ignore-case",
        argumentName="ignorecase",
        action=Parser::STORE_TRUE,
        description="Ignores case"
    )

    std::map<std::string, std:string> args = parser.parseArgs(argc, argv);

    if (args["ignorecase"] == "true") {
        std::cout << "Ignore case flag was given" << std::endl;
    }
}
```

- `4- Problems`
If you encounter any problems, contact me on Discord: `AinTea#0519`