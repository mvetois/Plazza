/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#include <string>
#include <sstream>
#include "Error.hpp"
#include "Pizza.hpp"

using Plazza::Pizza;
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

Pizza::Pizza(int pizzaType, PizzaSize size, double) : _size(size), _pizzaType(pizzaType)
{
}

Pizza::~Pizza()
{
}

std::string Pizza::pack(Pizza toPack)
{
    std::string pack = std::to_string(toPack.getType()) + " " + toPack.getSize() + " " + std::to_string(toPack.getCookingTime());
    return pack;
}

static Pizza::PizzaSize parsSize(std::string size)
{
    if (size == "S")
        return Pizza::PizzaSize::S;
    if (size == "M")
        return Pizza::PizzaSize::M;
    if (size == "L")
        return Pizza::PizzaSize::L;
    if (size == "XL")
        return Pizza::PizzaSize::XL;
    if (size == "XXL")
        return Pizza::PizzaSize::XXL;
    throw Error(Error::Code::UNDEFINEDPIZZA, "The Pizza Size to pack is undefined", Error::Type::FATAL);
    return Pizza::PizzaSize::XXL;
}


Pizza *Pizza::unpack(std::string toUnpack)
{
    std::vector<std::string> params = split(toUnpack, ' ');
    std::string pizzaType = params[0];
    std::string size = params[1];
    std::string cookingMultiplier = params[2];
    if (atoi(pizzaType.c_str()) == Regina)
        return Plazza::Regina::newRegina(parsSize(size), atof(cookingMultiplier.c_str()));
    if (atoi(pizzaType.c_str()) == Americana)
        return Plazza::Americana::newAmericana(parsSize(size), atof(cookingMultiplier.c_str()));
    if (atoi(pizzaType.c_str()) == Fantasia)
        return Plazza::Fantasia::newFantasia(parsSize(size), atof(cookingMultiplier.c_str()));
    if (atoi(pizzaType.c_str()) == Margarita)
        return Plazza::Margarita::newMargarita(parsSize(size), atof(cookingMultiplier.c_str()));
    throw Error(Error::Code::UNDEFINEDPIZZA, "Pizza to unpack is undefined", Error::Type::FATAL);
    return nullptr;
}

double Pizza::getCookingTime() const
{
    return _cookingTime;
}

std::string Pizza::getName() const
{
    return _name;
}

int Pizza::getType() const
{
    return _pizzaType;
}

std::string Pizza::getSize() const
{
    if (_size == Pizza::S)
        return "S";
    if (_size == Pizza::M)
        return "M";
    if (_size == Pizza::L)
        return "L";
    if (_size == Pizza::XL)
        return "XL";
    if (_size == Pizza::XXL)
        return "XXL";
    return "";
}

std::vector<Pizza::Ingredients> Pizza::getIngredient() const
{
    return _ingredient;
}