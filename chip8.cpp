#include <iostream>
#include <fstream>
#include "chip8.h"

chip8::chip8(){
    programCounter = 0x200;

    for(int i = 0; i < 80; i++){
        sysMemory[0x50 + i] = fontset[i];
    }
}

void chip8::cycle(){
    std::cout << "cycle works\n";
}

void chip8::loadROM(char const* romName){
    std::ifstream romFile(romName, std::ios::binary | std::ios::ate);

    if(romFile.is_open()){
        std::streampos size = romFile.tellg();
    }
}