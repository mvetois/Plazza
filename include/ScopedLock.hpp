/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ScopedLock
*/

#ifndef SCOPEDLOCK_HPP_
#define SCOPEDLOCK_HPP_

#include "Mutex.hpp"

namespace Tools {

    class ScopedLock {
        public:
            ScopedLock(Mutex &mutex);
            virtual ~ScopedLock();
        private:
            Mutex &_mutex;
    };

};
#endif /* !SCOPEDLOCK_HPP_ */
