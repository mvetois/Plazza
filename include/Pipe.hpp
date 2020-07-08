/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Pipe
*/

#ifndef PIPE_HPP_
#define PIPE_HPP_

#include <stdio.h>
#include <fstream>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include "Error.hpp"

#define SIZE_READ 100

namespace Tools {

    class Pipe {
        public:
            Pipe(std::string const &path);
            virtual ~Pipe();
        protected:
            std::string _path;
    };

    class Input : public Pipe {
        public:
            Input(std::string const &path);
            virtual ~Input();

            Input &operator>>(std::string &text);
            void read(std::string &text);
        private:
            std::ifstream _file;
    };

    class Output : public Pipe {
        public:
            Output(std::string const &path);
            virtual ~Output();

            Output &operator<<(std::string const &text);
            void write(std::string const &text);
        private:
            std::ofstream _file;
    };
};

#endif /* !PIPE_HPP_ */
