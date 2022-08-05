# <a name="index-section"></a> Index
Here is a list of what you'll find in this `README.md` :
* [Installation guide](#installation-section)
* [Compilation guide](#compilation-section)
* [Documentation](#documentation-section)
* [Code examples](#example-section)
* [Report problems](#problems-section)
<br></br>

# <a name="installation-section"></a> Installation
To `compile` the library, use `setup.sh` by doing in your terminal :
```sh
[[ -x ./setup.sh ]] && ./setup.sh || $(chmod +x ./setup.sh && ./setup.sh)
```
<br>
Or you can do it by yourself by typing in your terminal :

```sh
[[ ! -d lib ]] && mkdir lib
g++ -c ./cpparser.cpp
ar cr libcpparser.a *.o
mv libcpparser.a lib/
```


# <a name="compilation-section"></a> Compilation
To compile your program you will need to add some flags, just like this :
```sh
g++ <your_program> -lcpparser I include -L lib
```


# <a name="documentation-section"></a> Documentation
**Each argument type has an example in [example](#example-section) section** <br></br>

There are 4 argument types (`Default`  means the value when the argument is not called) :
* `Parser::STORE_ONE_VALUE` :
  - **Accessible by:** `args["argname"].String`
  - **Type:** `std::string`
  - **Default to:** `""`.
<br>

* `Parser::STORE_MULTIPLE_VALUES`
  - **Accessible by:** `args["argname"].Vector`
  - **Type:** `std::vector<std::string>`
  - **Default to:** `{}`.
<br>

* `Parser::STORE_TRUE`
  - **Accessible by:** `args["argname"].Bool`
  - **Has type:** `bool`
  - **Default to:** `false`.
<br>

* `Parser::STORE_FALSE`
  - **Accessible by:** `args["argname"].Bool`
  - **Type:** `bool`
  - **Default to:** `true`


# <a name="example-section"></a> Example
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

---

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

---

```cpp
#include <iostream>
#include <string>
#include <map>

#include "cpparser.cpp"


int main(int argc, char** argv) {
	// It's the same for 'Parser::STORE_FALSE'
    Parser parser("Example for 'Parser::STORE_TRUE' argument type);

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


# <a name="problems-section"></a> Problems
If you had any problem with compiling/using the library, or if you have any suggestions, please contact `AinTea#0519` on <a href="https://discord.com">Discord</a>

