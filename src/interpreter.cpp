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

instructValues interpreter::decode(uint16_t instr){

    instructValues decodedInstr;

    decodedInstr.action = instr >> 12;
    
    decodedInstr.X = int((instr & 0x0F00) >> 8);
    decodedInstr.Y = int((instr & 0x00F0) >> 4);
    decodedInstr.N = instr & 0x000F;
    decodedInstr.NN = instr & 0x00FF;
    decodedInstr.NNN = instr & 0x0FFF;

    return decodedInstr;

}

void interpreter::execute(instructValues decodedInstr){
    
    switch(decodedInstr.action){

        case 0x00:
            display->clear();
            break;
        
        case 0x01:
            context->pc = decodedInstr.NNN;
            break;
        
        case 0x06:
            context->varRegisters[decodedInstr.X] = decodedInstr.NN;
            break;
        
        case 0x07:
            context->varRegisters[decodedInstr.X] += decodedInstr.NN;
            break;
        
        case 0x0A:
            context->index = decodedInstr.NNN;
            break;
        
        case 0x0D:
            int x = context->varRegisters[decodedInstr.X];
            int y = context->varRegisters[decodedInstr.Y];
            int h = int(decodedInstr.N);
            draw(x, y, h);
            break;

    }

}

void interpreter::draw(int x, int y, int h){

}

interpreter::~interpreter(){

    delete context;
    delete display;
    delete keypad;
    delete interpreterTimer;

}