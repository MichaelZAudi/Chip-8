#ifndef CHIP8_H
#define CHIP8_H


class chip8{
    public:
        u_int8_t V[16]{0};
        u_int8_t sysMemory[4096]{0};
        u_int8_t stackPointer{0};
        u_int8_t delayTimer{0};
        u_int8_t soundTimer{0};
        u_int8_t inputKeys[16]{0};
        u_int16_t stack[16]{0};
        u_int16_t indexRegister{0};
        u_int16_t programCounter{0};
        u_int16_t opcode{0};
        u_int32_t videoOut[64 * 32]{0};

        u_int8_t fontset[80] =
        {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

        chip8();
        void cycle();
        void loadROM(char const* romName);

        
};

#endif