/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** log
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/Log.hpp"

Test(log_01, log)
{
    Log log;

    cr_assert(log.clear() == true);
}

Test(log_02, log)
{
    Log log;

    cr_assert(log.write("tests") == true);
}

Test(log_03, log)
{
    Log log("tests");

    cr_assert(log.write("tests") == true);
}