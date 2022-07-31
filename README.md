# Installation
<a name="installation-section"></a>

To `compile` the library, use `setup.sh` by doing in your terminal :
```sh
chmod +x setup.sh && ./setup.sh
```
# Example
<a name="example-section"></a>

Here are 4 simple example of how works the `cpParser` library, with each argument type :
```cpp
#include <iostream>
#include <string>

#include "cpparser.cpp"


int main(int argc, char** argv) {
    Parser parser("Example for 'Parser::STORE_ONE_VALUE' argument type");

    parser.addArgument(
        "-n",
        "--name",
        "name",
        Parser::STORE_ONE_VALUE,
        "User name"
    );

    auto args = parser.parseArgs(argc, argv);

    std::cout << "Your name is " << args["name"].String << std::endl;

    return 0;
}
```
<br>

```cpp
#include <iostream>
#include <string>
#include <vector>

#include "cpparser.cpp"


int main(int argc, char** argv) {
    Parser parser("Example for 'Parser::STORE_MULTIPLE_VALUES' argument type");

    parser.addArgument(
        "-u",
        "--urls",
        "urlList",
        Parser::STORE_MULTIPLE_VALUES,
        "The list of URL"
    );

    auto args = parser.parseArgs(argc, argv);

    for (std::string url: args["urlList"].Vector) {
        std::cout << url << std::endl;
    }

    return 0;
}
```
<br>

```cpp
#include <iostream>
#include <string>
#include <map>

#include "cpparser.cpp"


int main(int argc, char** argv) {
    Parser parser("Example for 'Parser::STORE_TRUE' argument type (same goes for 'Parser::STORE_FALSE')");

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
```
# Documentation
#<a name="documentation-section"></a>
**Each argument type has an example in [Example](#example-section) part**

There are 4 argument types (`Default`  means the value when the argument is not called) :
* `Parser::STORE_ONE_VALUE`, accessible with `args["argname"].String`, has type `std::string`. Default to `""`.
* `Parser::STORE_MULTIPLE_VALUES`, accessible with `args["argname"].Vector`, has type `std::vector<std::string>`. Default to `{}`.
* `Parser::STORE_TRUE`, accessible with `args["argname"].Bool`, has type `bool`. Default to `false`.
* `Parser::STORE_FALSE`, accessible with `args["argname"].Bool`, has type `bool`. Default to `true`.
# Problems
#<a name="problems-section"></a>
If you had any problem with compiling/using the library, or if you have any suggestions, please contact `AinTea#0519` on <a href="https://discord.com">Discord</a>
