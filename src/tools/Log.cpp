/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** Log
*/

#include "Log.hpp"

Log::Log()
{
}

Log::Log(std::string str)
{
    std::ofstream ofs("log.txt", std::ios_base::app);

    ofs << str << std::endl;
    ofs.close();
}

Log::~Log()
{
}

bool Log::write(std::string str)
{
    std::ofstream ofs("log.txt", std::ios_base::app);

    if (!ofs.is_open())
        return (false);
    ofs << str << std::endl;
    ofs.close();
    return (true);
}

bool Log::clear()
{
    std::ofstream ofs("log.txt", std::ofstream::out);
    if (!ofs.is_open())
        return (false);
    ofs << "[Plazza Log File]" << std::endl;
    ofs.close();
    return (true);
}