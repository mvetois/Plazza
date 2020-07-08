/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** cmd
*/

#ifndef CMD_HPP_
#define CMD_HPP_

#include "Reception.hpp"
#include "Parsing.hpp"
#include <iostream>

namespace Plazza {

    class Cmd {
        public:
            Cmd(Plazza::Parsing pars, Plazza::Reception room);
            ~Cmd();
            std::string getCommand() const;
            void launchTerm();
            void passCommand();
            void killKitchen();
        protected:
        private:
        Plazza::Parsing _pars;
        Plazza::Reception _room;
        std::string _command;
    };
};

#endif /* !CMD_HPP_ */
