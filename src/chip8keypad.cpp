#include "chip8keypad.hpp"

chip8Keypad::chip8Keypad(chip8Display* display){

    if (!display)
        throw NullDisplayException();

    /*
    Keys:
    1 2 3 4
    q w e r
    a s d f
    z x c v
     */
    keyMap = {
      {0x0, SDLK_1},
      {0x1, SDLK_2},
      {0x2, SDLK_3},
      {0x3, SDLK_4},
      {0x4, SDLK_q},
      {0x5, SDLK_w},
      {0x6, SDLK_e},
      {0x7, SDLK_r},
      {0x8, SDLK_a},
      {0x9, SDLK_s},
      {0xA, SDLK_d},
      {0xB, SDLK_f},
      {0xC, SDLK_z},
      {0xD, SDLK_x},
      {0xE, SDLK_c},
      {0xF, SDLK_v},
    };
    
}

Sint32 chip8Keypad::getKeyPress(){
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_KEYDOWN)
            return event.key.keysym.sym;
        
    }
    return false;
}

chip8Keypad::~chip8Keypad() = default;