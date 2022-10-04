#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>



// TODO : do function documentation, class and constructor documentation


// Due to some C++ restrictions (that are, I could say, part of the core of the language itself)
// I made some functions and classes inside this namespace to make easier the use of your argument values

// In every function/class I will write why I put his here, and an example of how and why to use it
// TODO : do what the comment above this one says

namespace cputils {
	std::string strip(std::string string);
    std::vector<std::string> split(std::string string, char separator);
    std::string removeLastChar(std::string string);

	template <typename T>
	bool contains(std::vector<T> v, T value);

    template <typename T>
    void shift(std::vector<T>* vector);

    std::string getArgValue(std::vector<std::string>* argsVector);
    std::string multiplyChar(std::string toMultiply, int multiplicator);
    std::vector<std::string> toVector(char** array, int arraySize);


    class UnknownFlagException : public std::exception {
        private:
            char* message;

        public:
            UnknownFlagException(char* errorMessage);

            char* what(std::string flagName);
    };


    class InvalidFlagException : public std::exception {
        private:
            char* message;
        
        public:
            InvalidFlagException(char* errorMessage);

            char* what();
    };
}


class Argument {
    private:
        std::string shortFlag;
        std::string longFlag;
        std::string argumentName;
        bool required;
        int action;
		std::vector<std::string> choices;
        std::string description;

    public:
        Argument(std::string shortFlag, std::string longFlag, std::string argumentName, bool required, int action, std::vector<std::string> choices, std::string description);

        std::string getShortFlag();
        std::string getLongFlag();
        std::string getArgumentName();
        bool isRequired();
        int getAction();
		std::vector<std::string> getChoices();
        std::string getDescription();

		bool hasChoice(std::string to_check);
};



struct ArgumentValue {
    // The values it could take
    std::string String = "";
    std::vector<std::string> Vector = {};
    bool Bool;


    operator std::string() {return String;}
    operator std::vector<std::string>() {return Vector;}
    operator bool() {return Bool;}
};

std::ostream& operator<<(std::ostream &stream, const ArgumentValue &argval);


class Parser {
    private:
        bool throwError;

        std::string description;
        std::vector<Argument>* argumentList = new std::vector<Argument>();

        bool isArgumentRegistered(std::string flagName);


    public:
        static const int STORE_ONE_VALUE = 0;
        static const int STORE_MULTIPLE_VALUES = 1;
        static const int STORE_TRUE = 2;
        static const int STORE_FALSE = 3;

        const std::vector<int> POSSIBLE_ACTIONS = {
            Parser::STORE_ONE_VALUE,
            Parser::STORE_MULTIPLE_VALUES,
            Parser::STORE_TRUE,
            Parser::STORE_FALSE,
        };


        Parser(std::string help, bool throwError);
        Parser(std::string help);

        void showHelp();

        std::vector<Argument> getArgs();

        void addArgument(std::string shortFlag, std::string longFlag, std::string argumentName, bool required, int action, std::string description);
        void addArgument(std::string shortFlag, std::string longFlag, std::string argumentName, int action, std::string description);
        void addArgument(std::string shortFlag, std::string longFlag, std::string argumentName, bool required, int action, std::vector<std::string> choices, std::string description);
        void addArgument(std::string shortFlag, std::string longFlag, std::string argumentName, int action, std::vector<std::string> choices, std::string description);

        std::map<std::string, ArgumentValue> parseArgs(int argc, char** argv);
};
