#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "constants.hpp"
#include "structures.hpp"
#include "chip8context.hpp"
#include "chip8display.hpp"
#include "chip8timer.hpp"
#include "chip8keypad.hpp"

using namespace std;
using namespace chip8;

class interpreter{

    private:
        chip8Context* context = nullptr;
        chip8Display* display = nullptr;
        chip8Timer* interpreterTimer = nullptr;
        chip8Keypad* keypad = nullptr;
        uint16_t fetch();
        instructValues decode(uint16_t instr);
        void execute(instructValues decodedInstr);
        void draw(int x, int y, int h);
    
    public:
        interpreter();
        interpreter(char const* filename);
        int run();
        ~interpreter();
};

#endif