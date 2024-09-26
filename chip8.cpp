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
    opcode = (sysMemory[programCounter] << 8) | sysMemory[programCounter + 1];
    programCounter += 2;
    switch(opcode & 0xF000){
        case(0x0):
            switch(opcode){
                case(0x0):
                    Chip8::OP_00E0();
                    break;
                case(0xE):
                    Chip8::OP_00EE();
                    break;
                default:
                    std::cout << "Invalid opcode." << std::endl;
                    break;
            }
        case(0x1):
            Chip8::OP_1NNN();
            break;
        case(0x2):
            Chip8::OP_2NNN();
            break;
        case(0x3):
            Chip8::OP_3XNN();
            break;
        case(0x4):
            Chip8::OP_4XNN();
            break;
        case(0x5):
            Chip8::OP_5XY0();
            break;
        case(0x6):
            Chip8::OP_6XNN();
            break;
        case(0x7):
            Chip8::OP_7XNN();
            break;
        case(0x8):
            switch(opcode){
                case(0x0):
                    Chip8::OP_8XY0();
                    break;
                case(0x1):
                    Chip8::OP_8XY1();
                    break;
                case(0x2):
                    Chip8::OP_8XY2();
                    break;
                case(0x3):
                    Chip8::OP_8XY3();
                    break;
                case(0x4):
                    Chip8::OP_8XY4();
                    break;
                case(0x5):
                    Chip8::OP_8XY5();
                    break;
                case(0x6):
                    Chip8::OP_8XY6();
                    break;
                case(0x7):
                    Chip8::OP_8XY7();
                    break;
                case(0xE):
                    Chip8::OP_8XYE();
                    break;
                default:
                    std::cout << "Invalid opcode." << std::endl;
                    break;
            }
        case(0x9):
            Chip8::OP_9XY0();
            break;
        case(0xA):
            Chip8::OP_ANNN();
            break;
        case(0xB):
            Chip8::OP_BNNN();
            break;
        case(0xC):
            Chip8::OP_CXNN();
            break;
        case(0xD):
            Chip8::OP_DXYN();
            break;
        case(0xE):
            switch(opcode){
                case(0x9E):
                    Chip8::OP_EX9E();
                    break;
                case(0xA1):
                    Chip8::OP_EXA1();
                    break;
                default:
                    std::cout << "Invalid opcode." << std::endl;
                    break;
            }
        case(0xF):
            switch(opcode){
                case(0x07):
                    Chip8::OP_FX07();
                    break;
                case(0x0A):
                    Chip8::OP_FX0A();
                    break;
                case(0x15):
                    Chip8::OP_FX15();
                    break;
                case(0x18):
                    Chip8::OP_FX18();
                    break;
                case(0x1E):
                    Chip8::OP_FX1E();
                    break;
                case(0x29):
                    Chip8::OP_FX29();
                    break;
                case(0x33):
                    Chip8::OP_FX33();
                    break;
                case(0x55):
                    Chip8::OP_FX55();
                    break;
                case(0x65):
                    Chip8::OP_FX65();
                    break;
                default:
                    std::cout << "Invalid opcode." << std::endl;
                    break;
            }
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

void Chip8::OP_8XY4(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t Y = (opcode & 0x00F0u) >> 4u;
    u_int16_t sum = V[X] + V[Y];
    if(sum > 255u){
        V[15] = 1;
    }
    else{
        V[15] = 0;
    }
    V[X] = sum & 0xFFu;
}

void Chip8::OP_8XY5(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t Y = (opcode & 0x00F0u) >> 4u;
    u_int8_t difference = V[X] - V[Y];
    if(V[X] > V[Y]){
        V[15] = 1;
    }
    else{
        V[15] = 0;
    }

    V[X] = difference;
}

void Chip8::OP_8XY6(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    V[15] = V[X] & 0x1u;
    V[X] = V[X] >> 1;
}

void Chip8::OP_8XY7(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t Y = (opcode & 0x00F0u) >> 4u;
    u_int8_t difference = V[Y] - V[X];
    if(V[Y] > V[X]){
        V[15] = 1;
    }
    else{
        V[15] = 0;
    }

    V[X] = difference;
}

void Chip8::OP_8XYE(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    V[15] = (V[X] & 0x80u) >> 7u;
    V[X] = V[X] << 1;
}
void Chip8::OP_9XY0(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t Y = (opcode & 0x00F0u) >> 4u;
    if(V[X] != V[Y]){
        programCounter += 2;
    }
}

void Chip8::OP_ANNN(){
    I = opcode & 0x0FFFu;
}

void Chip8::OP_BNNN(){
    programCounter = (opcode & 0x0FFFu) + V[0];
}

void Chip8::OP_CXNN(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t NN = opcode & 0x00FFu;
    std::srand(std::time(0));
    V[X] = u_int8_t(std::rand() % 255) & NN;
}

void Chip8::OP_DXYN(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t Y = (opcode & 0x00F0u) >> 4u;
    u_int8_t N = opcode & 0x000Fu;
}

void Chip8::OP_EX9E(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;

    if(inputKeys[V[X]]){
        programCounter += 2;
    }
}

void Chip8::OP_EXA1(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;

    if(!inputKeys[V[X]]){
        programCounter += 2;
    }
}

void Chip8::OP_FX07(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    V[X] = delayTimer;
}

void Chip8::OP_FX0A(){

}

void Chip8::OP_FX15(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    delayTimer = V[X];
}

void Chip8::OP_FX18(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    soundTimer = V[X];
}

void Chip8::OP_FX1E(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    I += V[X];
}

void Chip8::OP_FX29(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    I = 0x50 * (V[X] * 5);
}

void Chip8::OP_FX33(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    u_int8_t BCD = V[X];
    sysMemory[I + 2] = BCD % 10;
    BCD = BCD / 10;
    sysMemory[I + 1] = BCD % 10;
    BCD = BCD / 10;
    sysMemory[I] = BCD % 10;
}

void Chip8::OP_FX55(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    for(u_int8_t i; i <= X, i++){
        sysMemory[I + i] = V[i];
    }
}

void Chip8::OP_FX65(){
    u_int8_t X = (opcode & 0x0F00u) >> 8u;
    for(u_int8_t i; i <= X; i++){
        V[i] = sysMemory[I + i];
    }
}