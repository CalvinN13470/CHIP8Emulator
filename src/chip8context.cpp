#include "chip8context.hpp"

Chip8Context::Chip8Context(){

    memory.fill(0x00);
    varRegisters.fill(0x00);
    pc = 0x0000;
    index = 0x0000;

    delayTimer = new Chip8Timer(constants::DELAY_MAX_DELTA_TIME, constants::DELAY_CYCLE_LENGTH);
    soundTimer = new Chip8Timer(constants::DELAY_MAX_DELTA_TIME, constants::DELAY_CYCLE_LENGTH);

    for (int i = 0 ; i < chip8::font::FONT_DATA_SIZE ; ++i){
        memory[chip8::constants::FONT_DATA_ENTRY_INDEX + i] = chip8::font::data[i];
    }

}

Chip8Context::~Chip8Context() = default;