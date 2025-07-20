#include "chip8timer.hpp"

chip8Timer::chip8Timer(size_t delta, size_t cycle){

    timer = 0;
    deltaTime = 0;
    accumulator = 0;
    
    maxDelta = delta;
    cycleLength = cycle;

    lastTime = steady_clock::now();
    currentTime = steady_clock::now();

}

void chip8Timer::step(){
    
    currentTime = steady_clock::now();
    deltaTime = duration_cast<nanoseconds>(currentTime - lastTime).count();

    //prevents large amounts of steps when program pauses
    if (deltaTime > maxDelta)
        deltaTime = maxDelta;
    
    lastTime = currentTime;
    accumulator += deltaTime;

    while (accumulator > cycleLength){\
        if (timer > 0)
            timer -= 1;
        accumulator -= cycleLength;
    }
}

void chip8Timer::setTime(const uint8_t newTime){
    timer = newTime;
}

uint8_t chip8Timer::getTime(){
    step();
    return timer;
}

bool chip8Timer::isZero(){
    return (timer == 0);
}

chip8Timer::~chip8Timer() = default;