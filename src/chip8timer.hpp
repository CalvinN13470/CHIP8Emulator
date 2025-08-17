#ifndef TIMER_HPP
#define TIMER_HPP

#include "headers.hpp"
#include "constants.hpp"
#include "exceptions/invalid_timer_value_exception.hpp"

using namespace std::chrono;
using namespace chip8::constants;

class Chip8Timer{
    private:
        uint8_t timer;
        uint64_t deltaTime;
        uint64_t accumulator;
        size_t maxDelta;
        size_t cycleLength;

        steady_clock::time_point lastTime;
        steady_clock::time_point currentTime;

        void step();
        
    public:
        Chip8Timer(size_t delta, size_t cycle);
        void addTime(const uint8_t addedTime);
        void setTime(const uint8_t newTime);
        uint8_t getTime();
        bool isZero();
        ~Chip8Timer();
};

#endif