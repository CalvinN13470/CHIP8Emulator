#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "headers.hpp"
#include "chip8display.hpp"
#include "exceptions/null_display_exception.hpp"

class Chip8Keypad{
    private:
        SDL_Event event;
    public:
        //requires chip8Display instance
        Chip8Keypad(Chip8Display* display);

        //maps to hold hex values corresponding to key inputs
        std::map<uint8_t, Sint32> hexToKey;
        std::map<Sint32, uint8_t> keyToHex;

        //returns SDLK value
        uint8_t getKeyPress();
        ~Chip8Keypad();
};

#endif