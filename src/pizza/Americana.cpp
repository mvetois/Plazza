/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Americana
*/

#include "Pizza.hpp"

using Plazza::Pizza;
using Plazza::Americana;

Americana::Americana(PizzaSize size, double cookingMultiplier) : Pizza(Pizza::Americana, size, cookingMultiplier)
{
    _name = "Americana";
    _ingredient.push_back(Doe);
    _ingredient.push_back(Tomato);
    _ingredient.push_back(Gruyere);
    _ingredient.push_back(Steak);
    _cookingTime = 2 * cookingMultiplier;
}

Americana::~Americana()
{
}

Plazza::Pizza *Americana::newAmericana(PizzaSize size, double cookingMultiplier)
{
    return new Americana(size, cookingMultiplier);
}