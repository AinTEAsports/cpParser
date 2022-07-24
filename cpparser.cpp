#include <iostream>
#include <string>
#include <vector>
#include <map>



// TODO : do function documentation, class and constructor documentation


// Due to some C++ restrictions (that are, I could say, part of the core of the language itself)
// I made some functions and classes inside this namespace to make easier the use of your argument values

// In every function/class I will write why I put his here, and an example of how and why to use it
// TODO : do what the comment above this one says
namespace cputils {
	std::string strip(std::string string) {
        if (string.size() == 0) {
            return "";
        }


		std::vector<char> toStrip = {};
        std::string result = "";

		// We copy the string content into toStrip
		for (int i = 0; i < string.size(); i++) {
			toStrip.push_back(string[i]);
		}

		
		// We remove every space in front of the string
		while (toStrip[0] == ' ') {
			toStrip.erase(toStrip.begin());
		}

		while (toStrip[toStrip.size()-1] == ' ') {
            toStrip.pop_back();
        }


        // We join the char
        for (char character: toStrip) {
            result += character;
        }

        return result;
	}


    std::vector<std::string> split(std::string string, char separator = ' ') {
        std::string stringPart = "";
        std::vector<std::string> splittedString = {};

        for (int i = 0; i < string.size(); i++) {
            if (string[i] == separator) {
                splittedString.push_back(stringPart);
                stringPart = "";
                continue;
            }

            stringPart += string[i];
        }

        return splittedString;
    }




    std::string removeLastChar(std::string string) {
        std::string result = "";

        for (int i = 0; i < string.size()-1; i++) {
            result += string[i];
        }

        return result;
    }


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


    class InvalidFlagException : public std::exception {
        private:
            char* message;
        
        public:
            InvalidFlagException(char* errorMessage) : message(errorMessage) {this->message = errorMessage;};

            char* what() {
                return this->message;
            }
    };
}


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
            std::cout << cputils::multiplyChar("-", description.size()) << '\n';
            std::cout << '\n';

            for (Argument argument: *argumentList) {
                std::cout << "[" << argument.getShortFlag() << "|" << argument.getLongFlag() << "]" << "\t\t" << argument.getDescription() << '\n';
            }
        }


        std::vector<Argument> getArgs() {
            return *argumentList;
        }


        void addArgument(std::string shortFlag, std::string longFlag, std::string  argumentName, int action = 0, std::string description = "") {
            if (!shortFlag.rfind("-", 0) == 0 || !longFlag.rfind("-", 0) == 0) {
                char error[] = "The flag you gave might start by '-' for the short flag, and by '--' for the long flag";
                throw std::runtime_error("The flag you gave ('" + shortFlag + " | " + longFlag + "') might start by '-' for the short flag, and by '--' for the long flag");

                exit(0);
            }

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


            std::vector<std::string> argvalues = cputils::toVector(argv, argc);
            std::map<std::string, std::string> argsMap;

            // Filling the map so not given arguments have default value of ""
            for (Argument a: *argumentList) {
                argsMap.insert(std::pair<std::string, std::string>(a.getArgumentName(), ""));
            }


            // Verifying if every flag in argv is valid
            for (std::string argument: argvalues) {
                if (!argument.rfind("-", 0) == 0) {
                    continue;
                }


                if (!this->isArgumentRegistered(argument)) {
                    if (this->throwError) {
                        throw std::runtime_error("Flag '" + argument + "' is not valid");
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
            cputils::shift(&argvalues);

            while (argvalues.size() != 0) {
                if (!argvalues[0].rfind("-", 0) == 0) {
                    cputils::shift(&argvalues);
                }

                for (Argument registeredArgument: *argumentList) {
                    if (argvalues[0] == registeredArgument.getShortFlag() || argvalues[0] == registeredArgument.getLongFlag()) {
                        switch (registeredArgument.getAction()) {
                            case Parser::NO_ACTION:
                                // argsMap.insert(std::pair<std::string, std::string>(registeredArgument.getArgumentName(), getArgValue(&argvalues)));
                                argsMap[registeredArgument.getArgumentName()] = cputils::strip(cputils::getArgValue(&argvalues));
                                // argsMap[registeredArgument.getArgumentName()] = removeLastChar(argsMap[registeredArgument.getArgumentName()]);
                                break;
                            case Parser::STORE_TRUE:
                                cputils::shift(&argvalues);
                                argsMap[registeredArgument.getArgumentName()] = "true";
                                break;
                            case Parser::STORE_FALSE:
                                cputils::shift(&argvalues);
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
