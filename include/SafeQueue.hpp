/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** SafeQueue
*/

#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

namespace Tools {

    template <class allType>
    class ISafeQueue {
        public:
            virtual ~ISafeQueue () = default;
            virtual void push(allType value) = 0;
            virtual bool tryPop(allType &value) = 0;
    };

    template <class allType>
    class SafeQueue {
        public:
            SafeQueue();
            ~SafeQueue();
            push(allType value);
            tryPop(allType &value);
        protected:
        private:
            allType value;
    };

};

#endif /* !SAFEQUEUE_HPP_ */
