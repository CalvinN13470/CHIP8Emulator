#include "interpreter.hpp"

interpreter::interpreter(){

    context = new chip8Context();
    display = new chip8Display();
    keypad = new chip8Keypad(display);

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
    context->pc = context->pc + 0x2;

    uint16_t instr = ((uint16_t)instr1 << 8) | instr2;

    return instr;

}

instructValues interpreter::decode(uint16_t instr){

    instructValues decodedInstr;

    decodedInstr.instr = instr;
    decodedInstr.action = instr >> 12;
    decodedInstr.X = int((instr & 0x0F00) >> 8);
    decodedInstr.Y = int((instr & 0x00F0) >> 4);
    decodedInstr.N = instr & 0x000F;
    decodedInstr.NN = instr & 0x00FF;
    decodedInstr.NNN = instr & 0x0FFF;

    return decodedInstr;

}

void interpreter::execute(instructValues decodedInstr){
    int SUPERCHIP = 1;

    switch(decodedInstr.action){

        case 0x00:
            {
                //subroutine return
                if (decodedInstr.NN == 0xE0){    
                    context->pc = context->stack.top();
                    context->stack.pop();
                }
                //clear screen
                else{
                    display->clear();
                }
            }
            break;
        
        //jump
        case 0x01:
            {
                context->pc = decodedInstr.NNN;
            }
            break;

        //skip conditional
        case 0x03:
            {
                if (context->varRegisters[decodedInstr.X] == decodedInstr.NN)
                    context->pc += 0x2;
            }
            break;

        //skip conditional
        case 0x04:
            {
                if (context->varRegisters[decodedInstr.X] != decodedInstr.NN)
                    context->pc += 0x2;
            }
            break;

        //skip conditional
        case 0x05:
            {
                if (context->varRegisters[decodedInstr.X] == context->varRegisters[decodedInstr.Y])
                    context->pc += 0x2;    
            }
            break;

        //set VX = NN
        case 0x06:
            {
                context->varRegisters[decodedInstr.X] = decodedInstr.NN;
            }
            break;

        //add NN to VX
        case 0x07:
            {
                context->varRegisters[decodedInstr.X] += decodedInstr.NN;
            }
            break;

        
        case 0x08:
            {
                switch(decodedInstr.N){

                    //set VX to VY
                    case 0x00:
                    {
                        context->varRegisters[decodedInstr.X] = context->varRegisters[decodedInstr.Y];
                    }   
                    break;

                    //binary OR
                    case 0x01:
                    {    
                        context->varRegisters[decodedInstr.X] = context->varRegisters[decodedInstr.X] | context->varRegisters[decodedInstr.Y];
                    }    
                    break;

                    //binary AND
                    case 0x02:
                    {
                        context->varRegisters[decodedInstr.X] = context->varRegisters[decodedInstr.X] & context->varRegisters[decodedInstr.Y];
                    }   
                    break;

                    //binary XOR
                    case 0x03:
                    {
                        context->varRegisters[decodedInstr.X] = context->varRegisters[decodedInstr.X] ^ context->varRegisters[decodedInstr.Y];
                    }
                    break;

                    //add VY to VX
                    case 0x04:
                    {
                        uint16_t sum = context->varRegisters[decodedInstr.X] + context->varRegisters[decodedInstr.Y];

                        if (sum > 255)
                            context->varRegisters[0xF] = 1;
                        else
                            context->varRegisters[0xF] = 0;
                        
                        context->varRegisters[decodedInstr.X] = 0xFF & sum;
                    }
                    break;

                    //subtract VX by VY
                    case 0x05:
                    {
                        if (context->varRegisters[decodedInstr.X] > context->varRegisters[decodedInstr.Y])
                            context->varRegisters[0xF] = 1;
                        else
                            context->varRegisters[0xF] = 0;

                        context->varRegisters[decodedInstr.X] -= context->varRegisters[decodedInstr.Y];
                    }
                    break;

                    //shift right
                    case 0x06:
                    {
                        if (SUPERCHIP)
                            context->varRegisters[decodedInstr.X] = context->varRegisters[decodedInstr.Y];
                        
                        context->varRegisters[0xF] = context->varRegisters[decodedInstr.X] & 0x1;
                        context->varRegisters[decodedInstr.X] = context->varRegisters[decodedInstr.X] >> 1;
                    }
                    break;

                    //subtract VY by VX
                    case 0x07:
                    {
                        if (context->varRegisters[decodedInstr.Y] > context->varRegisters[decodedInstr.X])
                            context->varRegisters[0xF] = 1;
                        else
                            context->varRegisters[0xF] = 0;

                        context->varRegisters[decodedInstr.X] = context->varRegisters[decodedInstr.Y] - context->varRegisters[decodedInstr.X];
                    }
                    break;

                    //shift left
                    case 0x0E:
                    {
                        if (SUPERCHIP)
                            context->varRegisters[decodedInstr.X] = context->varRegisters[decodedInstr.Y];
                        
                        context->varRegisters[0xF] = context->varRegisters[decodedInstr.X] >> 7;
                        context->varRegisters[decodedInstr.X] = context->varRegisters[decodedInstr.X] << 1;  
                    }
                    break;  

                }
            }
            break;

        //skip conditional
        case 0x09:
        {
            if (context->varRegisters[decodedInstr.X] != context->varRegisters[decodedInstr.Y]){
                context->pc = context->pc + 0x2;
            }
        }
        break;

        //set index
        case 0x0A:
        {
            context->index = decodedInstr.NNN;
        }
        break;
        
        //jump with offset
        case 0x0B:
        {
            uint16_t dest = decodedInstr.NNN;
            if (SUPERCHIP)
                dest += context->varRegisters[decodedInstr.X];
            else
                dest += context->varRegisters[0x0];
            
            context->pc = dest;
        }
        break;
        
        //random num generator
        case 0x0C:
        {
            uint16_t random = rand();
            context->varRegisters[decodedInstr.X] = random & decodedInstr.NN;
        }
        break;

        //draw
        case 0x0D:
        {
            int x = context->varRegisters[decodedInstr.X];
            int y = context->varRegisters[decodedInstr.Y];
            int h = int(decodedInstr.N);
            context->varRegisters[0x0F] = 0x00;
            draw(x, y, h);
        }
        break;

        case 0x0E:
        {
            switch (decodedInstr.N){

                //skip if not key press
                case 0x01:
                {
                    if (keypad->getKeyPress() != keypad->hexToKey[context->varRegisters[decodedInstr.X]])
                        context->pc += 0x2;
                }
                break;

                //skip if key press
                case 0x0E:
                {
                    if (keypad->getKeyPress() == keypad->hexToKey[context->varRegisters[decodedInstr.X]])
                        context->pc += 0x2;
                }
                break;
            }
        }
        break;

        case 0x0F:
        {
            switch (decodedInstr.instr & 0x00FF){

                //set VX to delay timer
                case 0x07:
                {
                    context->varRegisters[decodedInstr.X] = context->delayTimer->getTime();
                }
                break;

                //set delay timer to vx
                case 0x15:
                {
                    context->delayTimer->setTime(context->varRegisters[decodedInstr.X]);
                }
                break;

                //set sound timer to vx
                case 0x18:
                {
                    context->soundTimer->setTime(context->varRegisters[decodedInstr.X]);
                }
                break;

                case 0x1E:
                {
                    /*
                    add VX to index
                    Some interpreters set VF to index "overflows" from 0FFF to above 1000.
                    Not doing it in this case but may not be able to runs games like Spaceflight 2091.
                    */
                    context->index += context->varRegisters[decodedInstr.X];
                }
                break;

                //wait for key press
                case 0x0A:
                {
                    Sint32 key = 0;
                    while (true){
                        if (keypad->getKeyPress()){
                            key = keypad->getKeyPress();
                            break;
                        }
                    }
                    context->varRegisters[decodedInstr.X] = keypad->keyToHex[key];
                    context->pc += 2;
                }
                break;
            }
        }
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