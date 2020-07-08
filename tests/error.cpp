/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** error
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/Error.hpp"

using Plazza::Error;

Test(error_01, error)
{
    Error e(Error::Code::NO, "error", Error::Type::COMMON);
    cr_assert(e.getType() == "COMMON");
    cr_assert(e.what() != "");
}

Test(error_02, error)
{
    Error e(Error::Code::NO, "error", Error::Type::FATAL);
    cr_assert(e.getType() == "FATAL");
}

Test(error_03, error)
{
    Error e(Error::Code::NO, "None", Error::Type::NONE);
    cr_assert(e.getType() == "NONE");
}