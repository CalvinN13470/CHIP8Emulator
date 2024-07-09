#include "chip8Timer.hpp"

chip8Timer::chip8Timer(){

    timer = 0;
    deltaTime = 0;
    accumulator = 0;
    
    lastTime = steady_clock::now();
    currentTime = steady_clock::now();


}

void chip8Timer::step(){

    currentTime = steady_clock::now();

    deltaTime = duration_cast<nanoseconds>(currentTime - lastTime).count();

    //prevents large amounts of steps when program pauses
    if (deltaTime > maxDeltaTime)
        deltaTime = maxDeltaTime;
    
    lastTime = currentTime;
    accumulator += deltaTime;

    while (accumulator > cycleLength){\
        if (timer > 0)
            timer -= 1;
        accumulator -= cycleLength;
    }

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

chip8Timer::~chip8Timer(){

}