#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "headers.hpp"
#include "constants.hpp"
#include "structures.hpp"

#include "chip8Font.hpp"

class chip8Context{

    public:
        static std::array<std::uint8_t, chip8::constants::memSize> memory;
        static std::stack<std::uint16_t> stack;
        static chip8::registers registers;

    chip8Context();
    ~chip8Context();
    
};

#endif