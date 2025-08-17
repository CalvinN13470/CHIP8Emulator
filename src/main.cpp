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

int main (int argc, char* argv[]){

    if (argc == 1){
        cerr << "Please include ROM file location in argument and add the argument 'superchip' as the second argument if you would like superchip enabled." << endl;
    }
    else if (argc > 3){
        cerr << "Unexpected number of arguments (" << argc << "): ";
        for (int i = 0 ; i < argc ; ++i){
            cerr << argv[i] << " ";
        }
        cerr << endl;
    }
    else{
        Interpreter* session;
        if (argc == 3){
            if (strcmp(argv[2], "superchip") != 0){
                cerr << "Please enter 'superchip' as second arugment to enable superchip or omit second argument to disable superchip. Second Argument: " << argv[2] << endl;
                return -1;
            }
            else{
                session = new Interpreter(argv[1], ENABLE_SUPERCHIP);
            }
        }
        else{
            session = new Interpreter(argv[1], DISABLE_SUPERCHIP);
        }

        if (!session->run()){
            cerr << "interpreter has failed to run" << endl;
        }
        
        delete session;

    }
    
    return 0;
}