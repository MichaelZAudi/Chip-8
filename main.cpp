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
    Chip8 test;
    
    Display cat(argv[1], stoi(argv[2]));
    test.cycle();
    test.loadROM(argv[1]);
    while(true){
        cat.updateScreen(test.videoOut, test.videoOut[0] * 64);
    }
}
