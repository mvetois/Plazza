/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Margarita
*/

#include "Pizza.hpp"

using Plazza::Pizza;
using Plazza::Margarita;

Margarita::Margarita(PizzaSize size, double cookingMultiplier) : Pizza(Pizza::Margarita, size, cookingMultiplier)
{
    _name = "Margarita";
    _ingredient.push_back(Doe);
    _ingredient.push_back(Tomato);
    _ingredient.push_back(Gruyere);
    _ingredient.push_back(Ham);
    _ingredient.push_back(Mushrooms);
    _cookingTime = 2 * cookingMultiplier;
}

Margarita::~Margarita()
{
}

Plazza::Pizza *Margarita::newMargarita(PizzaSize size, double cookingMultiplier)
{
    return new Margarita(size, cookingMultiplier);
}