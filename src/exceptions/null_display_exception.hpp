#ifndef NULL_DISPLAY_EXCEPTION_HPP
#define NULL_DISPLAY_EXCEPTION_HPP

#include "../headers.hpp"

class NullDisplayException : public std::exception{
    public:
        std::string msg();
};

#endif