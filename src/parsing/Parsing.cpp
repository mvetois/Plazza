/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** Parsing
*/

#include "Pizza.hpp"
#include "Error.hpp"
#include "Parsing.hpp"

using Plazza::Parsing;
using Plazza::Error;

static std::vector<std::string> split(std::string str, char delimiter)
{
    std::vector<std::string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;

    while (getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    return internal;
}

static void printUsage()
{
    std::cout << "Usage : ./plazza [arg1] [arg2] [arg3]\n\targ1: Multiplicator of cooking time of a pizza\n\targ2: Number of cooks by Kitchens\n\targ3: Refresh time of ingredients in milliseconde" << std::endl;
    exit(0);
}

Parsing::Parsing(int argc, char **argv)
{
    CheckMainArgs(argc, argv);
}

Parsing::~Parsing()
{
}

bool Parsing::IsNum(const char *str)
{
    for (int i = 0; str[i] != (const char)'\0'; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

bool Parsing::CheckMainArgs(int argc, char **argv)
{
    std::string arg;

    try {
        for (size_t i = 1; argv[i]; i++) {
            if ((arg = argv[i]) == "-help")
                printUsage();
        }
        if (argc < 4) {
            throw Error(Error::Code::MAINARGSNB, "Too few arguments for the program (use ./plazza -help)", Error::Type::FATAL);
        }
        if (argc > 4)
            throw Error(Error::Code::MAINARGSNB, "Too many arguments for the program (use ./plazza -help)", Error::Type::FATAL);
        for (size_t i = 2; argv[i]; i++) {
            if (!IsNum(argv[i]))
                throw Error(Error::Code::MAINARGSTYPE, "the argument '" + (arg = argv[i]) + "' is not correct (use ./plazza -help)", Error::Type::FATAL);
        }
        if (!IsNum(argv[1])) {
            if (std::regex_match(argv[1], std::regex("([0][.][0-9]+)")))
                return true;
            else
                throw Error(Error::Code::MAINARGSTYPE, "the first argument must be an int or a float between 0 and 1 (use ./plazza -help)", Error::Type::FATAL);
        }
    }
    catch(Plazza::Error& ex) {
        ex.what();
    }
    return true;
}

static bool checkPizzaName(std::string pizzaName)
{
    if (pizzaName == "Regina") 
        return true;
    if (pizzaName == "Margarita")
        return true;
    if (pizzaName == "Americana")
        return true;
    if (pizzaName == "Fantasia")
        return true;
    return false;
}

void Parsing::FillPizzaCmd(std::string command)
{
    _pizzaName = command.substr(0, command.find_first_of(" "));
    command = command.substr(command.find_first_of(" ") + 1, command.size());
    _pizzaSize = command.substr(0, command.find_first_of(" "));
    command = command.substr(command.find_first_of(" "), command.size());
    _pizzaNumber = command.substr(command.find_first_of(" ") + 1, command.size());
}

bool Parsing::CheckPizzaCmd(std::string command)
{
    FillPizzaCmd(command);
    if (std::regex_match(_pizzaName, std::regex("([A-Z][a-z])+"))) {
        throw Error(Error::Code::WRONGFORMAT, "The name format is uncorrect please respect the following syntax : TYPE SIZE NUMBER", Error::Type::COMMON);
        return false;
    }
    if (!checkPizzaName(_pizzaName)) {
        throw Error(Error::Code::UNDEFINEDPIZZA, "This Pizza '" + _pizzaName + "' is undefined", Error::Type::COMMON);
        return false;
    }
    if (std::regex_match(_pizzaSize, std::regex("(\b[S]\b)|(\b[M]\b)|(\b[L]\b)|(\b[X][L]\b)|(\b[X][X][L]\b)"))) {
        throw Error(Error::Code::WRONGFORMAT, "The size format is uncorrect please respect the following syntax : TYPE SIZE NUMBER", Error::Type::COMMON);
        return false;
    }
    if (std::regex_match(_pizzaNumber, std::regex("(\b[x][0-9]+\b)"))) {
        throw Error(Error::Code::WRONGFORMAT, "The number format is uncorrect please respect the following syntax : TYPE SIZE NUMBER", Error::Type::COMMON);
        return false;
    }
    return true;
}

bool Parsing::CheckCommand(std::string command)
{
    std::vector<std::string> pizzaCommands = split(command, ';');
    for (int i = 1; i < pizzaCommands.size(); i++)
        pizzaCommands[i].erase(0, 1);
    for (int i = 0; i < pizzaCommands.size(); i++) {
        if (std::regex_match(pizzaCommands[i], std::regex("([A-Z][a-z]+)([ ])(([S])|([M])|([L])|([X][L])|([X][X][L]))([ ])([x][0-9]+)"))) {
            if (!CheckPizzaCmd(pizzaCommands[i]))
                return false;
        } else {
            throw Error(Error::Code::UNDEFINEDCOMMAND, "the command '" + command + "' is undefined", Error::Type::COMMON);
        }
    }
    return true;
}

std::string Parsing::GetPizzaName() const
{
    return (_pizzaName);
}

std::string Parsing::GetPizzaSize() const
{
    return (_pizzaSize);
}

std::string Parsing::GetPizzaNumber() const
{
    return (_pizzaNumber);
}