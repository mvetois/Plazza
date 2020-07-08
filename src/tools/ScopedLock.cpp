/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ScopedLock
*/

#include "ScopedLock.hpp"

using Tools::ScopedLock;

ScopedLock::ScopedLock(Mutex &mutex) : _mutex(mutex)
{
    _mutex.lock();
}

ScopedLock::~ScopedLock()
{
    _mutex.unlock();
}
