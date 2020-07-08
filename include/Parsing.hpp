/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <regex>
#include <iostream>

namespace Plazza {
    
    class Parsing {
        public:
            Parsing(int argc, char **argv);
            ~Parsing();
            bool CheckMainArgs(int argc, char **argv);
            void FillPizzaCmd(std::string command);
            bool CheckPizzaCmd(std::string command);
            bool CheckCommand(std::string command);
            bool IsNum(const char *str);
            std::string GetPizzaName() const;
            std::string GetPizzaSize() const;
            std::string GetPizzaNumber() const;
        private:
            std::string _pizzaName;
            std::string _pizzaSize;
            std::string _pizzaNumber;
    };
}

#endif /* !PARSING_HPP_ */
