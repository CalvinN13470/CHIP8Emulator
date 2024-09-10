#ifndef STRUCT_HPP
#define STRUCT_HPP

#include "headers.hpp"

namespace chip8{

    struct instructValues{

        uint8_t action = 0x00;
        int X = 0;
        int Y = 0;
        uint8_t N = 0x00;
        uint8_t NN = 0x00;
        uint16_t NNN = 0x0000;

    };

};

#endif