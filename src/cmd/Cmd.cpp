/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** cmd
*/

#include "Reception.hpp"
#include "Parsing.hpp"
#include "Error.hpp"
#include "Pizza.hpp"
#include "Cmd.hpp"
#include "Log.hpp"

#include <sys/types.h>
#include <unistd.h>

using Plazza::Cmd;
using Plazza::Parsing;
using Plazza::Reception;
using Plazza::Pizza;

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

Cmd::Cmd(Parsing pars, Reception room) : _command(""), _pars(pars), _room(room)
{
}

Cmd::~Cmd()
{
}

void Cmd::killKitchen()
{
    // for (std::map<int, std::string>::iterator it = _room.GetKitchen().begin(); it != _room.GetKitchen().end(); it++) {
    //     kill(it->first, SIGKILL);
    //     _room.GetKitchen().erase(it);
    // }
}

void Cmd::launchTerm()
{
    Log log;
    std::vector<std::string> pizzaOrders;
    while (true) {
        std::getline(std::cin, _command);
        log.write("User[Input]: " + _command);
        if (_command == "exit" || _command == "quit")
            return _room.killKitchens();
        if (_command == "status") {
            _room.kitchenStatus();
            continue;
        }
        if (!std::cin) {
            if (std::cin.eof())
                exit(0);
            exit(84);
        }
        try {
            if (!_pars.CheckCommand(_command))
                return;
            pizzaOrders = split(_command, ';');
            for (int i = 1; i < pizzaOrders.size(); i++)
                pizzaOrders[i].erase(0, 1);
            for (int i = 0; i < pizzaOrders.size(); i++)
                _room.createPizza(pizzaOrders[i]);
            _room.handleQueue();
        }
        catch(Plazza::Error& ex) {
            ex.what();
        }
    }
}

std::string Cmd::getCommand() const
{
    return _command;
}