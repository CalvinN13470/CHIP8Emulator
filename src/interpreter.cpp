#include "interpreter.hpp"

Interpreter::Interpreter(){

    context = new Chip8Context();
    display = new Chip8Display();
    keypad = new Chip8Keypad(display);

}

Interpreter::Interpreter(char const* filename, bool enableSuperchip){

    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open()){
        std::cerr << "Error: Could not open ROM file " << filename << std::endl;
    }
    else{
        context = new Chip8Context();
        display = new Chip8Display();
        keypad = new Chip8Keypad(display);
        interpreterTimer = new Chip8Timer(constants::PROC_MAX_DELTA_TIME, constants::PROC_CYCLE_LENGTH);

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

    superchip = enableSuperchip;

}

uint16_t Interpreter::fetch(){

    uint8_t instr1 = context->memory[int(context->pc)];
    uint8_t instr2 = context->memory[int(context->pc) + 1];
    context->pc = context->pc + 0x2;

    uint16_t instr = ((uint16_t)instr1 << 8) | instr2;

    return instr;

}

instructValues Interpreter::decode(uint16_t instr){

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

void Interpreter::execute(instructValues decodedInstr){

    switch(decodedInstr.action){

        case 0x00:
            {
                //subroutine return
                if (decodedInstr.NN == 0xEE){    
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
                        if (superchip)
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
                        if (superchip)
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
            if (superchip)
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
                    Some Interpreters set VF to index "overflows" from 0FFF to above 1000.
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

                //font character
                case 0x29:
                {
                    context->index = constants::FONT_DATA_ENTRY_INDEX + (font::FONT_CHAR_SIZE * context->varRegisters[decodedInstr.X]);
                }
                break;

                //binary-coded decimal conversion
                case 0x33:
                {
                    int extractedValue = context->varRegisters[decodedInstr.X];
                    context->memory[context->index] = extractedValue / 100;
                    context->memory[context->index + 1] = (extractedValue % 100) / 10;
                    context->memory[context->index + 2] = extractedValue % 10;
                }
                break;

                //store in memory
                case 0x55:
                {
                    uint16_t temp = context->index;
                    for (int i = 0 ; i <= decodedInstr.X ; ++i){
                        context->memory[context->index] = context->varRegisters[i];
                        context->index += 1;
                    }
                    if (superchip){
                        context->index = temp;
                    }
                }
                break;

                //load from memory
                case 0x65:
                {
                    uint16_t temp = context->index;
                    for (int i = 0 ; i <= decodedInstr.X ; ++i){
                        context->varRegisters[i] = context->memory[context->index];
                        context->index += 1;
                    }
                    if (superchip){
                        context->index = temp;
                    }
                }
                break;
            }
        }
        break;

    }

}

void Interpreter::draw(int x, int y, int h){
    x = x % constants::EMULATOR_DISPLAY_WIDTH;
    y = y % constants::EMUlATOR_DISPLAY_HEIGHT;
    int pX = x;
    int pY = y;

    for (int i = 0 ; i < h ; ++i){

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

int Interpreter::run(){

    if (context == nullptr){
        std::cerr << "Could not run. Interpreter not properly initialized" << std::endl;
        return -1;
    }
    else{
        while(keypad->getKeyPress() != SDLK_ESCAPE){
            uint16_t encodedInstruction = fetch();
            instructValues decodedInstruction = decode(encodedInstruction);
            execute(decodedInstruction);
        }
    }
    return 1;
    
}

Interpreter::~Interpreter(){

    delete context;
    delete display;
    delete keypad;
    delete interpreterTimer;

}