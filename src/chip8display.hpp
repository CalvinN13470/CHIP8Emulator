#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "constants.hpp"
#include "headers.hpp"

using namespace chip8::constants;

class Chip8Display{

    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        std::array<bool, EMULATOR_DISPLAY_WIDTH * EMUlATOR_DISPLAY_HEIGHT> screenBuffer;

    public:
        Chip8Display();
        void render();
        void clear();
        void setPixel(int x, int y, bool state);
        bool getPixel(int x, int y);
        ~Chip8Display();
};

#endif