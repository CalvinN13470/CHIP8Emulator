#ifndef CONST_HPP
#define CONST_HPP

#include "headers.hpp"

namespace chip8::constants{

    const std::size_t memSize = 4096;
    const std::size_t stackAddressSize = 16;

    const std::size_t indexRegisterSize = 16;
    const std::size_t varRegisterSize = 8;
    const std::size_t varRegisterCount = 16;

    const std::size_t delayTimerSize = 8;
    const std::size_t soundTimerSize = 8;

    //Location in memory to add font data
    const std::size_t fontDataEntryIndex = 80;

}

#endif