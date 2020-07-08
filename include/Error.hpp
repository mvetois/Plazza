/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <iostream>

namespace Plazza {
    
    class Error : virtual public std::exception {
        public :
            typedef enum ErrorCode_e {
                KITCHENFAILED,
                MAINARGSNB,
                MAINARGSTYPE,
                MUTEXFAIL,
                MUTEXLOCK,
                MUTEXUNLOCK,
                NO,
                PIPEFAILURE,
                PROCESSCREATE,
                PROCESSWAIT,
                UNDEFINEDPIZZA,
                UNDEFINEDCOMMAND,
                THREADSTART,
                THREADWAIT,
                THREADRUNTASK,
                THREADSTOP,
                WRONGFORMAT
            } Code;
            
            typedef enum ErrorType_e {
                COMMON,
                FATAL,
                NONE
            } Type;

            Error(Code error, std::string const& phrase, Type niveau) throw();
            ~Error() throw();
            const char* what() throw();
            std::string getType() const;
        private:
            Code _code;         //Numéro de l'erreur
            std::string _msg;   //Description de l'erreur
            Type _errorLv;      //Niveau de l'erreur
    };
}

#endif /* !ERROR_HPP_ */
