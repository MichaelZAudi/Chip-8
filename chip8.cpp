#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
#include "chip8.h"

Chip8::Chip8(){
    programCounter = 0x200;

    for(int i = 0; i < 80; i++){
        sysMemory[0x50 + i] = fontset[i];
    }
}

void Chip8::cycle(){
    opcode = sysMemory[programCounter] << 8 | sysMemory[programCounter + 1];
    programCounter += 2;
    switch(opcode){

        default:
            std::cout << "Invalid opcode." << std::endl;
            break;
    }
    if(delayTimer > 0){
        delayTimer--;
    };
    if(soundTimer > 0){
        soundTimer--;
    }
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

void Chip8::OP_00E0(){
    std::memset(videoOut, 0, sizeof(videoOut));
}

void Chip8::OP_00EE(){

}