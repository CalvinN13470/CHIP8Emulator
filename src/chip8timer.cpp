#include "chip8timer.hpp"

chip8Timer::chip8Timer(size_t max, size_t length){

    timer = 0;
    deltaTime = 0;
    accumulator = 0;
    
    maxDelta = max;
    cycleLength = length;

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

void chip8Timer::addTime(const uint8_t addedTime){
    timer += addedTime;
}

uint8_t chip8Timer::getTime(){
    return timer;
}

bool chip8Timer::isZero(){
    return (timer == 0);
}

chip8Timer::~chip8Timer() = default;