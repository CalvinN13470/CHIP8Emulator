#ifndef CONST_HPP
#define CONST_HPP

#include "headers.hpp"

namespace chip8::constants{

    const std::size_t PIXEL_SIZE = 10;
    const std::size_t EMULATOR_DISPLAY_WIDTH = 64;
    const std::size_t EMUlATOR_DISPLAY_HEIGHT = 32;
    const std::size_t WINDOW_DISPLAY_WIDTH = PIXEL_SIZE * EMULATOR_DISPLAY_WIDTH;
    const std::size_t WINDOW_DISPLAY_HEIGHT = PIXEL_SIZE * EMUlATOR_DISPLAY_HEIGHT;

    const std::size_t MEM_SIZE = 4096;
    const std::size_t STACK_ADDRESS_SIZE = 16;

    const std::size_t INDEX_REGISTER_SIZE = 16;
    const std::size_t VAR_REGISTER_SIZE = 8;
    const std::size_t VAR_REGISTER_COUNT = 16;

    const std::size_t DELAY_TIMER_SIZE = 8;
    const std::size_t SOUND_TIMER_SIZE = 8;
    
    // 1/60th of a second in nanoseconds
    const std::size_t DELAY_CYCLE_LENGTH = 16666666;
    const std::size_t DELAY_MAX_DELTA_TIME = 50000000;

    // 1/700th of a second in nanoseconds
    const std::size_t PROC_CYCLE_LENGTH = 1430000;
    const std::size_t PROC_MAX_DELTA_TIME = 2000000;

    //Location in memory to add font data
    const std::size_t FONT_DATA_ENTRY_INDEX = 80;

}

#endif