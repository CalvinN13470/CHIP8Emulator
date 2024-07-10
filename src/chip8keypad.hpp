#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "headers.hpp"
#include "chip8display.hpp"
#include "exceptions/null_display_exception.hpp"

class chip8Keypad{
    private:
        SDL_Event event;
    public:
        //requires chip8Display instance
        chip8Keypad(chip8Display* display);

        //returns SDLK value
        Sint32 getKeyPress();
        ~chip8Keypad();
};

#endif