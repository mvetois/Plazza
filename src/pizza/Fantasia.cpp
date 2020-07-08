/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Fantasia
*/

#include "Pizza.hpp"

using Plazza::Pizza;
using Plazza::Fantasia;

Fantasia::Fantasia(PizzaSize size, double cookingMultiplier) : Pizza(Pizza::Fantasia, size, cookingMultiplier)
{
    _name = "Fantasia";
    _ingredient.push_back(Doe);
    _ingredient.push_back(Tomato);
    _ingredient.push_back(EggPlant);
    _ingredient.push_back(GoatCheese);
    _cookingTime = 4 * cookingMultiplier;
}

Fantasia::~Fantasia()
{
}

Plazza::Pizza *Fantasia::newFantasia(PizzaSize size, double cookingMultiplier)
{
    return new Fantasia(size, cookingMultiplier);
}