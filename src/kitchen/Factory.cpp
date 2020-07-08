/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Factory
*/

#include "Factory.hpp"
#include "Kitchen.hpp"
#include "Process.hpp"

using Plazza::Factory;
using Plazza::Kitchen;
using Tools::Process;

Factory::Factory(std::string const &namedPathInput, std::string const &namedPathOutput, int cooksPerKitchen, int refreshTime)
{
    Kitchen *kitchen = new Kitchen(namedPathInput, namedPathOutput, cooksPerKitchen, refreshTime);
    _process = new Process(*kitchen);
    delete kitchen;
}

Factory::~Factory()
{
    delete _process;
}
