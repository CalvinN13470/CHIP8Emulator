#include "chip8Context.hpp"

chip8Context::chip8Context(){
    for (int i = 0 ; i < chip8::font::fontDataSize ; i++){
        memory[chip8::constants::fontDataEntryIndex + i] = chip8::font::data[i];
    }
}

chip8Context::~chip8Context(){

}