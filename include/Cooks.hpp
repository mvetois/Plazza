/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cooks
*/

#ifndef COOKS_HPP_
#define COOKS_HPP_

#include <map>
#include <vector>
#include <string>
#include "ICooking.hpp"
#include "Pizza.hpp"

namespace Plazza {

    class Cooks : public ICooking {
        public:
            Cooks(Pizza *pizza);
            ~Cooks();
            virtual void cook(std::string &name);
        private:
            Pizza *_pizza;
    };

};

#endif /* !COOKS_HPP_ */
