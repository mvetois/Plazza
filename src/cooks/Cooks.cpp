/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cooks
*/

#include <vector>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include "Cooks.hpp"
#include "Log.hpp"

using Plazza::Cooks;

Cooks::Cooks(Pizza *pizza) : _pizza(pizza)
{
}

Cooks::~Cooks()
{
}

void Cooks::cook(std::string &name)
{
    usleep(_pizza->getCookingTime() * 1000000);
    std::cout << "Cook[" << name << "]: a " << _pizza->getName() << " " << _pizza->getSize() << " is ready! Enjoy your meal!" << std::endl;
    Log log;
    log.write("Cook[" + name + "]: has done " + _pizza->getName() + " " + _pizza->getSize());
}