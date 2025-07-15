#include "interpreter.hpp"

interpreter::interpreter(){

    context = new chip8Context();
    display = new chip8Display();
    keypad = new chip8Keypad(display);
    interpreterTimer = new chip8Timer(constants::PROC_MAX_DELTA_TIME, constants::PROC_CYCLE_LENGTH);

}

interpreter::interpreter(char const* filename){


    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open()){
        std::cerr << "Error: Could not open ROM file " << filename << std::endl;
    }
    else{
        context = new chip8Context();
        display = new chip8Display();
        keypad = new chip8Keypad(display);
        interpreterTimer = new chip8Timer(constants::PROC_MAX_DELTA_TIME, constants::PROC_CYCLE_LENGTH);

        long size = file.tellg();
        char* buffer = new char[size];

        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        for (long i = 0; i < size ; ++i){
            context->memory[ROM_DATA_ENTRY_INDEX + i] = buffer[i];
        }

        context->pc = ROM_DATA_ENTRY_INDEX;
    }

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
            context->varRegisters[0x0F] = 0x00;
            draw(x, y, h);
            break;

    }

}

void interpreter::draw(int x, int y, int h){
    x = x % constants::EMULATOR_DISPLAY_WIDTH;
    y = y % constants::EMUlATOR_DISPLAY_HEIGHT;
    int pX = x;
    int pY = y;

    for (int i = 0 ; i < h ; i++){

        if (pY > constants::EMUlATOR_DISPLAY_HEIGHT)
            break;

        uint8_t byteData = context->memory[context->index + i];
        pX = x;

        for (int j = 7 ; j >=0 ; j--){

            if (pX > constants::EMULATOR_DISPLAY_WIDTH)
                break;

            bool bit = (byteData >> j) & 1;

            if (bit){
                if (display->getPixel(pX, pY)){
                    display->setPixel(pX, pY, false);
                    context->varRegisters[0x0F] = 0x01;
                }
                else{
                    display->setPixel(pX, pY, true);
                }
            }
            pX += 1;
        }
        pY += 1;
    }

    display->render();

}

int interpreter::run(){

    if (context == nullptr){
        std::cerr << "Interpreter not properly initialized" << std::endl;
        return -1;
    }
    else{
        while(true){
            uint16_t curInstruction = fetch();
            instructValues values = decode(curInstruction);
            execute(values);
        }
    }
}

interpreter::~interpreter(){

    delete context;
    delete display;
    delete keypad;
    delete interpreterTimer;

}