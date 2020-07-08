/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include <iostream>
#include "Process.hpp"

namespace Plazza {

    class Factory {
        public:
            Factory(std::string const &namedPathInput, std::string const &namedPathOutput, int cooksPerKitchen, int refreshTime);
            ~Factory();
        private:
            Tools::Process *_process;
    };
}

#endif /* !FACTORY_HPP_ */
