// #include "headers.hpp"
// #include "constants.hpp"
// #include "chip8context.hpp"
// #include "chip8display.hpp"
// #include "chip8timer.hpp"
// #include "chip8keypad.hpp"
// #include "exceptions/null_display_exception.hpp"

#include "interpreter.hpp"

using namespace chip8;
using namespace std;

int main (){

    chip8Display* display = nullptr;
    chip8Keypad* keypad = nullptr;
    display = new chip8Display();
    keypad = new chip8Keypad(display);
    while (true){
        if (keypad->getKeyPress() == keypad->keyMap[0xA])
            cout << "hello" << endl;
    }
    
}