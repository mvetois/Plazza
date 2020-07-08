/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Reception
*/

#include <ostream>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include "Error.hpp"
#include "Reception.hpp"
#include "Parsing.hpp"
#include "Log.hpp"
#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include "Factory.hpp"

using Plazza::Reception;
using Plazza::Parsing;
using Plazza::Pizza;
using Tools::Mutex;
using Tools::ScopedLock;

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

template<typename Clock, typename Duration>
std::ostream &operator<<(std::ostream &stream, const std::chrono::time_point<Clock, Duration> &time_point)
{
    const time_t time = Clock::to_time_t(time_point);
    char buffer[26];
    ctime_r(&time, buffer);
    buffer[24] = '\0';  // Removes the newline that is added
    return stream << buffer;
}

Reception::Reception(int argc, char **argv, server serv) : _cookingTime(atof(argv[1])), _cooksPerKitchen(atoi(argv[2])), _refreshTime(atoi(argv[3])), _server(serv)
{
    std::chrono::system_clock ourTime;
    _pizzas[Pizza::Regina] = &Plazza::Regina::newRegina;
    _pizzas[Pizza::Margarita] = &Plazza::Margarita::newMargarita;
    _pizzas[Pizza::Americana] = &Plazza::Americana::newAmericana;
    _pizzas[Pizza::Fantasia] = &Plazza::Fantasia::newFantasia;
    _pizzasName["Regina"] = Pizza::Regina;
    _pizzasName["Margarita"] = Pizza::Margarita;
    _pizzasName["Americana"] = Pizza::Americana;
    _pizzasName["Fantasia"] = Pizza::Fantasia;
    _pizzasSize["S"] = Pizza::S;
    _pizzasSize["M"] = Pizza::M;
    _pizzasSize["L"] = Pizza::L;
    _pizzasSize["XL"] = Pizza::XL;
    _pizzasSize["XXL"] = Pizza::XXL;
    if (_server == alberto) {
        std::cout << "Buongiorno, my name is Alberto, it's " << ourTime.now() << ", can i take your order please?" << std::endl;
        Log log;
        log.write("Initalisation...");
    }
}

Reception::~Reception()
{
}

void Reception::killKitchens()
{
    for (std::list<std::pair<Tools::Input *, Tools::Output *>>::iterator kitchen = _kitchens.begin(); kitchen != _kitchens.end(); ++kitchen) {
		kitchen->second->write("kill");
	}
}

void Reception::createPizza(std::string &pizzaOrder)
{
    std::vector<std::string> params = split(pizzaOrder, ' ');
    int nb_pizza;

    if (!params.empty() && params.size() == 3) {
        nb_pizza = std::stoi(params[2].erase(0, 1));
        for (int i = 0; i < nb_pizza; i++)
            _orders.push((_pizzas.find(_pizzasName.find(params[0])->second)->second)(_pizzasSize.find(params[1])->second, _cookingTime));
    }
}

void Reception::handleQueue()
{
    Mutex mutex;
    ScopedLock locker(mutex);
    std::string nbCooks;
    std::string kitchenCanCook;

    if (_orders.empty())
        return;
    if (_kitchens.empty())
        this->createKitchen();
    while (!_orders.empty()) {
        Pizza *pizza = _orders.front();
        _orders.pop();

        std::list<std::pair<Tools::Input *, Tools::Output *>> freeCooksInKitchen;
        for (std::list<std::pair<Tools::Input *, Tools::Output *>>::iterator kitchen = _kitchens.begin(); kitchen != _kitchens.end(); ++kitchen) {
            Tools::Input *in = (*kitchen).first;
            Tools::Output *out = (*kitchen).second;
            (*out).write("freeCooks");
            (*in).read(nbCooks);
            if (nbCooks == "kitchenClosing") {
                delete (*kitchen).first;
                delete (*kitchen).second;
                kitchen = _kitchens.erase(kitchen);
                --kitchen;
            } else {
                (*out).write("canCook " + Pizza::pack(*pizza));
                (*in).read(kitchenCanCook);
                if (nbCooks != "0" && kitchenCanCook != "kitchenClosing" && kitchenCanCook == "true") {
                    freeCooksInKitchen.push_back(std::make_pair((*kitchen).first, (*kitchen).second));
                } else if (kitchenCanCook == "kitchenClosing") {
                    delete (*kitchen).first;
                    delete (*kitchen).second;
                    kitchen = _kitchens.erase(kitchen);
                    --kitchen;
                }
            }
        }
        if (!_kitchens.empty() && !freeCooksInKitchen.empty()) {
            Tools::Output *cookingKitchen = freeCooksInKitchen.front().second;
            (*cookingKitchen).write("cook: " + Pizza::pack(*pizza));
        } else {
            Tools::Output *newKitchen = this->createKitchen().second;
            (*newKitchen).write("cook: " + Pizza::pack(*pizza));
        }
    }
}

void Reception::kitchenStatus()
{
    std::cout << "[status]" << std::endl;
    for (std::list<std::pair<Tools::Input *, Tools::Output *>>::iterator kitchen = _kitchens.begin(); kitchen != _kitchens.end(); ++kitchen) {
        Tools::Output *out = (*kitchen).second;
        (*out).write("status");
    }
}

std::pair<Tools::Input *, Tools::Output *> Reception::createKitchen()
{
    static int kitchenNumber = 0;
    Mutex mutex;
    ScopedLock locker(mutex);
    std::string pipeIn = "/tmp/kitchenIn_" + std::to_string(kitchenNumber);
    std::string pipeOut = "/tmp/kitchenOut_" + std::to_string(kitchenNumber);
    new Factory(pipeIn, pipeOut, _cooksPerKitchen, _refreshTime);

    Mutex pipe;
    pipe.lock();
    Tools::Input *in = new Tools::Input(pipeIn);
    pipe.unlock();
    pipe.lock();
    Tools::Output *out = new Tools::Output(pipeOut);
    pipe.unlock();
    _kitchens.push_back(std::make_pair(in, out));
    kitchenNumber++;
    return _kitchens.back();
}