#include "chip8timer.hpp"

Chip8Timer::Chip8Timer(size_t delta, size_t cycle){

    timer = 0;
    deltaTime = 0;
    accumulator = 0;
    
    maxDelta = delta;
    cycleLength = cycle;

    lastTime = steady_clock::now();
    currentTime = steady_clock::now();

}

void Chip8Timer::step(){
    
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

void Chip8Timer::addTime(const uint8_t addedTime){
    timer += addedTime;
}

void Chip8Timer::setTime(const uint8_t newTime){
    timer = newTime;
}

uint8_t Chip8Timer::getTime(){
    step();
    return timer;
}

bool Chip8Timer::isZero(){
    return (timer == 0);
}

Chip8Timer::~Chip8Timer() = default;