/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** pizza
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/Pizza.hpp"
#include "../include/Error.hpp"

using Plazza::Pizza;
using Plazza::Error;

Test(pizza_01, pizza)
{
    Pizza *cmd = Plazza::Americana::newAmericana(Pizza::PizzaSize::S, 0.5);
    cr_assert(cmd != nullptr);
    cr_assert(cmd->getSize() == "S");
    delete cmd;
}

Test(pizza_02, pizza)
{
    Pizza *cmd = Plazza::Fantasia::newFantasia(Pizza::PizzaSize::M, 0.5);
    cr_assert(cmd != nullptr);
    cr_assert(cmd->getSize() == "M");
    delete cmd;
}

Test(pizza_03, pizza)
{
    Pizza *cmd = Plazza::Margarita::newMargarita(Pizza::PizzaSize::L, 0.5);
    cr_assert(cmd != nullptr);
    cr_assert(cmd->getSize() == "L");
    delete cmd;
}

Test(pizza_04, pizza)
{
    Pizza *cmd = Plazza::Regina::newRegina(Pizza::PizzaSize::XL, 0.5);
    cr_assert(cmd != nullptr);
    cr_assert(cmd->getSize() == "XL");
    delete cmd;
}

Test(pizza_05, pizza)
{
    try {
        Pizza *cmd = Plazza::Regina::newRegina(Pizza::PizzaSize::XXL, 0.5);
        cr_assert(cmd != nullptr);
        cr_assert(cmd->getName() == "Regina");
        cr_assert(cmd->getSize() == "XXL");
        cr_assert(cmd->getType() == Pizza::Regina);
        cr_assert(cmd->getCookingTime() == 0.5);
        std::vector<Plazza::Pizza::Ingredients> ing;
        ing.push_back(Plazza::Pizza::Ingredients::Doe);
        ing.push_back(Plazza::Pizza::Ingredients::Tomato);
        ing.push_back(Plazza::Pizza::Ingredients::Gruyere);
        cr_assert(cmd->getIngredient() == ing);
        std::string pack = cmd->pack(*cmd);
        Pizza *a = Pizza::unpack(pack);
        delete cmd;
    } catch (Error &ex) {
        ex.what();
    }
}