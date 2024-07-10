#include "chip8context.hpp"

chip8Context::chip8Context(){

    memory.fill(0x00);

    for (int i = 0 ; i < chip8::font::fontDataSize ; i++){
        memory[chip8::constants::fontDataEntryIndex + i] = chip8::font::data[i];
    }

}

chip8Context::~chip8Context() = default;