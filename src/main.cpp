/*
** EPITECH PROJECT, 2020
** Plazza
** File description:
** main
*/

#include "Cmd.hpp"
#include "Parsing.hpp"
#include "Reception.hpp"

#include "Pizza.hpp"
#include "Cooks.hpp"
#include "Error.hpp"
#include "Mutex.hpp"
#include "Thread.hpp"
#include "Pizza.hpp"
#include "ThreadPool.hpp"
#include "ScopedLock.hpp"
#include "Log.hpp"

using Tools::Mutex;
using Tools::Thread;
using Tools::ThreadPool;
using Tools::ScopedLock;
using Plazza::Pizza;
using Plazza::Cooks;

int main(int argc, char **argv)
{
    srand(time(0));
    try {
        Log log;
        log.clear();
        Plazza::Parsing arg(argc, argv);
        Plazza::Reception pizzeria(argc, argv, Plazza::alberto);
        Plazza::Cmd term(arg, pizzeria);
        term.launchTerm();
    }
    catch (Plazza::Error &ex) {
        ex.what();
    }
    return 0;
}