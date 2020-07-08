/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ThreadPool
*/

#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

#include "Thread.hpp"
#include "ICooking.hpp"
#include <list>
#include <queue>

using Tools::Thread;
using Tools::IThread;

namespace Tools {

    class ThreadPool {
        public:
            ThreadPool(int nbThread);
            ~ThreadPool();

            void addTask(ICooking *task); 
            void executeTasks();

            std::vector<IThread::status_t> getStatus() const;
            int cooksAvailable() const;
        private:
            std::list<Thread *> _cooks;
            std::queue<ICooking *> _tasksQueue;
    };

};

#endif /* !THREADPOOL_HPP_ */