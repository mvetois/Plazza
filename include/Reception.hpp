/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <chrono>
#include <map>
#include <vector>
#include <queue>
#include <list>
#include <string>
#include <utility>
#include <signal.h>
#include "Pizza.hpp"
#include "Pipe.hpp"

namespace Plazza {

    typedef enum server_e {
        alberto = 1
    } server;

    class Reception {
        public:
            Reception(int argc, char **argv, server serv);
            ~Reception();
            void killKitchens();
            void createPizza(std::string &pizzaOrder);
            void handleQueue();
            void kitchenStatus();
            std::pair<Tools::Input *, Tools::Output *> createKitchen();
        private:
            double _cookingTime;
            int _cooksPerKitchen;
            int _refreshTime;
            server _server;
            std::map<int, Pizza *(*)(Pizza::PizzaSize, double)> _pizzas;
            std::map<std::string, Pizza::PizzaType> _pizzasName;
            std::map<std::string, Pizza::PizzaSize> _pizzasSize;
            std::list<std::pair<Tools::Input *, Tools::Output *>> _kitchens;
            std::queue<Pizza *> _orders;
    };
};

#endif /* !RECEPTION_HPP_ */
