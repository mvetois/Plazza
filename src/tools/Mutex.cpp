/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Mutex
*/

#include "Error.hpp"
#include "Mutex.hpp"

using Plazza::Error;
using Tools::Mutex;

Mutex::Mutex() : _mutex(new pthread_mutex_t), _status(Mutex::UNLOCK)
{
    if (pthread_mutex_init(_mutex, NULL) != 0)
        throw Error(Error::Code::MUTEXFAIL, "Mutex::init() : failed", Error::Type::FATAL);
}

Mutex::~Mutex()
{
    if (_status == Mutex::LOCK)
        this->unlock();
    if (pthread_mutex_destroy(_mutex) != 0) {
        std::cerr << "[ERROR]: Mutex::destroy() : failed | FATAL ERROR" << std::endl;
        exit(84);
    }
}

void Mutex::lock()
{
    if (pthread_mutex_lock(_mutex) != 0)
        throw Error(Error::Code::MUTEXLOCK, "Mutex::lock() : failed", Error::Type::FATAL);
    _status = Mutex::LOCK;
}

void Mutex::unlock()
{
    if (pthread_mutex_unlock(_mutex) != 0)
        throw Error(Error::Code::MUTEXLOCK, "Mutex::unlock() : failed", Error::Type::FATAL);
    _status = Mutex::UNLOCK;
}

void Mutex::trylock()
{
    bool lock = pthread_mutex_trylock(_mutex) == 0;

    _status = lock ? Mutex::LOCK : Mutex::UNLOCK;
}

pthread_mutex_t *Mutex::getMutex() const
{
    return _mutex;
}
