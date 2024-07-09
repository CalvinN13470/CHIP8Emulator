#ifndef STRUCT_HPP
#define STRUCT_HPP

#include "headers.hpp"
#include "constants.hpp"
#include "chip8Timer.hpp"

namespace chip8{

    struct registers{

        std::array<uint8_t, constants::varRegisterCount> varRegister;

        uint16_t pc;
        uint16_t index;

        chip8Timer delayTimer;
        chip8Timer soundTimer;

    };

};

#endif