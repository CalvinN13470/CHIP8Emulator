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

int chip8Timer::step(){
    
    bool step = false;
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
        step = true;
    }

    return step;

}

bool chip8Timer::addTime(const uint16_t addedTime){
    if ((uint16_t)timer + addedTime > 0x00FF){
        throw InvalidTimerValueException();
        return false;
    }

    timer += addedTime;
    return true;
}

uint8_t chip8Timer::getTimeHex(){
    return timer;
}

int chip8Timer::getTimeInt(){
    return (int) timer;
}

bool chip8Timer::isZero(){
    return (timer == 0);
}

chip8Timer::~chip8Timer() = default;