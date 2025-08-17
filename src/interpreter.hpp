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

class Interpreter{

    private:
        Chip8Context* context = nullptr;
        Chip8Display* display = nullptr;
        Chip8Timer* interpreterTimer = nullptr;
        Chip8Keypad* keypad = nullptr;
        int superchip;
        uint16_t fetch();
        instructValues decode(uint16_t instr);
        void execute(instructValues decodedInstr);
        void draw(int x, int y, int h);
    
    public:
        Interpreter();
        Interpreter(char const* filename, bool enableSuperchip);
        int run();
        ~Interpreter();
};

#endif