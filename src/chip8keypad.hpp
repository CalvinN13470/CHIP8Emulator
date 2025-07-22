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

        //maps to hold hex values corresponding to key inputs
        std::map<uint8_t, Sint32> hexToKey;
        std::map<Sint32, uint8_t> keyToHex;

        //returns SDLK value
        Sint32 getKeyPress();
        ~chip8Keypad();
};

#endif