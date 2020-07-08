/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ThreadHandle
*/

#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>

namespace Tools {

    class IMutex {
        public:
            virtual ~IMutex() = default;
            virtual void lock() = 0;
            virtual void unlock() = 0;
            virtual void trylock() = 0;
    };

    class Mutex : public IMutex {

        public:
            typedef enum status_e {
                LOCK,
                UNLOCK
            } status_t;

            Mutex();
            virtual ~Mutex();
            virtual void lock();
            virtual void unlock();
            virtual void trylock();

            pthread_mutex_t *getMutex() const;
        private:
            pthread_mutex_t *_mutex;
            Mutex::status_t _status;
    };

};
#endif /* !MUTEX_HPP */
