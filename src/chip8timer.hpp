#ifndef TIMER_HPP
#define TIMER_HPP

#include "headers.hpp"
#include "constants.hpp"

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
        //disableTimerCount removes the neccessity to add time
        chip8Timer(size_t max, size_t length);
        int step();
        void addTime(const uint8_t addedTime);
        uint8_t getTime();
        bool isZero();
        ~chip8Timer();
};

#endif