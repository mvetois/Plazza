/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <chrono>
#include <map>
#include <vector>
#include "Cooks.hpp"
#include "ICooking.hpp"
#include "ThreadPool.hpp"
#include "Pizza.hpp"
#include "Process.hpp"
#include "Pipe.hpp"

#define DURATION 5

namespace Plazza {

    class Kitchen : public ICooking {
        public:
            Kitchen(std::string const &namedPathInput, std::string const &namedPathOutput, int cooksPerKitchen, int refreshTime);
            ~Kitchen();

            void refreshCookingTable();
            void timeToClose();
            size_t freeCooks() const;

            virtual void cook(std::string &name);
            void handleCommand(std::string &receptionCommand);
            bool sendCommand(std::string &pizzaCommand);
            bool sendFreeCooks(std::string &freeCooks);
            bool sendCanCook(std::string &packedPizza);
            bool handleDeath(std::string &areYouAlive);
            bool printStatus(std::string &giveMeStatus);
            static std::string KitchenKeyGen();
        private:
            std::chrono::system_clock::time_point _born; // 5 seconds == 5 seconds ? yes : yes;
            int _cooksPerKitchen;
            int _refreshTime;
            std::string _namedPathInput;
            std::string _namedPathOutput;
            Tools::Input *_receptionInput;
            Tools::Output *_receptionOutput;
            Tools::Process *_process;
            Tools::ThreadPool *_cooks;
            std::queue<Pizza *> _orders;
            std::map<Pizza::Ingredients, int> _cookingTable; // ingredients + count
            std::string _name;
            bool _alive;
    };
}
#endif /* !KITCHEN_HPP_ */
