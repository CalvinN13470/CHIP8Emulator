#include "chip8display.hpp"

chip8Display::chip8Display(){

    window = SDL_CreateWindow("Calvin's CHIP8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_DISPLAY_WIDTH, WINDOW_DISPLAY_HEIGHT, 0);
    if (window == nullptr)
        std::cerr << "Unable to create Window. SDL Error: " << SDL_GetError() << std::endl;
    
    else{
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer == nullptr)
            std::cerr << "Unable to create renderer. SDL Error " << SDL_GetError() << std::endl;
    }
    
}

void chip8Display::render(const std::array<bool, EMULATOR_DISPLAY_WIDTH * EMUlATOR_DISPLAY_HEIGHT> screenBuffer){

    //clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0 ; i < EMULATOR_DISPLAY_WIDTH * EMUlATOR_DISPLAY_HEIGHT ; i++){

        if (screenBuffer[i] != false){

            int x = (i % EMULATOR_DISPLAY_WIDTH) * PIXEL_SIZE;
            int y = (i / EMUlATOR_DISPLAY_HEIGHT) * PIXEL_SIZE;
            SDL_Rect pixelRect = {x, y, PIXEL_SIZE, PIXEL_SIZE};
            SDL_RenderFillRect(renderer, &pixelRect);

        }

    }

    SDL_RenderPresent(renderer);

}

chip8Display::~chip8Display(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}