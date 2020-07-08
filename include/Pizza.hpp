/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <vector>
#include <string>

namespace Plazza {

    class Pizza {
        public:
            enum PizzaType {
                Regina = 1,
                Margarita = 2,
                Americana = 4,
                Fantasia = 8
            };
            enum PizzaSize {
                S = 1,
                M = 2,
                L = 4,
                XL = 8,
                XXL = 16
            };
            enum Ingredients {
                Doe,
                Tomato,
                Gruyere,
                Ham,
                Mushrooms,
                Steak,
                EggPlant,
                GoatCheese,
                ChiefLove
            };
        
        public:
            Pizza(int pizzaType, PizzaSize size, double cookingMultiplier);
            virtual ~Pizza();
            static std::string pack(Pizza toPack);
            static Pizza *unpack(std::string toUnpack); 
            virtual double getCookingTime() const;
            virtual std::string getName() const;
            virtual std::string getSize() const;
            virtual int getType() const;
            virtual std::vector<Pizza::Ingredients> getIngredient() const;
        protected:
            PizzaSize _size;
            int _pizzaType;
            std::string _name;
            std::vector<Pizza::Ingredients> _ingredient;
            double _cookingTime;

    };

    class Regina : public Pizza {
        public:
            static Pizza *newRegina(Pizza::PizzaSize, double dookingMultiplier);
            ~Regina();
        private:
            Regina(PizzaSize size, double cookingMultiplier);
    };

    class Margarita : public Pizza {
        public:
            static Pizza *newMargarita(Pizza::PizzaSize, double dookingMultiplier);
            ~Margarita();
        private:
            Margarita(PizzaSize size, double cookingMultiplier);
    };

    class Americana : public Pizza {
        public:
            static Pizza *newAmericana(Pizza::PizzaSize, double dookingMultiplier);
            ~Americana();
        private:
            Americana(PizzaSize size, double cookingMultiplier);
    };

    class Fantasia : public Pizza {
        public:
            static Pizza *newFantasia(Pizza::PizzaSize, double dookingMultiplier);
            ~Fantasia();
        private:
            Fantasia(PizzaSize size, double cookingMultiplier);
    };
};
#endif /* !PIZZA_HPP_ */
