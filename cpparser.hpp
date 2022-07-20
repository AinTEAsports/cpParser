#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>


template <typename T>
void printArray(T * array, size_t arraySize) {
    std::cout << "[";

    for (int i = 0; i < arraySize; i++) {
        std::cout << array[i];

        if (i < arraySize-1) {
            std::cout << ", ";
        }
    }

    std::cout << "]" << std::endl;
}


template <typename T>
void printArray(std::vector<T> vector) {
    std::cout << "[";

    for (int i = 0; i < vector.size(); i++) {
        std::cout << vector[i];

        if (i < vector.size()-1) {
            std::cout << ", ";
        }
    }

    std::cout << "]" << std::endl;
}


std::vector<std::string> toVector(char** array, int arraySize) {
    std::string foo;
    std::vector<std::string> returnValue;

    for (int i = 0; i < arraySize; i++) {
        returnValue.push_back(std::string(array[i]));
    }

    return returnValue;
}


template <typename T>
bool contains(std::vector<T> vector, T toFind) {
    for (T value: vector) {
        if (value == toFind) {
            return true;
        }
    }

    return false;
}



class UnknownFlagException : public std::exception {
    private:
        char* message;

    public:
        UnknownFlagException(char* errorMessage) : message(errorMessage) {};

        char* what(std::string flagName) {
            return this->message;
        }
};


class Argument {
    private:
        std::string shortFlag;
        std::string longFlag;
        std::string argumentName;
        std::string action;
        std::string description;

    public:
        Argument(std::string shortFlag, std::string longFlag, std::string  argumentName, int action = 0,  std::string description = "") {
            this->shortFlag = shortFlag;
            this->longFlag = longFlag;
            this->argumentName = argumentName;
            this->action = action;
            this->description = description;
        }


        std::string getShortFlag() {
            return this->shortFlag;
        }


        std::string getLongFlag() {
            return this->longFlag;
        }


        std::string getArgumentName() {
            return this->argumentName;
        }


        std::string getAction() {
            return this->action;
        }


        std::string getDescription() {
            return this->description;
        }
};


class Parser {
    private:
        std::string description;
        std::vector<Argument>* argumentList = new std::vector<Argument>();


        bool isArgumentRegistered(std::string flagName) {
            for (Argument argument: *argumentList) {
                if(flagName == argument.getShortFlag() || flagName == argument.getLongFlag()) {
                    return true;
                }
            }

            return false;
        }


    public:
        static const int NO_ACTION = 0;
        static const int STORE_TRUE = 1;
        static const int STORE_FALSE = 2;


        Parser(std::string help) {
            this->description = help;
            this->addArgument("-h", "--help", "help", 0, "Shows this message");
        }


        void showHelp() {
            std::cout << description << "\n\n\n";

            for (Argument argument: *argumentList) {
                std::cout << "[" << argument.getShortFlag() << "|" << argument.getLongFlag() << "]" << "\t\t" << argument.getDescription() << '\n';
            }
        }


        std::vector<Argument> getArgs() {
            return *argumentList;
        }


        void addArgument(std::string shortFlag, std::string longFlag, std::string  argumentName, int action = 0, std::string description = "") {
            Argument newArgument(shortFlag, longFlag, argumentName, action, description);
            argumentList->push_back(newArgument);
        }


        std::map<std::string, std::string> parseArgs(int argc, char** argv) {
            std::vector<std::string> argvalues = toVector(argv, argc);
            std::map<std::string, std::string> argsMap;


            // Verifying if every flag in argv is valid
            for (std::string argument: argvalues) {
                if (!argument.rfind("-", 0) == 0) {
                    continue;
                }


                if (!this->isArgumentRegistered(argument)) {
                    char errorMessage[] = "Flag '%s' is not valid";
                    sprintf(errorMessage, errorMessage, argument);

                    throw UnknownFlagException(errorMessage);
                }
                
                // If '-h' or '--help' is in arguments, show help and exit
                if (argument == "-h" || argument == "--help") {
                    std::cout << "Usage: " << argv[0] << " [OPTIONS...]  <ARGUMENTS...>" << "\n-----------------\n";
                    this->showHelp();

                    exit(0);
                }


            }



            // Getting arguments
            // here use shift until first argument starts with '-'
            // same algorithm as in bash script where you manually parsearguments


            return argsMap;
        }
};
