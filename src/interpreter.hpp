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
        chip8Context* context;
        chip8Display* display;
        chip8Timer* interpreterTimer;
        chip8Keypad* keypad;
        uint16_t fetch();
        instructValues decode(uint16_t instr);
        void execute(instructValues decodedInstr);
    
    public:
        interpreter();
        int start();
        ~interpreter();
};

#endif