/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Process
*/

#include <sys/types.h>
#include <sys/wait.h>
#include "Error.hpp"
#include "Process.hpp"

using Plazza::Error;
using Tools::Process;
using Tools::IProcess;

Process::Process(ICooking &task) : _pid(0), _status(IProcess::WAITING), _text("kitchen")
{
    if ((_pid = fork()) == -1)
        throw Error(Error::Code::PROCESSCREATE, "Process : fork failed", Error::Type::FATAL);
    if (_pid == 0) {
            task.cook(_text);
            exit(0);
            throw Error(Error::Code::PROCESSCREATE, "Process exit Failed", Error::Type::FATAL);
    }
    else
        _status = IProcess::RUNNING;
}

Process::~Process()
{
    this->waitProcess();
}

void Process::waitProcess()
{
    if (_status == Process::RUNNING) {
        if (waitpid(_pid, NULL, 0) == -1)
            throw Error(Error::Code::PROCESSWAIT, "waitProcess() : waitpid failed", Error::Type::FATAL);
        _status = Process::WAITING;
    }
}