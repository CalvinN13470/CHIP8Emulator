#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "constants.hpp"
#include "headers.hpp"

using namespace chip8::constants;

class chip8Display{

    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

    public:
        chip8Display();
        void render(std::array<bool, EMULATOR_DISPLAY_WIDTH * EMUlATOR_DISPLAY_HEIGHT> screenBuffer);
        ~chip8Display();
};

#endif