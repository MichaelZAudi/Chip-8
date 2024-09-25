#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
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
    programCounter = stack[--stackPointer];
}

void Chip8::OP_1NNN(){
    programCounter = opcode & 0x0FFFu;
}

void Chip8::OP_2NNN(){
    stack[stackPointer] = programCounter;
    stackPointer += 2;
    programCounter = opcode & 0x0FFFu;
}

void Chip8::OP_3XNN(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t NN = opcode & 0x00FFu;
    if(V[X] == NN){
        programCounter += 2;
    }
}

void Chip8::OP_4XNN(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t NN = opcode & 0x00FFu;
    if(V[X] != NN){
        programCounter += 2;
    }
}

void Chip8::OP_5XY0(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t Y = (opcode & 0x00F0u) >> 4u;
    if(V[X] == V[Y]){
        programCounter += 2;
    }
}

void Chip8::OP_6XNN(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t NN = opcode & 0x00FFu;
    V[X] = NN;
}

void Chip8::OP_7XNN(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t NN = opcode & 0x00FFu;
    V[X] += NN;
}

void Chip8::OP_8XY0(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t Y = (opcode & 0x00F0u) >> 4u;
    V[X] = V[Y];
}

void Chip8::OP_8XY1(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t Y = (opcode & 0x00F0u) >> 4u;
    V[X] = V[X] | V[Y];
}

void Chip8::OP_8XY2(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t Y = (opcode & 0x00F0u) >> 4u;
    V[X] = V[X] & V[Y];
}

void Chip8::OP_8XY3(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t Y = (opcode & 0x00F0u) >> 4u;
    V[X] = V[X] ^ V[Y];
}