#include <iostream>
#include <string>
#include <vector>
#include <map>



// TODO : do function documentation, class and constructor documentation


template <typename T>
void shift(std::vector<T>* vector) {
    vector->erase(vector->begin());
}


std::string getArgValue(std::vector<std::string>* argsVector) {
    std::string args = "";

    // The first element will be the flag so we remove it to go into while statement
    shift(argsVector);

    // While first value does not starts with '-'
    while (!(*argsVector)[0].rfind("-", 0) == 0) {
        args += (*argsVector)[0] + " ";
        shift(argsVector);

        if (argsVector->size() == 0) {
            break;
        }
    }

    return args;
}


std::string multiplyChar(std::string toMultiply, int multiplicator) {
    std::string result = "";

    for (int _ = 0; _ < multiplicator; _++) result += toMultiply;

    return result;
}


std::vector<std::string> toVector(char** array, int arraySize) {
    std::string foo;
    std::vector<std::string> returnValue;

    for (int i = 0; i < arraySize; i++) {
        returnValue.push_back(std::string(array[i]));
    }

    return returnValue;
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
        int action;
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


        int getAction() {
            return this->action;
        }


        std::string getDescription() {
            return this->description;
        }
};


class Parser {
    private:
        bool throwError;

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


        Parser(std::string help, bool throwError = false) {
            this->description = help;
            this->addArgument("-h", "--help", "help", 0, "Shows this message");

            this->throwError = throwError;
        }


        void showHelp() {
            std::cout << description << "\n";
            std::cout << multiplyChar("-", description.size()) << '\n';
            std::cout << '\n';

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
            // If arg count = 1 then there is only script name, so we just show help and exit
            if (argc == 1) {
                std::cout << "Usage: " << argv[0] << " [OPTIONS...]  <ARGUMENTS...>" << "\n\n";
                this->showHelp();
                exit(0);
            }


            std::vector<std::string> argvalues = toVector(argv, argc);
            std::map<std::string, std::string> argsMap;

            // Filling the map so not given arguments have default value of ""
            for (Argument a: *argumentList) {
                argsMap.insert(std::pair<std::string, std::string>(a.getArgumentName(), "true"));
            }


            // Verifying if every flag in argv is valid
            for (std::string argument: argvalues) {
                if (!argument.rfind("-", 0) == 0) {
                    continue;
                }


                if (!this->isArgumentRegistered(argument)) {
                    if (this->throwError) {
                        char errorMessage[] = "Flag '%s' is not valid";
                        sprintf(errorMessage, errorMessage, argument);

                        throw UnknownFlagException(errorMessage);
                    } else {
                        std::cout << argv[0] << ": unknown flag ('" << argument << "') was found\n\n";

                        this->showHelp();
                        exit(1);
                    }


                }
                
                // If '-h' or '--help' is in arguments, show help and exit
                if (argument == "-h" || argument == "--help") {
                    std::cout << "Usage: " << argv[0] << " [OPTIONS...]  <ARGUMENTS...>" << "\n\n";
                    this->showHelp();

                    exit(0);
                }
            }



            // Getting arguments
            // here use shift until first argument starts with '-'
            // same algorithm as in bash script where you manually parsearguments

            // The first element is the script name, it is not a flag so we delete it
            shift(&argvalues);

            while (argvalues.size() != 0) {
                for (Argument registeredArgument: *argumentList) {
                    if (argvalues[0] == registeredArgument.getShortFlag() || argvalues[0] == registeredArgument.getLongFlag()) {
                        switch (registeredArgument.getAction()) {
                            case Parser::NO_ACTION:
                                // argsMap.insert(std::pair<std::string, std::string>(registeredArgument.getArgumentName(), getArgValue(&argvalues)));
                                argsMap[registeredArgument.getArgumentName()] = getArgValue(&argvalues);
                                break;
                            case Parser::STORE_TRUE:
                                shift(&argvalues);
                                argsMap[registeredArgument.getArgumentName()] = "true";
                                break;
                            case Parser::STORE_FALSE:
                                shift(&argvalues);
                                argsMap[registeredArgument.getArgumentName()] = "false";
                                break;
                            default:
                                printf("WTF ???\n");
                        }
                    }
                }
            }


            return argsMap;
        }
};
