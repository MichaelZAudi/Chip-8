#include <iostream>
#include "chip8.h"
#include "display.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc < 4){
        return 0;
    }
    chip8 test;
    
    display cat(argv[1], stoi(argv[2]));
    test.cycle();
    test.loadROM(argv[1]);
    while(true){
        cat.clearScreen();
    }
}
