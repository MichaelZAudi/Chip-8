#include <iostream>
#include "chip8.h"
#include "display.h"

using namespace std;

int main(int argc, char* argv[]){
    try{
    if(argc != 4){
        throw 1;
    }
    }
    catch(...){
        cout << "Incorrect number of command line arguments.\n";
        return 0;
    }
    
    Chip8 chip;
    chip.loadROM(argv[1]);

    Display output(argv[1], stoi(argv[2]));

    auto startTime = time(nullptr);

    bool quit = false;
    while(!quit){
        quit = output.keyProcessing(chip.inputKeys);
        
        auto currentTime = time(nullptr);
        
        if((currentTime - startTime) > stoi(argv[3])){
            startTime = currentTime;
            chip.cycle();
            output.updateScreen(chip.videoOut, sizeof(chip.videoOut[0]) * 64);
        }

    }
}
