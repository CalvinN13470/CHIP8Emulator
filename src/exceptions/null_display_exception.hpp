#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include "../headers.hpp"

class NullDisplayException : public std::exception{
    public:
        std::string msg();
};

#endif