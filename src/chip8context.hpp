#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "headers.hpp"
#include "constants.hpp"
#include "chip8timer.hpp"

#include "chip8font.hpp"

using namespace chip8;

class chip8Context{

    public:
        std::array<std::uint8_t, chip8::constants::MEM_SIZE> memory;
        std::stack<std::uint16_t> stack;

        std::array<uint8_t, constants::VAR_REGISTER_COUNT> varRegisters;

        uint16_t pc;
        uint16_t index;

        chip8Timer* delayTimer;
        chip8Timer* soundTimer;

        chip8Context();
        ~chip8Context();
    
};

#endif