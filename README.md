<!-- # <a name="index-section"></a> Index
Here is a list of what you'll find in this `README.md` :
- [<a name="index-section"></a> Index](#-index)
- [<a name="installation-section"></a> Installation](#-installation)
- [<a name="compilation-section"></a> Compilation](#-compilation)
- [<a name="documentation-section"></a> Documentation](#-documentation)
- [<a name="example-section"></a> Example](#-example)
- [<a name="problems-section"></a> Problems](#-problems)
<br></br> -->

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
./setup.sh
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
# for more informations type './compile.sh -h'
./compile.sh <your_file> [OTHER FLAGS]
```
<br><b>OR</b><br>
<br>You can use `make` if you feel like editing the source filename in the `Makefile`<br>

<br>

<h3>
    :warning: If you want to compile manually your program you must add some things ! Otherwise you won't be able to compile your program.
</h3>

Here's an example with `g++` compiler: <br>

```sh
g++ <your_file> cpparser.cpp -Iinclude
```


# <a name="documentation-section"></a> Documentation
**Each argument type has an example in [example](#example-section) section** <br></br>

There are 4 argument types (`Default`  means the value when the argument is not called) :
* `Parser::STORE_ONE_VALUE` :
  - **Accessible by:** `args["<argname>"].String` or `args["<argname>"]` (C++ will try to convert it to a string)
  - **Type:** `std::string`
  - **Default to:** `""`
<br>

* `Parser::STORE_MULTIPLE_VALUES`
  - **Accessible by:** `args["<argname>"].Vector`
  - **Type:** `std::vector<std::string>`
  - **Default to:** `{}`
<br>

* `Parser::STORE_TRUE`
  - **Accessible by:** `args["<argname>"].Bool` or `args["<argname>"]` (C++ will try to convert it to a boolean)
  - **Has type:** `bool`
  - **Default to:** `false`
<br>

* `Parser::STORE_FALSE`
  - **Accessible by:** `args["<argname>"].Bool` or `args["<argname>"]` (C++ will try to convert it to a boolean)
  - **Type:** `bool`
  - **Default to:** `true`


# <a name="example-section"></a> Example
Here are 4 simple example of how works the `cpParser` library, with each argument type :
```cpp
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
        {"ain", "tea"},			// Values accepted for the flag,
					// if not given, all values are considered correct

        "User name"			// Description of argument
    );

    auto args = parser.parseArgs(argc, argv);

    // the value is contained in `args["name"]` (c++ will convert it to the right type), but to enforce
    // the type, `args["name"].String` is the way to go
    std::cout << "Your name is " << args["name"] << std::endl;

    return 0;
}
```

---

```cpp
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
```

---

```cpp
#include <iostream>
#include <string>
#include <map>

#include "cpparser.hpp"


int main(int argc, char* argv[]) {
    // It's the same for 'Parser::STORE_FALSE'
    Parser parser("Example for 'Parser::STORE_TRUE' argument type");

    parser.addArgument(
        "-i",
        "--ignore-case",
        "ignorecase",
        Parser::STORE_TRUE,
        "Ignores case"
    );

    auto args = parser.parseArgs(argc, argv);

    if (args["ignorecase"]) {
        std::cout << "'Ignore case' flag was given" << std::endl;
    } else {
        std::cout << "'Ignore case' flag was not given" << std::endl;
    }

    return 0;
}
```


# <a name="problems-section"></a> Problems
If you had any problem with compiling/using the library, or if you have any suggestions, please open an issue

