/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Thread
*/

#include <vector>
#include <fstream>
#include "Error.hpp"
#include "Thread.hpp"
#include "Log.hpp"

using Plazza::Error;
using Tools::Thread;
using Tools::IThread;

Thread::Thread() : _name(""), _status(IThread::WAITING)
{
}

Thread::~Thread()
{
    if (_status == IThread::RUNNING)
        this->stopThread(NULL);
}

void Thread::genName()
{
    std::vector<std::string> names;
    std::fstream fs;
    std::string str;

    fs.open("./data/CooksNames", std::fstream::in);
    if (fs.fail()) {
        _name = "Jean Neymar rend mon fichier";
    } else {
        std::getline(fs, str);
        while (!fs.eof()) {
            std::getline(fs, str);
            names.push_back(str.substr(1, str.size() - 2));
        }
        _name = names[rand() % names.size()];
    }
    std::cout <<"Cook[" << _name << "]: is ready to work" << std::endl;
    Log log("Cook["+ _name + "]: is ready to work");
}

Thread::status_t Thread::getStatus() const
{
    return _status;
}

void Thread::startThread(void *(*startRoutine)(void *), void *arg)
{
    if (_status == IThread::RUNNING)
        throw Error(Error::Code::THREADSTART, "startThread() : the thread is already running", Error::Type::FATAL);
    if (_status == IThread::DEAD)
        throw Error(Error::Code::THREADSTART, "startThread() : the thread is dead", Error::Type::FATAL);
    _status = IThread::RUNNING;
    if (pthread_create(&_thread, NULL, startRoutine, arg) != 0)
        throw Error(Error::Code::THREADSTART, "startThread() : failed", Error::Type::FATAL);
}

void *Thread::waitThread()
{
    void *ret_val;

    if (_status != IThread::RUNNING)
        throw Error(Error::Code::THREADWAIT, "waitThread() : the thread is not running", Error::Type::FATAL);
    if (pthread_join(_thread, &ret_val) != 0)
        throw Error(Error::Code::THREADWAIT, "waitThread() : failed", Error::Type::FATAL);
    _status = IThread::DEAD;
    return ret_val;
}

void Thread::stopThread(void *ret_val)
{
    if (_status != IThread::RUNNING)
        throw Error(Error::Code::THREADSTOP, "stopThread() : the thread is not running", Error::Type::FATAL);
    _status = IThread::DEAD;
    pthread_exit(ret_val);
}

void Thread::runTask(ICooking *task)
{
    _task = task;

    if (_status == IThread::RUNNING)
        throw Error(Error::Code::THREADRUNTASK, "runTask() : the thread is already running", Error::Type::FATAL);
    if (_status == IThread::DEAD)
        throw Error(Error::Code::THREADRUNTASK, "runTask() : the thread is dead", Error::Type::FATAL);
    _status = IThread::RUNNING;
    if (pthread_create(&_thread, NULL, &Thread::execTask, this) != 0)
        throw Error(Error::Code::THREADRUNTASK, "runTask() : failed", Error::Type::FATAL);
}

void *Thread::execTask(void *arg)
{
    Thread *thread = static_cast<Thread *>(arg);

    thread->_task->cook(thread->_name);
    thread->_status = IThread::WAITING;
    return NULL;
}