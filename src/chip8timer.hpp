#ifndef TIMER_HPP
#define TIMER_HPP

#include "headers.hpp"
#include "constants.hpp"
#include "exceptions/invalid_timer_value_exception.hpp"

using namespace std::chrono;
using namespace chip8::constants;

class chip8Timer{
    private:
        uint8_t timer;
        uint64_t deltaTime;
        uint64_t accumulator;
        size_t maxDelta;
        size_t cycleLength;

        steady_clock::time_point lastTime;
        steady_clock::time_point currentTime;
        
    public:
        chip8Timer(size_t delta, size_t cycle);
        int step();
        bool addTime(const uint16_t addedTime);
        uint8_t getTimeHex();
        int getTimeInt();
        bool isZero();
        ~chip8Timer();
};

#endif