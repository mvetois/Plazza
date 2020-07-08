/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "Cooks.hpp"
#include "Time.hpp"
#include "Kitchen.hpp"
#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include "Log.hpp"

using Plazza::Cooks;
using Plazza::Kitchen;
using Plazza::Pizza;
using Tools::ThreadPool;
using Tools::Mutex;
using Tools::ScopedLock;
using Tools::Input;
using Tools::Output;

Kitchen::Kitchen(std::string const &namedPathInput, std::string const &namedPathOutput, int cooksPerKitchen, int refreshTime) : _born(time.now()), _namedPathInput(namedPathOutput), _namedPathOutput(namedPathInput), _cooksPerKitchen(cooksPerKitchen), _refreshTime(refreshTime), _name(Kitchen::KitchenKeyGen()), _alive(true)
{
    _cookingTable.insert(std::make_pair(Pizza::Doe, 5));
    _cookingTable.insert(std::make_pair(Pizza::Tomato, 5));
    _cookingTable.insert(std::make_pair(Pizza::Gruyere, 5));
    _cookingTable.insert(std::make_pair(Pizza::Ham, 5));
    _cookingTable.insert(std::make_pair(Pizza::Mushrooms, 5));
    _cookingTable.insert(std::make_pair(Pizza::Steak, 5));
    _cookingTable.insert(std::make_pair(Pizza::EggPlant, 5));
    _cookingTable.insert(std::make_pair(Pizza::GoatCheese, 5));
    _cooks = new ThreadPool(cooksPerKitchen);
    _process = NULL;
    _receptionInput = NULL;
    _receptionOutput = NULL;
}

std::string Kitchen::KitchenKeyGen()
{
    std::vector<std::string> k;

    k.push_back("Pizza Pizza");
    k.push_back("Pizza & Pasta");
    k.push_back("Mozzarella");
    k.push_back("Mozzarepalla");
    k.push_back("Italiaaa");
    return (k[rand() % k.size()]);
}

Kitchen::~Kitchen()
{
    if (_process)
        delete _process;
    if (_receptionInput)
        delete _receptionInput;
    if (_receptionOutput)
        delete _receptionOutput;
}

void Kitchen::refreshCookingTable()
{
    while (_alive) {
        usleep(_refreshTime * 1000);
        if (_alive == false)
            break;
        Mutex mutex;
        mutex.lock();
        for (std::map<Pizza::Ingredients, int>::iterator it = _cookingTable.begin(); it != _cookingTable.end(); ++it)
			it->second += 1;
        std::cout << "Kitchen[" << _name << "]: just got some ingredients" << std::endl;
        std::time_t t = std::chrono::system_clock::to_time_t(time.now());
        std::string logLine = "Kitchen[" + _name + "]: got ingredients at " + std::ctime(&t);
        Log log(logLine.substr(0, logLine.size() - 1));

        mutex.unlock();
    }
}

void Kitchen::timeToClose()
{
    while (_alive) {
        if ((_born + std::chrono::seconds(DURATION) <= Plazza::time.now() && (_cooksPerKitchen == this->freeCooks()))) {
            std::cout << "Kitchen[" << _name << "] : was inactive too much time !" << std::endl;
            _alive = false;
            Log log("Kitchen[" + _name + "]: closed");
        }
    }
}

void Kitchen::cook(std::string &)
{
    Mutex mutex;
    std::string command;

    mutex.lock();
    _receptionOutput = new Output(_namedPathOutput);
    mutex.unlock();
    mutex.lock();
    _receptionInput = new Input(_namedPathInput);
    mutex.unlock();
    Thread cookingTable;
    cookingTable.startThread([](void *arg) -> void * {
        Kitchen *kitchen = static_cast<Kitchen *>(arg);
        kitchen->refreshCookingTable();
        return NULL;
    }, this);
    Thread kitchenAlive;
    kitchenAlive.startThread([](void *arg) -> void * {
        Kitchen *kitchen = static_cast<Kitchen *>(arg);
        kitchen->timeToClose();
        return NULL;
    }, this);
    while (true) {
        _receptionInput->read(command);
        this->handleCommand(command);
    }
}

