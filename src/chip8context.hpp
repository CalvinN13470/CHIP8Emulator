#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "headers.hpp"
#include "constants.hpp"
#include "structures.hpp"

#include "chip8font.hpp"

class chip8Context{

    public:
        std::array<std::uint8_t, chip8::constants::memSize> memory;
        std::stack<std::uint16_t> stack;
        chip8::registers registers;

        chip8Context();
        ~chip8Context();
    
};

#endif