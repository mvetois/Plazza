/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Thread
*/

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <string>
#include <iostream>
#include <pthread.h>
#include "ICooking.hpp"

namespace Tools {

    class IThread {
        public:
            typedef enum status_e {
                WAITING,
                RUNNING,
                DEAD
            } status_t;

            virtual ~IThread() = default;
            virtual void startThread(void *(*startRoutine)(void *), void *arg) = 0;
            virtual void *waitThread() = 0;
            virtual void stopThread(void *ret_val) = 0;
            virtual void runTask(ICooking *task) = 0;
            virtual IThread::status_t getStatus() const = 0;
            virtual void genName() = 0;
    };

    class Thread : public IThread {
        public:
            Thread();
            virtual ~Thread();
            virtual void startThread(void *(*startRoutine)(void *), void *arg);
            virtual void *waitThread();
            virtual void stopThread(void *ret_val);
            virtual void runTask(ICooking *task);
            virtual IThread::status_t getStatus() const;
            virtual void genName();
        private:
            static void *execTask(void *);
        private:
            std::string _name;
            IThread::status_t _status;
            pthread_t _thread;
            ICooking *_task;
    };

};
#endif /* !THREAD_HPP_ */
