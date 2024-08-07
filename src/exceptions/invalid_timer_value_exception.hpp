#ifndef INVALID_TIMER_VALUE_EXCEPTION_HPP
#define INVALID_TIMER_VALUE_EXCEPTION_HPP

#include "../headers.hpp"

class InvalidTimerValueException : public std::exception{
    public:
        std::string msg();
};

#endif