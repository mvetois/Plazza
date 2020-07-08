/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ThreadPool
*/

#include <algorithm>
#include "ThreadPool.hpp"

using Tools::ThreadPool;

ThreadPool::ThreadPool(int nbThread)
{
    for (int i = 0; i < nbThread; i++)
        _cooks.push_back(new Thread);
    for (std::list<Thread *>::iterator thread = _cooks.begin(); thread != _cooks.end(); ++thread) {
        (*thread)->genName();
    }
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::addTask(ICooking *task)
{
    _tasksQueue.push(task);
}

void ThreadPool::executeTasks()
{
    for (std::list<Thread *>::iterator thread = _cooks.begin(); thread != _cooks.end(); ++thread) {
        if (_tasksQueue.empty())
            break;
        if ((*thread)->getStatus() == IThread::WAITING) {
            (*thread)->runTask(_tasksQueue.front());
            _tasksQueue.pop();
        }
    }
}

std::vector<IThread::status_t> ThreadPool::getStatus() const
{
    std::vector<IThread::status_t> threadsStatus;

    for (std::list<Thread *>::const_iterator thread = _cooks.begin(); thread != _cooks.end(); ++thread)
        threadsStatus.push_back((*thread)->getStatus());
    return threadsStatus;
}

int ThreadPool::cooksAvailable() const
{
    int i = 0;
    std::vector<IThread::status_t> cooksStatus = this->getStatus();

    i = std::count(cooksStatus.begin(), cooksStatus.end(), IThread::WAITING);
    return i;
}