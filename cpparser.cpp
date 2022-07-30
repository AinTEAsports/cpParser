#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "include/cpparser.hpp"


/*               CPUTILS               */

std::string cputils::strip(std::string string) {
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


std::vector<std::string> cputils::split(std::string string, char separator = ' ') {
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


std::string cputils::removeLastChar(std::string string) {
    std::string result = "";

    for (int i = 0; i < string.size()-1; i++) {
        result += string[i];
    }

    return result;
}


template <typename T>
void cputils::shift(std::vector<T>* vector) {
    vector->erase(vector->begin());
}


std::string cputils::getArgValue(std::vector<std::string>* argsVector) {
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


std::string cputils::multiplyChar(std::string toMultiply, int multiplicator) {
    std::string result = "";

    for (int _ = 0; _ < multiplicator; _++) result += toMultiply;

    return result;
}



std::vector<std::string> cputils::toVector(char** array, int arraySize) {
    std::string foo;
    std::vector<std::string> returnValue;

    for (int i = 0; i < arraySize; i++) {
        returnValue.push_back(std::string(array[i]));
    }

    return returnValue;
}



cputils::UnknownFlagException::UnknownFlagException(char* errorMessage) : message(errorMessage) {};

char* cputils::UnknownFlagException::what(std::string flagName) {
    return this->message;
}


cputils::InvalidFlagException::InvalidFlagException(char* errorMessage) : message(errorMessage) {
    this->message = errorMessage;
}

char* cputils::InvalidFlagException::what() {
    return this->message;
}





/*               ARGUMENT CLASS               */

Argument::Argument(std::string shortFlag, std::string longFlag, std::string  argumentName, int action = 0,  std::string description = "") {
    this->shortFlag = shortFlag;
    this->longFlag = longFlag;
    this->argumentName = argumentName;
    this->action = action;
    this->description = description;
}


std::string Argument::getShortFlag() {
    return this->shortFlag;
}


std::string Argument::getLongFlag() {
    return this->longFlag;
}


std::string Argument::getArgumentName() {
    return this->argumentName;
}


int Argument::getAction() {
    return this->action;
}


std::string Argument::getDescription() {
    return this->description;
}




/*               PARSER CLASS               */

bool Parser::isArgumentRegistered(std::string flagName) {
    for (Argument argument: *argumentList) {
        if(flagName == argument.getShortFlag() || flagName == argument.getLongFlag()) {
            return true;
        }
    }

    return false;
}


Parser::Parser(std::string help, bool throwError = false) {
    this->description = help;
    this->addArgument("-h", "--help", "help", 0, "Shows this message");

    this->throwError = throwError;
}


void Parser::showHelp() {
    std::cout << description << "\n";
    std::cout << cputils::multiplyChar("-", description.size()) << '\n';
    std::cout << '\n';

    for (Argument argument: *argumentList) {
        std::cout << "[" << argument.getShortFlag() << "|" << argument.getLongFlag() << "]" << "\t\t" << argument.getDescription() << '\n';
    }
}


std::vector<Argument> Parser::getArgs() {
    return *argumentList;
}


void Parser::addArgument(std::string shortFlag, std::string longFlag, std::string  argumentName, int action = 0, std::string description = "") {
    if (!shortFlag.rfind("-", 0) == 0 || !longFlag.rfind("-", 0) == 0) {
        char error[] = "The flag you gave might start by '-' for the short flag, and by '--' for the long flag";
        throw std::runtime_error("The flag you gave ('" + shortFlag + " | " + longFlag + "') might start by '-' for the short flag, and by '--' for the long flag");

        exit(0);
    }

    if (std::count(this->POSSIBLE_ACTIONS.begin(), this->POSSIBLE_ACTIONS.end(), action) == 0) {
        throw std::invalid_argument("The action you gave for argument named '" + argumentName + "' does not exists");

        exit(0);
    }

    Argument newArgument(shortFlag, longFlag, argumentName, action, description);
    argumentList->push_back(newArgument);
}



std::map<std::string, ArgumentValue> Parser::parseArgs(int argc, char** argv) {
    // If arg count = 1 then there is only script name, so we just show help and exit
    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " [OPTIONS...]  <ARGUMENTS...>" << "\n\n";
        this->showHelp();
        exit(0);
    }


    std::vector<std::string> argvalues = cputils::toVector(argv, argc);
    std::map<std::string, ArgumentValue> argsMap;

    // Filling the map so not given arguments have default value of ""
    for (Argument a: *argumentList) {
        switch (a.getAction()) {
            case Parser::STORE_ONE_VALUE:
                argsMap.insert(std::pair<std::string, ArgumentValue>(a.getArgumentName(), ArgumentValue{"", {}, false}));
                break;
            case Parser::STORE_MULTIPLE_VALUES:
                argsMap.insert(std::pair<std::string, ArgumentValue>(a.getArgumentName(), ArgumentValue{"", {}, false}));
                break;
            case Parser::STORE_TRUE:
                argsMap.insert(std::pair<std::string, ArgumentValue>(a.getArgumentName(), ArgumentValue{"", {}, false}));
                break;
            case Parser::STORE_FALSE:
                argsMap.insert(std::pair<std::string, ArgumentValue>(a.getArgumentName(), ArgumentValue{"", {}, true}));
                break;
        }

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
                    case Parser::STORE_ONE_VALUE:
                        // argsMap.insert(std::pair<std::string, std::string>(registeredArgument.getArgumentName(), getArgValue(&argvalues)));
                        argsMap[registeredArgument.getArgumentName()].String = cputils::strip(cputils::getArgValue(&argvalues));
                        // argsMap[registeredArgument.getArgumentName()] = removeLastChar(argsMap[registeredArgument.getArgumentName()]);
                        break;
                    case Parser::STORE_MULTIPLE_VALUES:
                        // argsMap[registeredArgument.getArgumentName()].Vector = cputils::split(cputils::strip(cputils::getArgValue(&argvalues)));
                        argsMap[registeredArgument.getArgumentName()].Vector = cputils::split(cputils::getArgValue(&argvalues));
                        break;
                    case Parser::STORE_TRUE:
                        cputils::shift(&argvalues);
                        argsMap[registeredArgument.getArgumentName()].Bool = true;
                        break;
                    case Parser::STORE_FALSE:
                        cputils::shift(&argvalues);
                        argsMap[registeredArgument.getArgumentName()].Bool = false;
                        break;
                    default:
                        printf("WTF ???\n");
                }
            }
        }
    }


    return argsMap;
}
