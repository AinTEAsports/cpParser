#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

#include "include/cpparser.hpp"

// Yes, I did that, don't judge me please
#define yeet throw

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
bool cputils::contains(std::vector<T> v, T to_find) {
	for (T element: v) {
		if (element == to_find) return true;
	}

	return false;
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

Argument::Argument(std::string shortFlag, std::string longFlag, std::string argumentName, bool required = false, int action = 0, std::vector<std::string> choices = {}, std::string description = "") {
    this->shortFlag = shortFlag;
    this->longFlag = longFlag;
    this->argumentName = argumentName;
    this->required = required;
    this->action = action;
	this->choices = choices;
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


bool Argument::isRequired() {
    return this->required;
}

int Argument::getAction() {
    return this->action;
}


std::vector<std::string> Argument::getChoices() {
	return this->choices;
}


std::string Argument::getDescription() {
    return this->description;
}


bool Argument::hasChoice(std::string to_check) {
	for (std::string choice: this->choices) {
		if (choice == to_check) return true;
	}

	return false;
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


Parser::Parser(std::string help, bool throwError) {
    this->description = help;
    this->addArgument("-h", "--help", "help", 0, false, "Shows this message");

    this->throwError = throwError;
}

Parser::Parser(std::string help) {
    this->description = help;
    this->addArgument("-h", "--help", "help", 0, false, "Shows this message");

    this->throwError = false;
}



void Parser::showHelp() {
    std::cout << description << "\n";
    std::cout << cputils::multiplyChar("-", description.size()) << '\n';
    std::cout << '\n';


	int max_length = 0;
	std::string description;

	for (Argument argument: *argumentList) {
		description = std::string("[") + argument.getShortFlag() + std::string("|") + argument.getLongFlag() + std::string("]");

		if (description.size() > max_length) max_length = description.size();
	}


	std::string help_line;

    for (Argument argument: *argumentList) {
        // TODO : do appropriate help show, it should be really easy
		help_line = std::string("[") + argument.getShortFlag() + std::string("|") + argument.getLongFlag() + std::string("]");

        if (argument.isRequired()) {
            /* std::cout << "[" << argument.getShortFlag() << "|" << argument.getLongFlag() << "]\t\t" << argument.getDescription() << "\t(required)\n"; */
			std::cout << std::setw(max_length) << std::left << help_line << "          " << argument.getDescription() << "\t(required)\n";
        } else {
            /* std::cout << "[" << argument.getShortFlag() << "|" << argument.getLongFlag() << "]\t\t" << argument.getDescription() << '\n'; */
			std::cout << std::setw(max_length) << std::left << help_line << "          " << argument.getDescription() << '\n';
        }
    }
}


std::vector<Argument> Parser::getArgs() {
    return *argumentList;
}


void Parser::addArgument(std::string shortFlag, std::string longFlag, std::string argumentName, bool required = false, int action = 0, std::string description = "") {
    if (! (shortFlag.rfind("-", 0) == 0) || ! (longFlag.rfind("-", 0) == 0)) {
        char error[] = "The flag you gave might start by '-' for the short flag, and by '--' for the long flag";
        yeet std::runtime_error("The flag you gave ('" + shortFlag + " | " + longFlag + "') might start by '-' for the short flag, and by '--' for the long flag");

        exit(0);
    }

    if (std::count(this->POSSIBLE_ACTIONS.begin(), this->POSSIBLE_ACTIONS.end(), action) == 0) {
        yeet std::invalid_argument("The action you gave for argument named '" + argumentName + "' does not exists");

        exit(0);
    }

    Argument newArgument(shortFlag, longFlag, argumentName, required, action, {}, description);
    argumentList->push_back(newArgument);
}

void Parser::addArgument(std::string shortFlag, std::string longFlag, std::string argumentName, int action = 0, std::string description = "") {
    if (! (shortFlag.rfind("-", 0) == 0) || ! (longFlag.rfind("-", 0) == 0)) {
        char error[] = "The flag you gave might start by '-' for the short flag, and by '--' for the long flag";
        yeet std::runtime_error("The flag you gave ('" + shortFlag + " | " + longFlag + "') might start by '-' for the short flag, and by '--' for the long flag");

        exit(0);
    }

    if (std::count(this->POSSIBLE_ACTIONS.begin(), this->POSSIBLE_ACTIONS.end(), action) == 0) {
        yeet std::invalid_argument("The action you gave for argument named '" + argumentName + "' does not exists");

        exit(0);
    }

    Argument newArgument(shortFlag, longFlag, argumentName, false, action, {}, description);
    argumentList->push_back(newArgument);
}

void Parser::addArgument(std::string shortFlag, std::string longFlag, std::string argumentName, int action = 0, std::vector<std::string> choices = {}, std::string description = "") {
    if (! (shortFlag.rfind("-", 0) == 0) || ! (longFlag.rfind("-", 0) == 0)) {
        char error[] = "The flag you gave might start by '-' for the short flag, and by '--' for the long flag";
        yeet std::runtime_error("The flag you gave ('" + shortFlag + " | " + longFlag + "') might start by '-' for the short flag, and by '--' for the long flag");

        exit(0);
    }

    if (std::count(this->POSSIBLE_ACTIONS.begin(), this->POSSIBLE_ACTIONS.end(), action) == 0) {
        yeet std::invalid_argument("The action you gave for argument named '" + argumentName + "' does not exists");

        exit(0);
    }

    Argument newArgument(shortFlag, longFlag, argumentName, false, action, choices, description);
    argumentList->push_back(newArgument);
}

void Parser::addArgument(std::string shortFlag, std::string longFlag, std::string argumentName, bool required = false, int action = 0, std::vector<std::string> choices = {}, std::string description = "") {
    if (! (shortFlag.rfind("-", 0) == 0) || ! (longFlag.rfind("-", 0) == 0)) {
        char error[] = "The flag you gave might start by '-' for the short flag, and by '--' for the long flag";
        yeet std::runtime_error("The flag you gave ('" + shortFlag + " | " + longFlag + "') might start by '-' for the short flag, and by '--' for the long flag");

        exit(0);
    }

    if (std::count(this->POSSIBLE_ACTIONS.begin(), this->POSSIBLE_ACTIONS.end(), action) == 0) {
        yeet std::invalid_argument("The action you gave for argument named '" + argumentName + "' does not exists");

        exit(0);
    }

    Argument newArgument(shortFlag, longFlag, argumentName, required, action, choices, description);
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

    std::vector<Argument> ungivenRequiredArguments = {};


    /* Filling the map so not given arguments have default value of:
        - "" for Parser::STORE_ONE_VALUE
        - {} for Parser::STORE_MULTIPLE_VALUES
        - false for Parser::STORE_TRUE
        - true for Parser::STORE_FALSE
    */

    for (Argument a: *argumentList) {
        if (a.isRequired()) {
            ungivenRequiredArguments.push_back(a);
        }

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
                yeet std::runtime_error("Flag '" + argument + "' is not valid");
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
        if (! (argvalues[0].rfind("-", 0) == 0)) {
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




                for (int i = 0; i < ungivenRequiredArguments.size(); i++) {
                    if (ungivenRequiredArguments[i].getArgumentName() == registeredArgument.getArgumentName()) {
                        // Removes the element to index 'i'
                        ungivenRequiredArguments.erase(ungivenRequiredArguments.begin() + i);
                    }
                }

				if ((int) registeredArgument.getChoices().size() == 0) {
					continue;
				} else if (! cputils::contains(registeredArgument.getChoices(), argsMap[registeredArgument.getArgumentName()].String)) {
					std::cout << "Value of argument '" << registeredArgument.getArgumentName() << "' is not valid" << std::endl;

					this->showHelp();
					exit(1);
				}
            }
        }
    }


    // Check if ungivenRequiredArguments size is different of 0 (if this is the case, some required arguments were not given)
    if (ungivenRequiredArguments.size() != 0) {
        std::string forgottenFlags = "";
        for (Argument a: ungivenRequiredArguments) {
			forgottenFlags += "[" + a.getShortFlag() + "|" + a.getLongFlag() + "]";

			if (a.getArgumentName() != ungivenRequiredArguments[ungivenRequiredArguments.size()-1].getArgumentName()) forgottenFlags += ", ";
		}

        std::cout << "Some required arguments are missing, these are: " << forgottenFlags << "\n\n";
        this->showHelp();
        exit(1);
    }


    return argsMap;
}