size_t Kitchen::freeCooks() const
{
    return (_cooks->cooksAvailable());
}

void Kitchen::handleCommand(std::string &receptionCommand)
{
    Mutex mutex;
    ScopedLock locker(mutex);
    std::map<std::string, bool (Kitchen::*)(std::string &)> commands;
    std::string finalCommand = receptionCommand.substr(0, receptionCommand.find_first_of(" "));

    commands["cook:"] = &Kitchen::sendCommand;
    commands["canCook"] = &Kitchen::sendCanCook;
    commands["freeCooks"] = &Kitchen::sendFreeCooks;
    commands["kill"] = &Kitchen::handleDeath;
    commands["status"] = &Kitchen::printStatus;

    if (_alive == false)
        finalCommand = "kill";
    if (!finalCommand.empty() && commands.find(finalCommand) != commands.end()) {
        if ((this->*(commands.find(finalCommand)->second))(receptionCommand) == true)
            _born = time.now();
    }
}

bool Kitchen::sendCommand(std::string &pizzaCommand)
{
    Mutex mutex;
    ScopedLock locker(mutex);

    pizzaCommand = pizzaCommand.substr(6);
    Pizza *toCook = Pizza::unpack(pizzaCommand);
    std::vector<Pizza::Ingredients> ingredients = toCook->getIngredient();
    for (std::vector<Pizza::Ingredients>::const_iterator ingredient = ingredients.begin(); ingredient != ingredients.end(); ++ingredient) {
		_cookingTable.find(*ingredient)->second--;
	}
    std::cout << "Kitchen[" << _name << "]: received an order." << std::endl;
    Log log("Kitchen[" + _name + "]: received an order");
    _cooks->addTask(new Cooks(toCook));
    _cooks->executeTasks();
    return true;
}

bool Kitchen::sendCanCook(std::string &packedPizza)
{
    Mutex mutex;
    ScopedLock locker(mutex);
    Pizza *unpacked = Pizza::unpack(packedPizza.substr(8));
    std::vector<Pizza::Ingredients> ingredients = unpacked->getIngredient();
    std::map<Pizza::Ingredients, int> temp = _cookingTable;
    bool canCook = true;
    for (std::vector<Pizza::Ingredients>::const_iterator ingredient = ingredients.begin(); ingredient != ingredients.end() && canCook; ++ingredient) {
		temp.find(*ingredient)->second--;
		if (temp.find(*ingredient)->second < 0)
			canCook = false;
	}
    if (canCook == true)
        _receptionOutput->write("true");
    else
        _receptionOutput->write("false");
    return false;
}

bool Kitchen::sendFreeCooks(std::string &)
{
    std::string freeCooks = std::to_string(this->freeCooks());
    _receptionOutput->write(freeCooks);
    return false;
}

bool Kitchen::handleDeath(std::string &)
{
    std::cout << "Kitchen[" << _name << "]: is closing ! Bye bye :D" << std::endl;
    Log log("Kitchen[" + _name + "]: closed");
    _receptionOutput->write("kitchenClosing");
    exit(EXIT_SUCCESS);
    return false;
}

bool Kitchen::printStatus(std::string &)
{
    std::cout << "\t[Kitchen]: " << _name << " - Cooks : " << std::to_string(freeCooks()) << "/" << _cooksPerKitchen << " cooks available\n";
    Log log("\t[Kitchen]: " + _name + " - Cooks : " + std::to_string(freeCooks()) + "/" + std::to_string(_cooksPerKitchen) + " cooks available");
    for (std::map<Pizza::Ingredients, int>::const_iterator ingredient = _cookingTable.begin(); ingredient != _cookingTable.end(); ++ingredient) {
		std::cout << "\tIngredient " << std::to_string(ingredient->first) << " : " << std::to_string(ingredient->second) << std::endl;
        log.write("\tIngredient " + std::to_string(ingredient->first) + " : " + std::to_string(ingredient->second));
	}
    log.write("\n");
    std::cout << std::endl;
    return false;
}