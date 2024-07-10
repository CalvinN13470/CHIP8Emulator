#include "chip8keypad.hpp"

chip8Keypad::chip8Keypad(chip8Display* display){

    if (!display)
        throw NullDisplayException();
    
}

Sint32 chip8Keypad::getKeyPress(){
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_KEYDOWN)
            return event.key.keysym.sym;
        
    }
    return false;
}

chip8Keypad::~chip8Keypad() = default;