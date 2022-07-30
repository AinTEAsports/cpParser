# cpParser
A Python argparse like C++ argument parser



# DUE TO RECENT CHANGES, THIS README FILE IS NOT ANYMORE WHAT YOU NEED TO DO, IT WILL BE SOON MODIFIED


`STEPS :`

- `1- Make the header accessible:`
  - `Solution 1:` you just need to download `cpparser.cpp` into your current directory
  - `Solution 2:` open your terminal in which directory you have your `main.cpp` and do <br>`curl https://raw.githubusercontent.com/AinTEAsports/cpParser/main/cpparser.cpp > ./cpparser.cpp`
<br/><br>

- `2- Start coding:` it is as simple as that, there is documentation in every function/method in `cpparser.cpp`
<br/><br>

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

    auto args = parser.parseArgs(argc, argv);

    if (args["ignorecase"].Bool == true) {
        std::cout << "Ignore case flag was given" << std::endl;
    }

    return 0;
}
```
Also, if you want an even more complex example, check `main.cpp` (and if you want to test it, don't forget to compile it with flag `-lcpr`)
<br/><br>

- `4- Problems`
If you encounter any problems, please contact me on Discord: `AinTea#0519`
