/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** ICooking
*/

#ifndef ICOOKING_HPP_
#define ICOOKING_HPP_

class ICooking
{
    public:
        virtual ~ICooking() = default;
        virtual void cook(std::string &name) = 0;
};

#endif /* !ICOOKING_HPP_ */
