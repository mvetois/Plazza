/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Process
*/

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include <unistd.h>
#include "ICooking.hpp"

namespace Tools {

    class IProcess {
        public:
            typedef enum status_e {
                RUNNING,
                WAITING
            } status_t;

            virtual ~IProcess() = default;
            virtual void waitProcess() = 0;
    };

    class Process : public IProcess {
        public:
            Process(ICooking &task);
            virtual ~Process();

            virtual void waitProcess();
        private:
            pid_t _pid;
            IProcess::status_t _status;
            std::string _text;
    };

}

#endif /* !PROCESS_HPP_ */