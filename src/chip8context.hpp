#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "headers.hpp"
#include "constants.hpp"
#include "chip8timer.hpp"

#include "chip8font.hpp"

using namespace chip8;

class Chip8Context{

    public:
        std::array<uint8_t, chip8::constants::MEM_SIZE> memory;
        std::stack<uint16_t> stack;

        std::array<uint8_t, constants::VAR_REGISTER_COUNT> varRegisters;

        uint16_t pc;
        uint16_t index;

        Chip8Timer* delayTimer;
        Chip8Timer* soundTimer;

        Chip8Context();
        ~Chip8Context();
    
};

#endif