#include "interpreter.hpp"

interpreter::interpreter(){

    context = new chip8Context();
    display = new chip8Display();
    keypad = new chip8Keypad(display);
    interpreterTimer = new chip8Timer(constants::PROC_MAX_DELTA_TIME, constants::PROC_CYCLE_LENGTH);

}

uint16_t interpreter::fetch(){

    uint8_t instr1 = context->memory[int(context->pc)];
    uint8_t instr2 = context->memory[int(context->pc) + 1];
    context->pc = context->pc + 0x0002;

    uint16_t instr = ((uint16_t)instr1 << 8) | instr2;

    return instr;

}

instructValues decode(uint16_t instr){

    instructValues decodedInstr;

    decodedInstr.action = int((uint8_t)(instr >> 12));
    
    decodedInstr.X = int((instr & 0x0F00) >> 8);
    decodedInstr.Y = int((instr & 0x00F0) >> 4);
    decodedInstr.N = int(instr & 0x000F);
    decodedInstr.NN = int(instr & 0x00FF);
    decodedInstr.NNN = int(instr & 0x0FFF);

    return decodedInstr;

}

void execute(instructValues decodedInstr){

}

interpreter::~interpreter(){

    delete context;
    delete display;
    delete keypad;
    delete interpreterTimer;

}