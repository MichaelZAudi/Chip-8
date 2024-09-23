#include <iostream>
#include <fstream>
#include "chip8.h"

Chip8::Chip8(){
    programCounter = 0x200;

    for(int i = 0; i < 80; i++){
        sysMemory[0x50 + i] = fontset[i];
    }
}

void Chip8::cycle(){
    std::cout << "cycle works\n";
}

void Chip8::loadROM(char const* romName){
    std::ifstream romFile(romName, std::ios::binary | std::ios::ate);

    if(romFile.is_open()){
        std::streampos size = romFile.tellg();
        char* bufferArray = new char[size];

        romFile.seekg(0, std::ios::beg);
        romFile.read(bufferArray, size);

        for(int i = 0; i < size; i++){
            sysMemory[0x200 + i] = bufferArray[i];
        }

        delete[] bufferArray;
        romFile.close();
    }
}