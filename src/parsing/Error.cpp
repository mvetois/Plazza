/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Error
*/

#include "Error.hpp"

using Plazza::Error;

Error::Error(Code error, std::string const& phrase, Type niveau) throw() : _code(error), _msg(phrase), _errorLv(niveau)
{
}

Error::~Error() throw()
{
}

const char* Error::what() throw()
{
    std::cerr << "[Error] : " << _msg <<  " | " << getType() << " ERROR TYPE" << std::endl;
    if (_errorLv == FATAL)
        exit(84);
    return _msg.c_str();
}

std::string Error::getType() const
{
    if (_errorLv == COMMON)
        return "COMMON";
    if (_errorLv == FATAL)
        return "FATAL";
    return "NONE";
}