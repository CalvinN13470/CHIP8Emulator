#ifndef STRUCT_HPP
#define STRUCT_HPP

#include "headers.hpp"
#include "constants.hpp"

namespace chip8{

    struct registers{

        std::array<uint8_t, constants::varRegisterCount> varRegister;

        uint16_t pc;
        uint16_t index;

        uint8_t delayTimer;
        uint8_t soundTimer;

    };

};

#endif